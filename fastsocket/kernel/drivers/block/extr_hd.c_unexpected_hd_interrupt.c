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
 unsigned int BUSY_STAT ; 
 unsigned int DRQ_STAT ; 
 unsigned int ECC_STAT ; 
 unsigned int ERR_STAT ; 
 int /*<<< orphan*/  HD_STATUS ; 
 int /*<<< orphan*/  SET_TIMER ; 
 int /*<<< orphan*/  dump_status (char*,unsigned int) ; 
 unsigned int inb_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unexpected_hd_interrupt(void)
{
	unsigned int stat = inb_p(HD_STATUS);

	if (stat & (BUSY_STAT|DRQ_STAT|ECC_STAT|ERR_STAT)) {
		dump_status("unexpected interrupt", stat);
		SET_TIMER;
	}
}