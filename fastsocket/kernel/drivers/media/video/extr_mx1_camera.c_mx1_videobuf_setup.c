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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {int user_width; int user_height; TYPE_1__ dev; TYPE_2__* current_fmt; } ;
struct TYPE_4__ {int depth; } ;

/* Variables and functions */
 int MAX_VIDEO_MEM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int mx1_videobuf_setup(struct videobuf_queue *vq, unsigned int *count,
			      unsigned int *size)
{
	struct soc_camera_device *icd = vq->priv_data;

	*size = icd->user_width * icd->user_height *
		((icd->current_fmt->depth + 7) >> 3);

	if (!*count)
		*count = 32;

	while (*size * *count > MAX_VIDEO_MEM * 1024 * 1024)
		(*count)--;

	dev_dbg(icd->dev.parent, "count=%d, size=%d\n", *count, *size);

	return 0;
}