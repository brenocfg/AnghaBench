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
struct pwc_device {scalar_t__ tilt_angle; scalar_t__ pan_angle; } ;

/* Variables and functions */
 int _pwc_mpt_reset (struct pwc_device*,int) ; 

int pwc_mpt_reset(struct pwc_device *pdev, int flags)
{
	int ret;
	ret = _pwc_mpt_reset(pdev, flags);
	if (ret >= 0) {
		pdev->pan_angle = 0;
		pdev->tilt_angle = 0;
	}
	return ret;
}