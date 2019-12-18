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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int timer_ter1; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_timer_interrupt (int,void*) ; 
 TYPE_1__* pquicc ; 

__attribute__((used)) static irqreturn_t hw_tick(int irq, void *dummy)
{
  /* Reset Timer1 */
  /* TSTAT &= 0; */

  pquicc->timer_ter1 = 0x0002; /* clear timer event */

  return arch_timer_interrupt(irq, dummy);
}