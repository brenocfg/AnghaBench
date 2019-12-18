#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int vm_size_t ;
typedef  TYPE_1__* ipc_table_size_t ;
typedef  void* ipc_table_elems_t ;
struct TYPE_3__ {void* its_size; } ;

/* Variables and functions */
 unsigned int PAGE_MAX_SIZE ; 

__attribute__((used)) static void
ipc_table_fill(
	ipc_table_size_t	its,	     /* array to fill */
	unsigned int		num,	     /* size of array */
	unsigned int		min,	     /* at least this many elements */
	vm_size_t		elemsize)    /* size of elements */
{
	unsigned int index;
	vm_size_t minsize = min * elemsize;
	vm_size_t size;
	vm_size_t incrsize;

	/* first use powers of two, up to the page size */

	for (index = 0, size = 1;
	     (index < num) && (size < PAGE_MAX_SIZE);
	     size <<= 1) {
		if (size >= minsize) {
			its[index].its_size = (ipc_table_elems_t)(size / elemsize);
			index++;
		}
	}

	/* then increments of a page, then two pages, etc. */

	for (incrsize = PAGE_MAX_SIZE; index < num;) {
		unsigned int period;

		for (period = 0;
		     (period < 15) && (index < num);
		     period++, size += incrsize) {
			if (size >= minsize) {
				its[index].its_size = (ipc_table_elems_t)(size / elemsize);
				index++;
			}
		}
		if (incrsize < (vm_size_t)(PAGE_MAX_SIZE << 3))
			incrsize <<= 1;
	}
}