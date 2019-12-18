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
struct video_device {int vfl_type; int minor; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/  release; int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSM_APPS_ID_V4L2 ; 
 TYPE_1__* g_pmsm_v4l2_dev ; 
 int /*<<< orphan*/  msm_ioctl_ops ; 
 int /*<<< orphan*/  msm_v4l2_fops ; 
 int msm_v4l2_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_v4l2_release_dev ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int msm_v4l2_video_dev_init(struct video_device *pvd)
{
	strncpy(pvd->name, MSM_APPS_ID_V4L2, sizeof(pvd->name));
	pvd->vfl_type = 1;
	pvd->fops = &msm_v4l2_fops;
	pvd->release = msm_v4l2_release_dev;
	pvd->minor = -1;
	pvd->ioctl_ops = &msm_ioctl_ops;
	return msm_v4l2_register(g_pmsm_v4l2_dev->drv);
}