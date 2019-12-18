#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int l; } ;
struct TYPE_3__ {int emu_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_SVP ; 
 int /*<<< orphan*/  GET_PPC_OFFS () ; 
 int SSP_PMC_HAVE_ADDR ; 
 int SSP_PMC_SET ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,char,int /*<<< orphan*/ ) ; 
 TYPE_2__ rPMC ; 
 TYPE_1__* ssp ; 

__attribute__((used)) static u32 read_PMC(void)
{
	elprintf(EL_SVP, "PMC r a %04x (st %c) @ %04x", rPMC.l,
		(ssp->emu_status & SSP_PMC_HAVE_ADDR) ? 'm' : 'a', GET_PPC_OFFS());
	if (ssp->emu_status & SSP_PMC_HAVE_ADDR) {
		//if (ssp->emu_status & SSP_PMC_SET)
		//	elprintf(EL_ANOMALY|EL_SVP, "prev PMC not used @ %04x", GET_PPC_OFFS());
		ssp->emu_status |= SSP_PMC_SET;
		ssp->emu_status &= ~SSP_PMC_HAVE_ADDR;
		return ((rPMC.l << 4) & 0xfff0) | ((rPMC.l >> 4) & 0xf);
	} else {
		ssp->emu_status |= SSP_PMC_HAVE_ADDR;
		return rPMC.l;
	}
}