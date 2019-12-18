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
struct TYPE_2__ {int /*<<< orphan*/  interrupt_task; } ;
struct ehca_shca {TYPE_1__ eq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

irqreturn_t ehca_interrupt_eq(int irq, void *dev_id)
{
	struct ehca_shca *shca = (struct ehca_shca*)dev_id;

	tasklet_hi_schedule(&shca->eq.interrupt_task);

	return IRQ_HANDLED;
}