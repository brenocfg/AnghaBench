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
struct omap24xxcam_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  in_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap24xxcam_reset (struct omap24xxcam_device*) ; 

__attribute__((used)) static void omap24xxcam_stalled_dma_reset(unsigned long data)
{
	struct omap24xxcam_device *cam = (struct omap24xxcam_device *)data;

	if (!atomic_read(&cam->in_reset)) {
		dev_dbg(cam->dev, "dma stalled, resetting camera\n");
		omap24xxcam_reset(cam);
	}
}