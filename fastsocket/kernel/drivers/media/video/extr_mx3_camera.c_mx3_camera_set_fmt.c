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
struct v4l2_subdev {int dummy; } ;
struct v4l2_pix_format {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_3__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct soc_camera_host {struct mx3_camera_dev* priv; } ;
struct soc_camera_format_xlate {int /*<<< orphan*/  host_fmt; int /*<<< orphan*/  buswidth; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {TYPE_2__ dev; int /*<<< orphan*/  current_fmt; int /*<<< orphan*/  buswidth; } ;
struct mx3_camera_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int acquire_dma_channel (struct mx3_camera_dev*) ; 
 int /*<<< orphan*/  configure_geometry (struct mx3_camera_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_fmt ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 struct soc_camera_format_xlate* soc_camera_xlate_by_fourcc (struct soc_camera_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stride_align (int /*<<< orphan*/ *) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_format*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int mx3_camera_set_fmt(struct soc_camera_device *icd,
			      struct v4l2_format *f)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct mx3_camera_dev *mx3_cam = ici->priv;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	const struct soc_camera_format_xlate *xlate;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	int ret;

	xlate = soc_camera_xlate_by_fourcc(icd, pix->pixelformat);
	if (!xlate) {
		dev_warn(icd->dev.parent, "Format %x not found\n",
			 pix->pixelformat);
		return -EINVAL;
	}

	stride_align(&pix->width);
	dev_dbg(icd->dev.parent, "Set format %dx%d\n", pix->width, pix->height);

	ret = acquire_dma_channel(mx3_cam);
	if (ret < 0)
		return ret;

	/*
	 * Might have to perform a complete interface initialisation like in
	 * ipu_csi_init_interface() in mxc_v4l2_s_param(). Also consider
	 * mxc_v4l2_s_fmt()
	 */

	configure_geometry(mx3_cam, pix->width, pix->height);

	ret = v4l2_subdev_call(sd, video, s_fmt, f);
	if (!ret) {
		icd->buswidth = xlate->buswidth;
		icd->current_fmt = xlate->host_fmt;
	}

	dev_dbg(icd->dev.parent, "Sensor set %dx%d\n", pix->width, pix->height);

	return ret;
}