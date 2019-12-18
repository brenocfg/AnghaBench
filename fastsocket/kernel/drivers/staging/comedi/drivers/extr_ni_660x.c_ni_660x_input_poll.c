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
struct comedi_subdevice {int /*<<< orphan*/  async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  interrupt_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  mite_chan; } ;

/* Variables and functions */
 int comedi_buf_read_n_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_sync_input_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* private (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* subdev_to_counter (struct comedi_subdevice*) ; 

__attribute__((used)) static int ni_660x_input_poll(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	unsigned long flags;
	/* lock to avoid race with comedi_poll */
	spin_lock_irqsave(&private(dev)->interrupt_lock, flags);
	mite_sync_input_dma(subdev_to_counter(s)->mite_chan, s->async);
	spin_unlock_irqrestore(&private(dev)->interrupt_lock, flags);
	return comedi_buf_read_n_available(s->async);
}