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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {int user_height; TYPE_2__ dev; TYPE_1__* current_fmt; int /*<<< orphan*/  user_width; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int soc_mbus_bytes_per_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vid_limit ; 

__attribute__((used)) static int pxa_videobuf_setup(struct videobuf_queue *vq, unsigned int *count,
			      unsigned int *size)
{
	struct soc_camera_device *icd = vq->priv_data;
	int bytes_per_line = soc_mbus_bytes_per_line(icd->user_width,
						icd->current_fmt->host_fmt);

	if (bytes_per_line < 0)
		return bytes_per_line;

	dev_dbg(icd->dev.parent, "count=%d, size=%d\n", *count, *size);

	*size = bytes_per_line * icd->user_height;

	if (0 == *count)
		*count = 32;
	if (*size * *count > vid_limit * 1024 * 1024)
		*count = (vid_limit * 1024 * 1024) / *size;

	return 0;
}