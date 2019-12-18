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
struct TYPE_2__ {int timer_tgcr; int timer_tmr1; int timer_tcn1; unsigned char timer_trr1; int timer_ter1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPMVEC_TIMER1 ; 
 unsigned char HZ ; 
 int /*<<< orphan*/  IRQ_FLG_LOCK ; 
 int IRQ_MACHSPEC ; 
 int TCMP ; 
 int TCTL ; 
 int TCTL_CLKSOURCE_32KHZ ; 
 int TCTL_IRQEN ; 
 int TCTL_OM ; 
 int TCTL_TEN ; 
 int TPRER ; 
 int /*<<< orphan*/  m68360_timer_irq ; 
 TYPE_1__* pquicc ; 
 int /*<<< orphan*/  request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned char system_clock ; 
 int /*<<< orphan*/  timer_routine ; 

void hw_timer_init(void)
{
  unsigned char prescaler;
  unsigned short tgcr_save;

#if 0
  /* Restart mode, Enable int, 32KHz, Enable timer */
  TCTL = TCTL_OM | TCTL_IRQEN | TCTL_CLKSOURCE_32KHZ | TCTL_TEN;
  /* Set prescaler (Divide 32KHz by 32)*/
  TPRER = 31;
  /* Set compare register  32Khz / 32 / 10 = 100 */
  TCMP = 10;                                                              

  request_irq(IRQ_MACHSPEC | 1, timer_routine, IRQ_FLG_LOCK, "timer", NULL);
#endif

  /* General purpose quicc timers: MC68360UM p7-20 */

  /* Set up timer 1 (in [1..4]) to do 100Hz */
  tgcr_save = pquicc->timer_tgcr & 0xfff0;
  pquicc->timer_tgcr  = tgcr_save; /* stop and reset timer 1 */
  /* pquicc->timer_tgcr |= 0x4444; */ /* halt timers when FREEZE (ie bdm freeze) */

  prescaler = 8;
  pquicc->timer_tmr1 = 0x001a | /* or=1, frr=1, iclk=01b */
                           (unsigned short)((prescaler - 1) << 8);
    
  pquicc->timer_tcn1 = 0x0000; /* initial count */
  /* calculate interval for 100Hz based on the _system_clock: */
  pquicc->timer_trr1 = (system_clock/ prescaler) / HZ; /* reference count */

  pquicc->timer_ter1 = 0x0003; /* clear timer events */

  /* enable timer 1 interrupt in CIMR */
  setup_irq(CPMVEC_TIMER1, &m68360_timer_irq);

  /* Start timer 1: */
  tgcr_save = (pquicc->timer_tgcr & 0xfff0) | 0x0001;
  pquicc->timer_tgcr  = tgcr_save;
}