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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  v; } ;
struct TYPE_3__ {int emu_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_SVP ; 
 int /*<<< orphan*/  GET_PPC_OFFS () ; 
 int* PC ; 
 int SSP_PMC_HAVE_ADDR ; 
 int SSP_PMC_SET ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rAL ; 
 TYPE_2__ rPMC ; 
 TYPE_1__* ssp ; 

__attribute__((used)) static u32 read_AL(void)
{
  if (*(PC-1) == 0x000f) {
#ifdef LOG_SVP
    elprintf(EL_SVP, "ssp dummy PM assign %08x @ %04x", rPMC.v, GET_PPC_OFFS());
#endif
    ssp->emu_status &= ~(SSP_PMC_SET|SSP_PMC_HAVE_ADDR); /* ? */
  }
  return rAL;
}