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
typedef  int u8 ;
typedef  int u16 ;
struct slot {struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROG_INTERFACE ; 
 int /*<<< orphan*/  SEC_BUS_CONFIG ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*,int) ; 
 int shpc_readb (struct controller*,int /*<<< orphan*/ ) ; 
 int shpc_readw (struct controller*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpc_get_mode1_ECC_cap(struct slot *slot, u8 *mode)
{
	int retval = 0;
	struct controller *ctrl = slot->ctrl;
	u16 sec_bus_status = shpc_readw(ctrl, SEC_BUS_CONFIG);
	u8 pi = shpc_readb(ctrl, PROG_INTERFACE);

	if (pi == 2) {
		*mode = (sec_bus_status & 0x0100) >> 8;
	} else {
		retval = -1;
	}

	ctrl_dbg(ctrl, "Mode 1 ECC cap = %d\n", *mode);
	return retval;
}