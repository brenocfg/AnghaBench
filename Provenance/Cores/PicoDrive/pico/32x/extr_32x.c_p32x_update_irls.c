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
struct TYPE_2__ {int sh2irqs; int* sh2irqi; } ;
typedef  int /*<<< orphan*/  SH2 ;

/* Variables and functions */
 int /*<<< orphan*/  EL_32X ; 
 TYPE_1__ Pico32x ; 
 int /*<<< orphan*/  SH2_IDLE_STATES ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  msh2 ; 
 int /*<<< orphan*/  p32x_sh2_poll_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sh2_cycles_done_m68k (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh2_end_run (int /*<<< orphan*/ *,int) ; 
 int sh2_irl_irq (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ssh2 ; 

void p32x_update_irls(SH2 *active_sh2, int m68k_cycles)
{
  int irqs, mlvl = 0, slvl = 0;
  int mrun, srun;

  if (active_sh2 != NULL)
    m68k_cycles = sh2_cycles_done_m68k(active_sh2);

  // msh2
  irqs = Pico32x.sh2irqs | Pico32x.sh2irqi[0];
  while ((irqs >>= 1))
    mlvl++;
  mlvl *= 2;

  // ssh2
  irqs = Pico32x.sh2irqs | Pico32x.sh2irqi[1];
  while ((irqs >>= 1))
    slvl++;
  slvl *= 2;

  mrun = sh2_irl_irq(&msh2, mlvl, active_sh2 == &msh2);
  if (mrun) {
    p32x_sh2_poll_event(&msh2, SH2_IDLE_STATES, m68k_cycles);
    if (active_sh2 == &msh2)
      sh2_end_run(active_sh2, 1);
  }

  srun = sh2_irl_irq(&ssh2, slvl, active_sh2 == &ssh2);
  if (srun) {
    p32x_sh2_poll_event(&ssh2, SH2_IDLE_STATES, m68k_cycles);
    if (active_sh2 == &ssh2)
      sh2_end_run(active_sh2, 1);
  }

  elprintf(EL_32X, "update_irls: m %d/%d, s %d/%d", mlvl, mrun, slvl, srun);
}