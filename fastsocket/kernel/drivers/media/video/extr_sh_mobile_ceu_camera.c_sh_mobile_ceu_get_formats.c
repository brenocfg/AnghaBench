#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct soc_camera_format_xlate {int /*<<< orphan*/  buswidth; TYPE_2__* cam_fmt; TYPE_2__* host_fmt; } ;
struct TYPE_4__ {struct device* parent; } ;
struct soc_camera_device {TYPE_2__* formats; struct sh_mobile_ceu_cam* host_priv; TYPE_1__ dev; } ;
struct sh_mobile_ceu_cam {int /*<<< orphan*/ * extra_fmt; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int fourcc; int /*<<< orphan*/  name; int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  V4L2_PIX_FMT_UYVY 131 
#define  V4L2_PIX_FMT_VYUY 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVYU 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 struct sh_mobile_ceu_cam* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* sh_mobile_ceu_formats ; 
 int sh_mobile_ceu_try_bus_param (struct soc_camera_device*) ; 

__attribute__((used)) static int sh_mobile_ceu_get_formats(struct soc_camera_device *icd, int idx,
				     struct soc_camera_format_xlate *xlate)
{
	struct device *dev = icd->dev.parent;
	int ret, k, n;
	int formats = 0;
	struct sh_mobile_ceu_cam *cam;

	ret = sh_mobile_ceu_try_bus_param(icd);
	if (ret < 0)
		return 0;

	if (!icd->host_priv) {
		cam = kzalloc(sizeof(*cam), GFP_KERNEL);
		if (!cam)
			return -ENOMEM;

		icd->host_priv = cam;
	} else {
		cam = icd->host_priv;
	}

	/* Beginning of a pass */
	if (!idx)
		cam->extra_fmt = NULL;

	switch (icd->formats[idx].fourcc) {
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_VYUY:
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_YVYU:
		if (cam->extra_fmt)
			goto add_single_format;

		/*
		 * Our case is simple so far: for any of the above four camera
		 * formats we add all our four synthesized NV* formats, so,
		 * just marking the device with a single flag suffices. If
		 * the format generation rules are more complex, you would have
		 * to actually hang your already added / counted formats onto
		 * the host_priv pointer and check whether the format you're
		 * going to add now is already there.
		 */
		cam->extra_fmt = (void *)sh_mobile_ceu_formats;

		n = ARRAY_SIZE(sh_mobile_ceu_formats);
		formats += n;
		for (k = 0; xlate && k < n; k++) {
			xlate->host_fmt = &sh_mobile_ceu_formats[k];
			xlate->cam_fmt = icd->formats + idx;
			xlate->buswidth = icd->formats[idx].depth;
			xlate++;
			dev_dbg(dev, "Providing format %s using %s\n",
				sh_mobile_ceu_formats[k].name,
				icd->formats[idx].name);
		}
	default:
add_single_format:
		/* Generic pass-through */
		formats++;
		if (xlate) {
			xlate->host_fmt = icd->formats + idx;
			xlate->cam_fmt = icd->formats + idx;
			xlate->buswidth = icd->formats[idx].depth;
			xlate++;
			dev_dbg(dev,
				"Providing format %s in pass-through mode\n",
				icd->formats[idx].name);
		}
	}

	return formats;
}