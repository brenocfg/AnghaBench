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
typedef  int /*<<< orphan*/  atom_exec_context ;

/* Variables and functions */
 int ATOM_UNIT_MICROSEC ; 
 int /*<<< orphan*/  SDEBUG (char*,unsigned int) ; 
 unsigned int U8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_can_sleep () ; 
 int /*<<< orphan*/  mdelay (unsigned int) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 

__attribute__((used)) static void atom_op_delay(atom_exec_context *ctx, int *ptr, int arg)
{
	unsigned count = U8((*ptr)++);
	SDEBUG("   count: %d\n", count);
	if (arg == ATOM_UNIT_MICROSEC)
		udelay(count);
	else if (!drm_can_sleep())
		mdelay(count);
	else
		msleep(count);
}