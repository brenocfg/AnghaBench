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
struct omap24xxcam_device {void* ick; int /*<<< orphan*/  dev; void* fck; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap24xxcam_clock_put (struct omap24xxcam_device*) ; 

__attribute__((used)) static int omap24xxcam_clock_get(struct omap24xxcam_device *cam)
{
	int rval = 0;

	cam->fck = clk_get(cam->dev, "fck");
	if (IS_ERR(cam->fck)) {
		dev_err(cam->dev, "can't get camera fck");
		rval = PTR_ERR(cam->fck);
		omap24xxcam_clock_put(cam);
		return rval;
	}

	cam->ick = clk_get(cam->dev, "ick");
	if (IS_ERR(cam->ick)) {
		dev_err(cam->dev, "can't get camera ick");
		rval = PTR_ERR(cam->ick);
		omap24xxcam_clock_put(cam);
	}

	return rval;
}