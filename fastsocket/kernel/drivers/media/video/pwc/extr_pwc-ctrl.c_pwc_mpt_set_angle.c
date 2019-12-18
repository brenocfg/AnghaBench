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
struct TYPE_2__ {int pan_min; int pan_max; int tilt_min; int tilt_max; } ;
struct pwc_device {scalar_t__ tilt_angle; scalar_t__ pan_angle; TYPE_1__ angle_range; } ;

/* Variables and functions */
 int EPIPE ; 
 int ERANGE ; 
 int _pwc_mpt_set_angle (struct pwc_device*,int,int) ; 

int pwc_mpt_set_angle(struct pwc_device *pdev, int pan, int tilt)
{
	int ret;

	/* check absolute ranges */
	if (pan  < pdev->angle_range.pan_min  ||
	    pan  > pdev->angle_range.pan_max  ||
	    tilt < pdev->angle_range.tilt_min ||
	    tilt > pdev->angle_range.tilt_max)
		return -ERANGE;

	/* go to relative range, check again */
	pan  -= pdev->pan_angle;
	tilt -= pdev->tilt_angle;
	/* angles are specified in degrees * 100, thus the limit = 36000 */
	if (pan < -36000 || pan > 36000 || tilt < -36000 || tilt > 36000)
		return -ERANGE;

	ret = _pwc_mpt_set_angle(pdev, pan, tilt);
	if (ret >= 0) {
		pdev->pan_angle  += pan;
		pdev->tilt_angle += tilt;
	}
	if (ret == -EPIPE) /* stall -> out of range */
		ret = -ERANGE;
	return ret;
}