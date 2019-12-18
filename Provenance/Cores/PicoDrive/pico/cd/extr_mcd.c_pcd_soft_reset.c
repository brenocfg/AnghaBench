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
struct TYPE_3__ {scalar_t__ s68k_pend_ints; } ;
struct TYPE_4__ {int* s68k_regs; TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_CD ; 
 int /*<<< orphan*/  PCD_EVENT_CDC ; 
 TYPE_2__* Pico_mcd ; 
 int /*<<< orphan*/  cdc_reset () ; 
 int /*<<< orphan*/  cdd_reset () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcd_event_schedule_s68k (int /*<<< orphan*/ ,int) ; 

void pcd_soft_reset(void)
{
  elprintf(EL_CD, "cd: soft reset");

  Pico_mcd->m.s68k_pend_ints = 0;
  cdc_reset();
  cdd_reset();
#ifdef _ASM_CD_MEMORY_C
  //PicoMemResetCDdecode(1); // don't have to call this in 2M mode
#endif

  memset(&Pico_mcd->s68k_regs[0x38], 0, 9);
  Pico_mcd->s68k_regs[0x38+9] = 0x0f;  // default checksum

  pcd_event_schedule_s68k(PCD_EVENT_CDC, 12500000/75);

  // TODO: test if register state/timers change
}