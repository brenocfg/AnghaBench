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
struct v4l2_rect {int width; int height; } ;
struct soc_camera_host {struct mx3_camera_dev* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {int user_width; int user_height; TYPE_1__ dev; } ;
struct mx3_camera_dev {struct idmac_channel** idmac_channel; } ;
struct idmac_channel {int dummy; } ;

/* Variables and functions */
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool channel_change_requested(struct soc_camera_device *icd,
				     struct v4l2_rect *rect)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct mx3_camera_dev *mx3_cam = ici->priv;
	struct idmac_channel *ichan = mx3_cam->idmac_channel[0];

	/* Do buffers have to be re-allocated or channel re-configured? */
	return ichan && rect->width * rect->height >
		icd->user_width * icd->user_height;
}