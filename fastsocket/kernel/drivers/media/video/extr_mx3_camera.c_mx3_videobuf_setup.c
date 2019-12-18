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
struct videobuf_queue {struct soc_camera_device* priv_data; } ;
struct soc_camera_host {struct mx3_camera_dev* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {unsigned int user_width; unsigned int user_height; TYPE_2__* current_fmt; TYPE_1__ dev; } ;
struct mx3_camera_dev {int /*<<< orphan*/ * idmac_channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int MAX_VIDEO_MEM ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mx3_videobuf_setup(struct videobuf_queue *vq, unsigned int *count,
			      unsigned int *size)
{
	struct soc_camera_device *icd = vq->priv_data;
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct mx3_camera_dev *mx3_cam = ici->priv;
	/*
	 * bits-per-pixel (depth) as specified in camera's pixel format does
	 * not necessarily match what the camera interface writes to RAM, but
	 * it should be good enough for now.
	 */
	unsigned int bpp = DIV_ROUND_UP(icd->current_fmt->depth, 8);

	if (!mx3_cam->idmac_channel[0])
		return -EINVAL;

	*size = icd->user_width * icd->user_height * bpp;

	if (!*count)
		*count = 32;

	if (*size * *count > MAX_VIDEO_MEM * 1024 * 1024)
		*count = MAX_VIDEO_MEM * 1024 * 1024 / *size;

	return 0;
}