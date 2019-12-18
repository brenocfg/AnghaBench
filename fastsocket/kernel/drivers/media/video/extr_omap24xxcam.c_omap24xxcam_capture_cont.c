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
struct omap24xxcam_device {int /*<<< orphan*/  core_enable_disable_lock; int /*<<< orphan*/  in_reset; scalar_t__ sgdma_in_queue; int /*<<< orphan*/  sgdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap24xxcam_core_enable (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_hwinit (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_sensor_if_enable (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_sgdma_process (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void omap24xxcam_capture_cont(struct omap24xxcam_device *cam)
{
	unsigned long flags;

	spin_lock_irqsave(&cam->core_enable_disable_lock, flags);

	if (atomic_read(&cam->in_reset) != 1)
		goto out;

	omap24xxcam_hwinit(cam);

	omap24xxcam_sensor_if_enable(cam);

	omap24xxcam_sgdma_process(&cam->sgdma);

	if (cam->sgdma_in_queue)
		omap24xxcam_core_enable(cam);

out:
	atomic_dec(&cam->in_reset);
	spin_unlock_irqrestore(&cam->core_enable_disable_lock, flags);
}