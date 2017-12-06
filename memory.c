/* Author(s): <Your name here>
 * Implementation of the memory manager for the kernel.
 */

#include "common.h"
#include "interrupt.h"
#include "kernel.h"
#include "memory.h"
#include "printf.h"
#include "scheduler.h"
#include "util.h"

#define MEM_START 0xa0908000

/* Static global variables */
// Keep track of all pages: their vaddr, status, and other properties
static page_map_entry_t page_map[ PAGEABLE_PAGES ];

// other global variables...
/*static lock_t page_fault_lock;*/

/* TODO: Returns physical address of page number i */
uint32_t page_vaddr( int i ) {
    return ;
}

/* TODO: Returns virtual address (in kernel) of page number i */
uint32_t page_paddr( int i ) {
    return ;
}

/* get the physical address from virtual address (in kernel) */
uint32_t va2pa( uint32_t va ) {
    return (uint32_t) va - 0xa0000000;
}

/* get the virtual address (in kernel) from physical address */
uint32_t pa2va( uint32_t pa ) {
    return (uint32_t) pa + 0xa0000000;
}


// TODO: insert page table entry to page table
void insert_page_table_entry( uint32_t *table, uint32_t vaddr, uint32_t paddr,
                              uint32_t flag, uint32_t pid ) {
    // insert entry

    // tlb flush
}

/* TODO: Allocate a page. Return page index in the page_map directory.
 *
 * Marks page as pinned if pinned == TRUE.
 * Swap out a page if no space is available.
 */
 
uint32_t find_free_page(page_map_entry_t* page_map) {
	int i;
	for (i = 0; i < PAGEABLE_PAGES; ++i)
	{
		if(page_map[i].is_available==TRUE)
		{
			break;
		}
	}
}
 
int page_alloc( int pinned ) {
 
    // code here
	uint32_t free_index;
	// find an availabe physical page
	free_index = find_free_page();
	
	
	if(free_index>=PAGEABLE_PAGES)
	{
		free_index=page_replacement_policy();//select a victim
		page_swap_out(free_index);
	}
	
	
	// initialize a physical page (wirte infomation to page_map)
 	page_map[free_index].is_pinned=(pinned==TRUE)?TRUE:FALSE;
 	if(pinned==FALSE)//pinned page need not to be in the swap queue
 		queue_put(page_queue,(node_t*)&page_map[free_index]);
 	page_map[free_index].is_available=FALSE;
 	page_map[free_index].pid=current_running->pid;
 	page_map[free_index].page_directory=current_running->page_directory;
 	page_map[free_index].swap_loc=current_running->swap_loc;
  	page_map[free_index].vaddr=current_running->fault_addr&PE_BASE_ADDR_MASK;
	//calculate real sectors to swap
	int near_sectors=current_running->swap_size % SECTORS_PER_PAGE;
	int need_sector_num=(current_running->fault_addr - PROCESS_START) / SECTOR_SIZE;
	if(current_running->swap_size- near_sectors <= need_sector_num)
		page_map[free_index].swap_size=near_sectors;
	else
		page_map[free_index].swap_size=SECTORS_PER_PAGE;
	// zero-out the process page
	bzero((char*)page_addr(free_index),PAGE_SIZE);
    ASSERT( free_index < PAGEABLE_PAGES );
	return free_index;

}

/* TODO: 
 * This method is only called once by _start() in kernel.c
 */
uint32_t init_memory( void ) {
    
    // initialize all pageable pages to a default state
    

}

/* TODO: 
 * 
 */
uint32_t setup_page_table( int pid ) {
    uint32_t page_table;

    // alloc page for page table 

   
    // initialize PTE and insert several entries into page tables using insert_page_table_entry
    

    return page_table;
}

uint32_t do_tlb_miss(uint32_t vaddr, int pid) {
    return 0;
}

void create_pte(uint32_t vaddr, int pid) {
    return;
}
