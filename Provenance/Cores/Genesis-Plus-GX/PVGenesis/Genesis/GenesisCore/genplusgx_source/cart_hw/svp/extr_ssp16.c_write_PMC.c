#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_4__ {void* h; void* l; } ;
struct TYPE_6__ {TYPE_1__ byte; } ;
struct TYPE_5__ {int emu_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_SVP ; 
 int /*<<< orphan*/  GET_PPC_OFFS () ; 
 int SSP_PMC_HAVE_ADDR ; 
 int SSP_PMC_SET ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ ) ; 
 TYPE_3__ rPMC ; 
 TYPE_2__* ssp ; 

__attribute__((used)) static void write_PMC(u32 d)
{
  if (ssp->emu_status & SSP_PMC_HAVE_ADDR) {
    /* if (ssp->emu_status & SSP_PMC_SET) */
    /*  elprintf(EL_ANOMALY|EL_SVP, "prev PMC not used @ %04x", GET_PPC_OFFS()); */
    ssp->emu_status |= SSP_PMC_SET;
    ssp->emu_status &= ~SSP_PMC_HAVE_ADDR;
    /* rPMC.l = d; */
    rPMC.byte.h = d;
#ifdef LOG_SVP
    elprintf(EL_SVP, "PMC w m %04x @ %04x", rPMC.byte.l, GET_PPC_OFFS());
#endif
  } else {
    ssp->emu_status |= SSP_PMC_HAVE_ADDR;
    /* rPMC.h = d; */
    rPMC.byte.l = d;
#ifdef LOG_SVP
    elprintf(EL_SVP, "PMC w a %04x @ %04x", rPMC.byte.h, GET_PPC_OFFS());
#endif
  }
}