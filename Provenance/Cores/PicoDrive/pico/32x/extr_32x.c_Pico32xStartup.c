#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pal; scalar_t__ ncart_in; } ;
struct TYPE_11__ {TYPE_1__ m; } ;
struct TYPE_10__ {int /*<<< orphan*/ * vdp_regs; int /*<<< orphan*/ * sh2_regs; } ;
struct TYPE_9__ {void* irq_callback; } ;

/* Variables and functions */
 int EL_32X ; 
 int EL_STATUS ; 
 int /*<<< orphan*/  P32XS2_ADEN ; 
 int /*<<< orphan*/  P32XS_nCART ; 
 int /*<<< orphan*/  P32XV_nPAL ; 
 int /*<<< orphan*/  PAHW_32X ; 
 TYPE_7__ Pico ; 
 TYPE_6__ Pico32x ; 
 int /*<<< orphan*/  PicoAHW ; 
 int /*<<< orphan*/  PicoMemSetup32x () ; 
 int /*<<< orphan*/  elprintf (int,char*) ; 
 int /*<<< orphan*/  emu_32x_startup () ; 
 TYPE_2__ msh2 ; 
 int /*<<< orphan*/  p32x_pwm_ctl_changed () ; 
 int /*<<< orphan*/  p32x_timers_recalc () ; 
 int rendstatus_old ; 
 int /*<<< orphan*/  sh2_init (TYPE_2__*,int,TYPE_2__*) ; 
 void* sh2_irq_cb ; 
 TYPE_2__ ssh2 ; 

void Pico32xStartup(void)
{
  elprintf(EL_STATUS|EL_32X, "32X startup");

  // TODO: OOM handling
  PicoAHW |= PAHW_32X;
  sh2_init(&msh2, 0, &ssh2);
  msh2.irq_callback = sh2_irq_cb;
  sh2_init(&ssh2, 1, &msh2);
  ssh2.irq_callback = sh2_irq_cb;

  PicoMemSetup32x();
  p32x_pwm_ctl_changed();
  p32x_timers_recalc();

  Pico32x.sh2_regs[0] = P32XS2_ADEN;
  if (Pico.m.ncart_in)
    Pico32x.sh2_regs[0] |= P32XS_nCART;

  if (!Pico.m.pal)
    Pico32x.vdp_regs[0] |= P32XV_nPAL;

  rendstatus_old = -1;

  emu_32x_startup();
}