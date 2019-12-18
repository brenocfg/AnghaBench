#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct meye_params {int subsample; int quality; int sharpness; int agc; int picture; int framerate; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct meye_params params; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERAAGC ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERAPICTURE ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERASHARPNESS ; 
 int /*<<< orphan*/  mchip_hic_stop () ; 
 TYPE_1__ meye ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sony_pic_camera_command (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int meyeioc_s_params(struct meye_params *jp)
{
	if (jp->subsample > 1)
		return -EINVAL;

	if (jp->quality > 10)
		return -EINVAL;

	if (jp->sharpness > 63 || jp->agc > 63 || jp->picture > 63)
		return -EINVAL;

	if (jp->framerate > 31)
		return -EINVAL;

	mutex_lock(&meye.lock);

	if (meye.params.subsample != jp->subsample ||
	    meye.params.quality != jp->quality)
		mchip_hic_stop();	/* need restart */

	meye.params = *jp;
	sony_pic_camera_command(SONY_PIC_COMMAND_SETCAMERASHARPNESS,
			      meye.params.sharpness);
	sony_pic_camera_command(SONY_PIC_COMMAND_SETCAMERAAGC,
			      meye.params.agc);
	sony_pic_camera_command(SONY_PIC_COMMAND_SETCAMERAPICTURE,
			      meye.params.picture);
	mutex_unlock(&meye.lock);

	return 0;
}