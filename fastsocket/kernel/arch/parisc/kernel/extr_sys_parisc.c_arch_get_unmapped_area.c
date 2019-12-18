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
struct file {int /*<<< orphan*/ * f_mapping; } ;

/* Variables and functions */
 unsigned long ENOMEM ; 
 unsigned long MAP_FIXED ; 
 unsigned long MAP_SHARED ; 
 unsigned long TASK_SIZE ; 
 unsigned long TASK_UNMAPPED_BASE ; 
 unsigned long get_shared_area (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long) ; 
 unsigned long get_unshared_area (unsigned long,unsigned long) ; 

unsigned long arch_get_unmapped_area(struct file *filp, unsigned long addr,
		unsigned long len, unsigned long pgoff, unsigned long flags)
{
	if (len > TASK_SIZE)
		return -ENOMEM;
	/* Might want to check for cache aliasing issues for MAP_FIXED case
	 * like ARM or MIPS ??? --BenH.
	 */
	if (flags & MAP_FIXED)
		return addr;
	if (!addr)
		addr = TASK_UNMAPPED_BASE;

	if (filp) {
		addr = get_shared_area(filp->f_mapping, addr, len, pgoff);
	} else if(flags & MAP_SHARED) {
		addr = get_shared_area(NULL, addr, len, pgoff);
	} else {
		addr = get_unshared_area(addr, len);
	}
	return addr;
}