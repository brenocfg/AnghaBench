#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ rom; } ;
struct TYPE_7__ {int v; } ;
struct TYPE_6__ {int emu_status; int* pmac_read; } ;
struct TYPE_5__ {scalar_t__ dram; } ;

/* Variables and functions */
 TYPE_4__ Pico ; 
 int SSP_PMC_HAVE_ADDR ; 
 int SSP_PMC_SET ; 
 int get_inc (int) ; 
 TYPE_3__ rPMC ; 
 TYPE_2__* ssp ; 
 TYPE_1__* svp ; 

u32 ssp_pm_read(int reg)
{
	u32 d = 0, mode;

	if (ssp->emu_status & SSP_PMC_SET)
	{
		ssp->pmac_read[reg] = rPMC.v;
		ssp->emu_status &= ~SSP_PMC_SET;
		return 0;
	}

	// just in case
	ssp->emu_status &= ~SSP_PMC_HAVE_ADDR;

	mode = ssp->pmac_read[reg]>>16;
	if      ((mode & 0xfff0) == 0x0800) // ROM
	{
		d = ((unsigned short *)Pico.rom)[ssp->pmac_read[reg]&0xfffff];
		ssp->pmac_read[reg] += 1;
	}
	else if ((mode & 0x47ff) == 0x0018) // DRAM
	{
		unsigned short *dram = (unsigned short *)svp->dram;
		int inc = get_inc(mode);
		d = dram[ssp->pmac_read[reg]&0xffff];
		ssp->pmac_read[reg] += inc;
	}

	// PMC value corresponds to last PMR accessed
	rPMC.v = ssp->pmac_read[reg];

	return d;
}