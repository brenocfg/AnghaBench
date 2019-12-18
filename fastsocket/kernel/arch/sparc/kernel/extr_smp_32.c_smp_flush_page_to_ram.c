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
typedef  int /*<<< orphan*/  smpfunc_t ;

/* Variables and functions */
 scalar_t__ BTFIXUP_CALL (int /*<<< orphan*/  (*) (unsigned long)) ; 
 int /*<<< orphan*/  local_flush_page_to_ram (unsigned long) ; 
 int /*<<< orphan*/  xc1 (int /*<<< orphan*/ ,unsigned long) ; 

void smp_flush_page_to_ram(unsigned long page)
{
	/* Current theory is that those who call this are the one's
	 * who have just dirtied their cache with the pages contents
	 * in kernel space, therefore we only run this on local cpu.
	 *
	 * XXX This experiment failed, research further... -DaveM
	 */
#if 1
	xc1((smpfunc_t) BTFIXUP_CALL(local_flush_page_to_ram), page);
#endif
	local_flush_page_to_ram(page);
}