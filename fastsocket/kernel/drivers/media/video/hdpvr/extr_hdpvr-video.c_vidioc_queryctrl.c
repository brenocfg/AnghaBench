#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct v4l2_queryctrl {int id; } ;
struct hdpvr_fh {struct hdpvr_device* dev; } ;
struct hdpvr_device {int flags; int /*<<< orphan*/  options; } ;
struct file {struct hdpvr_fh* private_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int HDPVR_FLAG_AC3_CAP ; 
 int V4L2_CTRL_FLAG_NEXT_CTRL ; 
 int fill_queryctrl (int /*<<< orphan*/ *,struct v4l2_queryctrl*,int) ; 
 int /*<<< orphan*/  memset (struct v4l2_queryctrl*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* supported_v4l2_ctrls ; 

__attribute__((used)) static int vidioc_queryctrl(struct file *file, void *private_data,
			    struct v4l2_queryctrl *qc)
{
	struct hdpvr_fh *fh = file->private_data;
	struct hdpvr_device *dev = fh->dev;
	int i, next;
	u32 id = qc->id;

	memset(qc, 0, sizeof(*qc));

	next = !!(id &  V4L2_CTRL_FLAG_NEXT_CTRL);
	qc->id = id & ~V4L2_CTRL_FLAG_NEXT_CTRL;

	for (i = 0; i < ARRAY_SIZE(supported_v4l2_ctrls); i++) {
		if (next) {
			if (qc->id < supported_v4l2_ctrls[i])
				qc->id = supported_v4l2_ctrls[i];
			else
				continue;
		}

		if (qc->id == supported_v4l2_ctrls[i])
			return fill_queryctrl(&dev->options, qc,
					      dev->flags & HDPVR_FLAG_AC3_CAP);

		if (qc->id < supported_v4l2_ctrls[i])
			break;
	}

	return -EINVAL;
}