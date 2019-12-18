#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cafe_camera {int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; int /*<<< orphan*/  iowait; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_DMA_ACTIVE ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  S_IDLE ; 
 int /*<<< orphan*/  cafe_ctlr_irq_disable (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_ctlr_stop (struct cafe_camera*) ; 
 int /*<<< orphan*/  cam_err (struct cafe_camera*,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cafe_ctlr_stop_dma(struct cafe_camera *cam)
{
	unsigned long flags;

	/*
	 * Theory: stop the camera controller (whether it is operating
	 * or not).  Delay briefly just in case we race with the SOF
	 * interrupt, then wait until no DMA is active.
	 */
	spin_lock_irqsave(&cam->dev_lock, flags);
	cafe_ctlr_stop(cam);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	mdelay(1);
	wait_event_timeout(cam->iowait,
			!test_bit(CF_DMA_ACTIVE, &cam->flags), HZ);
	if (test_bit(CF_DMA_ACTIVE, &cam->flags))
		cam_err(cam, "Timeout waiting for DMA to end\n");
		/* This would be bad news - what now? */
	spin_lock_irqsave(&cam->dev_lock, flags);
	cam->state = S_IDLE;
	cafe_ctlr_irq_disable(cam);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
}