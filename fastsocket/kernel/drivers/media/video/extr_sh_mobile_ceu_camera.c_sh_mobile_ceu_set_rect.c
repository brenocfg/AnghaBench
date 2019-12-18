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
typedef  unsigned int u32 ;
struct v4l2_rect {unsigned int width; unsigned int height; unsigned int left; unsigned int top; } ;
struct soc_camera_host {struct sh_mobile_ceu_dev* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {TYPE_2__ dev; TYPE_1__* current_fmt; struct sh_mobile_ceu_cam* host_priv; } ;
struct sh_mobile_ceu_dev {scalar_t__ is_interlaced; int /*<<< orphan*/  is_16bit; scalar_t__ image_mode; } ;
struct sh_mobile_ceu_cam {struct v4l2_rect ceu_rect; } ;
struct TYPE_3__ {int depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAMOR ; 
 int /*<<< orphan*/  CAPWR ; 
 int /*<<< orphan*/  CDWDR ; 
 int /*<<< orphan*/  CFSZR ; 
 int /*<<< orphan*/  ceu_write (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_geo (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_mobile_ceu_set_rect(struct soc_camera_device *icd,
				   unsigned int out_width,
				   unsigned int out_height)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct sh_mobile_ceu_cam *cam = icd->host_priv;
	struct v4l2_rect *rect = &cam->ceu_rect;
	struct sh_mobile_ceu_dev *pcdev = ici->priv;
	unsigned int height, width, cdwdr_width, in_width, in_height;
	unsigned int left_offset, top_offset;
	u32 camor;

	dev_dbg(icd->dev.parent, "Crop %ux%u@%u:%u\n",
		rect->width, rect->height, rect->left, rect->top);

	left_offset	= rect->left;
	top_offset	= rect->top;

	if (pcdev->image_mode) {
		in_width = rect->width;
		if (!pcdev->is_16bit) {
			in_width *= 2;
			left_offset *= 2;
		}
		width = cdwdr_width = out_width;
	} else {
		unsigned int w_factor = (icd->current_fmt->depth + 7) >> 3;

		width = out_width * w_factor / 2;

		if (!pcdev->is_16bit)
			w_factor *= 2;

		in_width = rect->width * w_factor / 2;
		left_offset = left_offset * w_factor / 2;

		cdwdr_width = width * 2;
	}

	height = out_height;
	in_height = rect->height;
	if (pcdev->is_interlaced) {
		height /= 2;
		in_height /= 2;
		top_offset /= 2;
		cdwdr_width *= 2;
	}

	/* Set CAMOR, CAPWR, CFSZR, take care of CDWDR */
	camor = left_offset | (top_offset << 16);

	dev_geo(icd->dev.parent,
		"CAMOR 0x%x, CAPWR 0x%x, CFSZR 0x%x, CDWDR 0x%x\n", camor,
		(in_height << 16) | in_width, (height << 16) | width,
		cdwdr_width);

	ceu_write(pcdev, CAMOR, camor);
	ceu_write(pcdev, CAPWR, (in_height << 16) | in_width);
	ceu_write(pcdev, CFSZR, (height << 16) | width);
	ceu_write(pcdev, CDWDR, cdwdr_width);
}