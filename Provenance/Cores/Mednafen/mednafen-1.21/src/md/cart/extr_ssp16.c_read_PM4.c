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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  emu_status; } ;

/* Variables and functions */
 int EL_ANOMALY ; 
 int EL_SVP ; 
 int GET_PPC_OFFS () ; 
 int /*<<< orphan*/  SSP_WAIT_30FE06 ; 
 int /*<<< orphan*/  SSP_WAIT_30FE08 ; 
 int /*<<< orphan*/  elprintf (int,char*,...) ; 
 scalar_t__ pm_io (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rPM4 ; 
 TYPE_1__* ssp ; 

__attribute__((used)) static u32 read_PM4(void)
{
	u32 d = pm_io(4, 0, 0);

	if (d == 0) {
		switch (GET_PPC_OFFS()) {
			case 0x0854: ssp->emu_status |= SSP_WAIT_30FE08; elprintf(EL_SVP, "det TIGHT loop: [30fe08]"); break;
			case 0x4f12: ssp->emu_status |= SSP_WAIT_30FE06; elprintf(EL_SVP, "det TIGHT loop: [30fe06]"); break;
		}
	}

	if (d != (u32)-1) return d;
	// can be removed?
	elprintf(EL_SVP|EL_ANOMALY, "PM4 raw r %04x @ %04x", rPM4, GET_PPC_OFFS());
	return rPM4;
}