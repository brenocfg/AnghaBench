#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct soc_camera_host {int dummy; } ;
struct soc_camera_format_xlate {int buswidth; TYPE_2__* cam_fmt; TYPE_2__* host_fmt; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {TYPE_2__* formats; TYPE_1__ dev; } ;
struct TYPE_4__ {int depth; int fourcc; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  V4L2_PIX_FMT_SGRBG10 129 
#define  V4L2_PIX_FMT_Y16 128 
 int /*<<< orphan*/  buswidth_supported (struct soc_camera_host*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 TYPE_2__* mx3_camera_formats ; 
 int mx3_camera_try_bus_param (struct soc_camera_device*,int) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mx3_camera_get_formats(struct soc_camera_device *icd, int idx,
				  struct soc_camera_format_xlate *xlate)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	int formats = 0, buswidth, ret;

	buswidth = icd->formats[idx].depth;

	if (!buswidth_supported(ici, buswidth))
		return 0;

	ret = mx3_camera_try_bus_param(icd, buswidth);
	if (ret < 0)
		return 0;

	switch (icd->formats[idx].fourcc) {
	case V4L2_PIX_FMT_SGRBG10:
		formats++;
		if (xlate) {
			xlate->host_fmt = &mx3_camera_formats[0];
			xlate->cam_fmt = icd->formats + idx;
			xlate->buswidth = buswidth;
			xlate++;
			dev_dbg(icd->dev.parent,
				"Providing format %s using %s\n",
				mx3_camera_formats[0].name,
				icd->formats[idx].name);
		}
		goto passthrough;
	case V4L2_PIX_FMT_Y16:
		formats++;
		if (xlate) {
			xlate->host_fmt = &mx3_camera_formats[1];
			xlate->cam_fmt = icd->formats + idx;
			xlate->buswidth = buswidth;
			xlate++;
			dev_dbg(icd->dev.parent,
				"Providing format %s using %s\n",
				mx3_camera_formats[0].name,
				icd->formats[idx].name);
		}
	default:
passthrough:
		/* Generic pass-through */
		formats++;
		if (xlate) {
			xlate->host_fmt = icd->formats + idx;
			xlate->cam_fmt = icd->formats + idx;
			xlate->buswidth = buswidth;
			xlate++;
			dev_dbg(icd->dev.parent,
				"Providing format %s in pass-through mode\n",
				icd->formats[idx].name);
		}
	}

	return formats;
}