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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  emu_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_SVP ; 
 int GET_PPC_OFFS () ; 
 int /*<<< orphan*/  SSP_WAIT_PM0 ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,...) ; 
 int pm_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rPM0 ; 
 TYPE_1__* ssp ; 

__attribute__((used)) static u32 read_PM0(void)
{
  u32 d = pm_io(0, 0, 0);
  if (d != (u32)-1) return d;
#ifdef LOG_SVP
  elprintf(EL_SVP, "PM0 raw r %04x @ %04x", rPM0, GET_PPC_OFFS());
#endif
  d = rPM0;
  if (!(d & 2) && (GET_PPC_OFFS() == 0x800 || GET_PPC_OFFS() == 0x1851E)) {
    ssp->emu_status |= SSP_WAIT_PM0;
#ifdef LOG_SVP
    elprintf(EL_SVP, "det TIGHT loop: PM0");
#endif
  }
  rPM0 &= ~2; /* ? */
  return d;
}