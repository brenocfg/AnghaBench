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
struct TYPE_2__ {scalar_t__ mode; int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;
struct sh_tmu_priv {TYPE_1__ ced; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CLOCK_EVT_MODE_ONESHOT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  sh_tmu_write (struct sh_tmu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t sh_tmu_interrupt(int irq, void *dev_id)
{
	struct sh_tmu_priv *p = dev_id;

	/* disable or acknowledge interrupt */
	if (p->ced.mode == CLOCK_EVT_MODE_ONESHOT)
		sh_tmu_write(p, TCR, 0x0000);
	else
		sh_tmu_write(p, TCR, 0x0020);

	/* notify clockevent layer */
	p->ced.event_handler(&p->ced);
	return IRQ_HANDLED;
}