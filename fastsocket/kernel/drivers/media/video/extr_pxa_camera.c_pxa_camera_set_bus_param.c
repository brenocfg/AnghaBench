#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct soc_mbus_pixelfmt {int /*<<< orphan*/  bits_per_sample; } ;
struct soc_camera_host {struct pxa_camera_dev* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {TYPE_3__* ops; TYPE_2__* current_fmt; struct pxa_cam* host_priv; TYPE_1__ dev; } ;
struct pxa_camera_dev {int channels; int platform_flags; } ;
struct pxa_cam {unsigned long flags; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_6__ {unsigned long (* query_bus_param ) (struct soc_camera_device*) ;int (* set_bus_param ) (struct soc_camera_device*,unsigned long) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int EINVAL ; 
 int PXA_CAMERA_HSP ; 
 int PXA_CAMERA_PCP ; 
 int PXA_CAMERA_VSP ; 
 unsigned long SOCAM_HSYNC_ACTIVE_HIGH ; 
 unsigned long SOCAM_HSYNC_ACTIVE_LOW ; 
 unsigned long SOCAM_PCLK_SAMPLE_FALLING ; 
 unsigned long SOCAM_PCLK_SAMPLE_RISING ; 
 unsigned long SOCAM_VSYNC_ACTIVE_HIGH ; 
 unsigned long SOCAM_VSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  pxa_camera_setup_cicr (struct soc_camera_device*,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long soc_camera_bus_param_compatible (unsigned long,unsigned long) ; 
 struct soc_mbus_pixelfmt* soc_mbus_get_fmtdesc (int /*<<< orphan*/ ) ; 
 unsigned long stub1 (struct soc_camera_device*) ; 
 int stub2 (struct soc_camera_device*,unsigned long) ; 
 int test_platform_param (struct pxa_camera_dev*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa_camera_set_bus_param(struct soc_camera_device *icd, __u32 pixfmt)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct pxa_camera_dev *pcdev = ici->priv;
	unsigned long bus_flags, camera_flags, common_flags;
	const struct soc_mbus_pixelfmt *fmt;
	int ret;
	struct pxa_cam *cam = icd->host_priv;

	fmt = soc_mbus_get_fmtdesc(icd->current_fmt->code);
	if (!fmt)
		return -EINVAL;

	ret = test_platform_param(pcdev, fmt->bits_per_sample, &bus_flags);
	if (ret < 0)
		return ret;

	camera_flags = icd->ops->query_bus_param(icd);

	common_flags = soc_camera_bus_param_compatible(camera_flags, bus_flags);
	if (!common_flags)
		return -EINVAL;

	pcdev->channels = 1;

	/* Make choises, based on platform preferences */
	if ((common_flags & SOCAM_HSYNC_ACTIVE_HIGH) &&
	    (common_flags & SOCAM_HSYNC_ACTIVE_LOW)) {
		if (pcdev->platform_flags & PXA_CAMERA_HSP)
			common_flags &= ~SOCAM_HSYNC_ACTIVE_HIGH;
		else
			common_flags &= ~SOCAM_HSYNC_ACTIVE_LOW;
	}

	if ((common_flags & SOCAM_VSYNC_ACTIVE_HIGH) &&
	    (common_flags & SOCAM_VSYNC_ACTIVE_LOW)) {
		if (pcdev->platform_flags & PXA_CAMERA_VSP)
			common_flags &= ~SOCAM_VSYNC_ACTIVE_HIGH;
		else
			common_flags &= ~SOCAM_VSYNC_ACTIVE_LOW;
	}

	if ((common_flags & SOCAM_PCLK_SAMPLE_RISING) &&
	    (common_flags & SOCAM_PCLK_SAMPLE_FALLING)) {
		if (pcdev->platform_flags & PXA_CAMERA_PCP)
			common_flags &= ~SOCAM_PCLK_SAMPLE_RISING;
		else
			common_flags &= ~SOCAM_PCLK_SAMPLE_FALLING;
	}

	cam->flags = common_flags;

	ret = icd->ops->set_bus_param(icd, common_flags);
	if (ret < 0)
		return ret;

	pxa_camera_setup_cicr(icd, common_flags, pixfmt);

	return 0;
}