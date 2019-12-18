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
struct v4l2_subdev {int dummy; } ;
struct soc_mbus_pixelfmt {int /*<<< orphan*/  name; int /*<<< orphan*/  bits_per_sample; } ;
struct soc_camera_format_xlate {int code; struct soc_mbus_pixelfmt const* host_fmt; } ;
struct TYPE_2__ {struct device* parent; } ;
struct soc_camera_device {struct pxa_cam* host_priv; TYPE_1__ dev; } ;
struct pxa_cam {int dummy; } ;
struct device {int dummy; } ;
typedef  enum v4l2_mbus_pixelcode { ____Placeholder_v4l2_mbus_pixelcode } v4l2_mbus_pixelcode ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  V4L2_MBUS_FMT_RGB555_2X8_PADHI_LE 133 
#define  V4L2_MBUS_FMT_RGB565_2X8_LE 132 
#define  V4L2_MBUS_FMT_UYVY8_2X8 131 
#define  V4L2_MBUS_FMT_VYUY8_2X8 130 
#define  V4L2_MBUS_FMT_YUYV8_2X8 129 
#define  V4L2_MBUS_FMT_YVYU8_2X8 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int,int) ; 
 int /*<<< orphan*/  enum_mbus_fmt ; 
 struct pxa_cam* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct soc_mbus_pixelfmt const* pxa_camera_formats ; 
 int /*<<< orphan*/  pxa_camera_packing_supported (struct soc_mbus_pixelfmt const*) ; 
 int pxa_camera_try_bus_param (struct soc_camera_device*,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 struct soc_mbus_pixelfmt* soc_mbus_get_fmtdesc (int) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int pxa_camera_get_formats(struct soc_camera_device *icd, unsigned int idx,
				  struct soc_camera_format_xlate *xlate)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct device *dev = icd->dev.parent;
	int formats = 0, ret;
	struct pxa_cam *cam;
	enum v4l2_mbus_pixelcode code;
	const struct soc_mbus_pixelfmt *fmt;

	ret = v4l2_subdev_call(sd, video, enum_mbus_fmt, idx, &code);
	if (ret < 0)
		/* No more formats */
		return 0;

	fmt = soc_mbus_get_fmtdesc(code);
	if (!fmt) {
		dev_err(dev, "Invalid format code #%u: %d\n", idx, code);
		return 0;
	}

	/* This also checks support for the requested bits-per-sample */
	ret = pxa_camera_try_bus_param(icd, fmt->bits_per_sample);
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

	switch (code) {
	case V4L2_MBUS_FMT_UYVY8_2X8:
		formats++;
		if (xlate) {
			xlate->host_fmt	= &pxa_camera_formats[0];
			xlate->code	= code;
			xlate++;
			dev_dbg(dev, "Providing format %s using code %d\n",
				pxa_camera_formats[0].name, code);
		}
	case V4L2_MBUS_FMT_VYUY8_2X8:
	case V4L2_MBUS_FMT_YUYV8_2X8:
	case V4L2_MBUS_FMT_YVYU8_2X8:
	case V4L2_MBUS_FMT_RGB565_2X8_LE:
	case V4L2_MBUS_FMT_RGB555_2X8_PADHI_LE:
		if (xlate)
			dev_dbg(dev, "Providing format %s packed\n",
				fmt->name);
		break;
	default:
		if (!pxa_camera_packing_supported(fmt))
			return 0;
		if (xlate)
			dev_dbg(dev,
				"Providing format %s in pass-through mode\n",
				fmt->name);
	}

	/* Generic pass-through */
	formats++;
	if (xlate) {
		xlate->host_fmt	= fmt;
		xlate->code	= code;
		xlate++;
	}

	return formats;
}