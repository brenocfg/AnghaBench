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
struct cafe_camera {scalar_t__ nbufs; int state; int /*<<< orphan*/  dev_lock; } ;
typedef  enum cafe_state { ____Placeholder_cafe_state } cafe_state ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ cafe_alloc_dma_bufs (struct cafe_camera*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_cam_configure (struct cafe_camera*) ; 
 int cafe_ctlr_configure (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_ctlr_irq_enable (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_ctlr_start (struct cafe_camera*) ; 
 scalar_t__ cafe_needs_config (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_reset_buffers (struct cafe_camera*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cafe_read_setup(struct cafe_camera *cam, enum cafe_state state)
{
	int ret;
	unsigned long flags;

	/*
	 * Configuration.  If we still don't have DMA buffers,
	 * make one last, desperate attempt.
	 */
	if (cam->nbufs == 0)
		if (cafe_alloc_dma_bufs(cam, 0))
			return -ENOMEM;

	if (cafe_needs_config(cam)) {
		cafe_cam_configure(cam);
		ret = cafe_ctlr_configure(cam);
		if (ret)
			return ret;
	}

	/*
	 * Turn it loose.
	 */
	spin_lock_irqsave(&cam->dev_lock, flags);
	cafe_reset_buffers(cam);
	cafe_ctlr_irq_enable(cam);
	cam->state = state;
	cafe_ctlr_start(cam);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	return 0;
}