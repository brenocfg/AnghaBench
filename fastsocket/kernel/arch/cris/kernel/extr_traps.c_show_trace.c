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

/* Variables and functions */
 int THREAD_SIZE ; 
 unsigned long VMALLOC_END ; 
 unsigned long VMALLOC_START ; 
 scalar_t__ __get_user (unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

void
show_trace(unsigned long *stack)
{
	unsigned long addr, module_start, module_end;
	extern char _stext, _etext;
	int i;

	printk("\nCall Trace: ");

	i = 1;
	module_start = VMALLOC_START;
	module_end = VMALLOC_END;

	while (((long)stack & (THREAD_SIZE-1)) != 0) {
		if (__get_user(addr, stack)) {
			/* This message matches "failing address" marked
			   s390 in ksymoops, so lines containing it will
			   not be filtered out by ksymoops.  */
			printk("Failing address 0x%lx\n", (unsigned long)stack);
			break;
		}
		stack++;

		/*
		 * If the address is either in the text segment of the
		 * kernel, or in the region which contains vmalloc'ed
		 * memory, it *may* be the address of a calling
		 * routine; if so, print it so that someone tracing
		 * down the cause of the crash will be able to figure
		 * out the call path that was taken.
		 */
		if (((addr >= (unsigned long)&_stext) &&
		     (addr <= (unsigned long)&_etext)) ||
		    ((addr >= module_start) && (addr <= module_end))) {
			if (i && ((i % 8) == 0))
				printk("\n       ");
			printk("[<%08lx>] ", addr);
			i++;
		}
	}
}