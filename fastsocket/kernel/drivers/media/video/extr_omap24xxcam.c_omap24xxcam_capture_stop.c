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
struct omap24xxcam_device {int /*<<< orphan*/  sgdma; int /*<<< orphan*/  core_enable_disable_lock; int /*<<< orphan*/  in_reset; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap24xxcam_core_disable (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_sgdma_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void omap24xxcam_capture_stop(struct omap24xxcam_device *cam)
{
	unsigned long flags;

	spin_lock_irqsave(&cam->core_enable_disable_lock, flags);

	if (atomic_inc_return(&cam->in_reset) != 1) {
		spin_unlock_irqrestore(&cam->core_enable_disable_lock, flags);
		return;
	}

	omap24xxcam_core_disable(cam);

	spin_unlock_irqrestore(&cam->core_enable_disable_lock, flags);

	omap24xxcam_sgdma_sync(&cam->sgdma);
}