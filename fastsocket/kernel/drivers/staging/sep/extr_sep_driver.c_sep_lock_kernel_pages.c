#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sep_lli_entry_t {unsigned long physical_address; unsigned long block_size; } ;
struct sep_device {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  edbg (char*,...) ; 
 struct sep_lli_entry_t* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_phys (unsigned long*) ; 

__attribute__((used)) static int sep_lock_kernel_pages(struct sep_device *sep,
				 unsigned long kernel_virt_addr,
				 unsigned long data_size,
				 unsigned long *num_pages_ptr,
				 struct sep_lli_entry_t **lli_array_ptr,
				 struct page ***page_array_ptr)
{
	int error = 0;
	/* the the page of the end address of the user space buffer */
	unsigned long end_page;
	/* the page of the start address of the user space buffer */
	unsigned long start_page;
	/* the range in pages */
	unsigned long num_pages;
	struct sep_lli_entry_t *lli_array;
	/* next kernel address to map */
	unsigned long next_kernel_address;
	unsigned long count;

	dbg("SEP Driver:--------> sep_lock_kernel_pages start\n");

	/* set start and end pages  and num pages */
	end_page = (kernel_virt_addr + data_size - 1) >> PAGE_SHIFT;
	start_page = kernel_virt_addr >> PAGE_SHIFT;
	num_pages = end_page - start_page + 1;

	edbg("SEP Driver: kernel_virt_addr is %08lx\n", kernel_virt_addr);
	edbg("SEP Driver: data_size is %lu\n", data_size);
	edbg("SEP Driver: start_page is %lx\n", start_page);
	edbg("SEP Driver: end_page is %lx\n", end_page);
	edbg("SEP Driver: num_pages is %lu\n", num_pages);

	lli_array = kmalloc(sizeof(struct sep_lli_entry_t) * num_pages, GFP_ATOMIC);
	if (!lli_array) {
		edbg("SEP Driver: kmalloc for lli_array failed\n");
		error = -ENOMEM;
		goto end_function;
	}

	/* set the start address of the first page - app data may start not at
	   the beginning of the page */
	lli_array[0].physical_address = (unsigned long) virt_to_phys((unsigned long *) kernel_virt_addr);

	/* check that not all the data is in the first page only */
	if ((PAGE_SIZE - (kernel_virt_addr & (~PAGE_MASK))) >= data_size)
		lli_array[0].block_size = data_size;
	else
		lli_array[0].block_size = PAGE_SIZE - (kernel_virt_addr & (~PAGE_MASK));

	/* debug print */
	dbg("lli_array[0].physical_address is %08lx, lli_array[0].block_size is %lu\n", lli_array[0].physical_address, lli_array[0].block_size);

	/* advance the address to the start of the next page */
	next_kernel_address = (kernel_virt_addr & PAGE_MASK) + PAGE_SIZE;

	/* go from the second page to the prev before last */
	for (count = 1; count < (num_pages - 1); count++) {
		lli_array[count].physical_address = (unsigned long) virt_to_phys((unsigned long *) next_kernel_address);
		lli_array[count].block_size = PAGE_SIZE;

		edbg("lli_array[%lu].physical_address is %08lx, lli_array[%lu].block_size is %lu\n", count, lli_array[count].physical_address, count, lli_array[count].block_size);
		next_kernel_address += PAGE_SIZE;
	}

	/* if more then 1 pages locked - then update for the last page size needed */
	if (num_pages > 1) {
		/* update the address of the last page */
		lli_array[count].physical_address = (unsigned long) virt_to_phys((unsigned long *) next_kernel_address);

		/* set the size of the last page */
		lli_array[count].block_size = (kernel_virt_addr + data_size) & (~PAGE_MASK);

		if (lli_array[count].block_size == 0) {
			dbg("app_virt_addr is %08lx\n", kernel_virt_addr);
			dbg("data_size is %lu\n", data_size);
			while (1);
		}

		edbg("lli_array[%lu].physical_address is %08lx, lli_array[%lu].block_size is %lu\n", count, lli_array[count].physical_address, count, lli_array[count].block_size);
	}
	/* set output params */
	*lli_array_ptr = lli_array;
	*num_pages_ptr = num_pages;
	*page_array_ptr = 0;
end_function:
	dbg("SEP Driver:<-------- sep_lock_kernel_pages end\n");
	return 0;
}