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
struct mv_xor_chan {int /*<<< orphan*/  irq_tasklet; TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_chan_get_intr_cause (struct mv_xor_chan*) ; 
 scalar_t__ mv_is_err_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_xor_device_clear_eoc_cause (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  mv_xor_err_interrupt_handler (struct mv_xor_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mv_xor_interrupt_handler(int irq, void *data)
{
	struct mv_xor_chan *chan = data;
	u32 intr_cause = mv_chan_get_intr_cause(chan);

	dev_dbg(chan->device->common.dev, "intr cause %x\n", intr_cause);

	if (mv_is_err_intr(intr_cause))
		mv_xor_err_interrupt_handler(chan, intr_cause);

	tasklet_schedule(&chan->irq_tasklet);

	mv_xor_device_clear_eoc_cause(chan);

	return IRQ_HANDLED;
}