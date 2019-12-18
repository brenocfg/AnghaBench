#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ field; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct vpfe_device {scalar_t__ cur_frm; scalar_t__ next_frm; int /*<<< orphan*/  dma_queue_lock; int /*<<< orphan*/  dma_queue; TYPE_3__ fmt; int /*<<< orphan*/  started; int /*<<< orphan*/  v4l2_dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vpfe_schedule_next_buffer (struct vpfe_device*) ; 

__attribute__((used)) static irqreturn_t vdint1_isr(int irq, void *dev_id)
{
	struct vpfe_device *vpfe_dev = dev_id;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "\nInside vdint1_isr...\n");

	/* if streaming not started, don't do anything */
	if (!vpfe_dev->started)
		return IRQ_HANDLED;

	spin_lock(&vpfe_dev->dma_queue_lock);
	if ((vpfe_dev->fmt.fmt.pix.field == V4L2_FIELD_NONE) &&
	    !list_empty(&vpfe_dev->dma_queue) &&
	    vpfe_dev->cur_frm == vpfe_dev->next_frm)
		vpfe_schedule_next_buffer(vpfe_dev);
	spin_unlock(&vpfe_dev->dma_queue_lock);
	return IRQ_HANDLED;
}