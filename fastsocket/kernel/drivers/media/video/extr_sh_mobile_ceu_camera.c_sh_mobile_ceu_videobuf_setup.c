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
struct soc_camera_host {struct sh_mobile_ceu_dev* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {int user_width; int user_height; TYPE_2__ dev; TYPE_1__* current_fmt; } ;
struct sh_mobile_ceu_dev {int video_limit; } ;
struct TYPE_3__ {int depth; } ;

/* Variables and functions */
 unsigned int PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mobile_ceu_videobuf_setup(struct videobuf_queue *vq,
					unsigned int *count,
					unsigned int *size)
{
	struct soc_camera_device *icd = vq->priv_data;
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct sh_mobile_ceu_dev *pcdev = ici->priv;
	int bytes_per_pixel = (icd->current_fmt->depth + 7) >> 3;

	*size = PAGE_ALIGN(icd->user_width * icd->user_height *
			   bytes_per_pixel);

	if (0 == *count)
		*count = 2;

	if (pcdev->video_limit) {
		while (*size * *count > pcdev->video_limit)
			(*count)--;
	}

	dev_dbg(icd->dev.parent, "count=%d, size=%d\n", *count, *size);

	return 0;
}