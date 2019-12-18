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
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct poseidon {int /*<<< orphan*/  lock; struct file* file_for_stream; } ;
struct front_face {struct poseidon* pd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  logs (struct front_face*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pd_vidioc_s_fmt (struct poseidon*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_s_fmt(struct file *file, void *fh, struct v4l2_format *f)
{
	struct front_face *front	= fh;
	struct poseidon *pd		= front->pd;

	logs(front);
	/* stop VBI here */
	if (V4L2_BUF_TYPE_VIDEO_CAPTURE != f->type)
		return -EINVAL;

	mutex_lock(&pd->lock);
	if (pd->file_for_stream == NULL)
		pd->file_for_stream = file;
	else if (file != pd->file_for_stream) {
		mutex_unlock(&pd->lock);
		return -EINVAL;
	}

	pd_vidioc_s_fmt(pd, &f->fmt.pix);
	mutex_unlock(&pd->lock);
	return 0;
}