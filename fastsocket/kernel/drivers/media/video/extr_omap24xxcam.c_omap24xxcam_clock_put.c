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
struct omap24xxcam_device {int /*<<< orphan*/ * fck; int /*<<< orphan*/ * ick; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap24xxcam_clock_put(struct omap24xxcam_device *cam)
{
	if (cam->ick != NULL && !IS_ERR(cam->ick))
		clk_put(cam->ick);
	if (cam->fck != NULL && !IS_ERR(cam->fck))
		clk_put(cam->fck);

	cam->ick = cam->fck = NULL;
}