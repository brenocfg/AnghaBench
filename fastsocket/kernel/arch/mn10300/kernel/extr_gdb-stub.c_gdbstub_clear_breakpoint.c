#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * origbytes; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOENT ; 
 int /*<<< orphan*/  gdbstub_bkpt (char*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* gdbstub_bkpts ; 
 int gdbstub_flush_caches ; 
 scalar_t__ gdbstub_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int gdbstub_clear_breakpoint(u8 *addr, int len)
{
	int bkpt, loop;

#ifdef GDBSTUB_USE_F7F7_AS_BREAKPOINT
	len = (len + 1) & ~1;
#endif

	gdbstub_bkpt("clearbkpt(%p,%d)\n", addr, len);

	for (bkpt = 255; bkpt >= 0; bkpt--)
		if (gdbstub_bkpts[bkpt].addr == addr &&
		    gdbstub_bkpts[bkpt].len == len)
			break;
	if (bkpt < 0)
		return -ENOENT;

	gdbstub_bkpts[bkpt].addr = NULL;

	gdbstub_flush_caches = 1;

	for (loop = 0; loop < len; loop++)
		if (gdbstub_write_byte(gdbstub_bkpts[bkpt].origbytes[loop],
				       addr + loop) < 0)
			return -EFAULT;

	return 0;
}