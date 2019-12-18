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
struct v4l2_queryctrl {int id; int /*<<< orphan*/  flags; } ;
struct si470x_device {TYPE_1__* videodev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_MUTE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int V4L2_CID_BASE ; 
 int V4L2_CID_LASTP1 ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_DISABLED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int v4l2_ctrl_query_fill (struct v4l2_queryctrl*,int /*<<< orphan*/ ,int,int,int) ; 
 struct si470x_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int si470x_vidioc_queryctrl(struct file *file, void *priv,
		struct v4l2_queryctrl *qc)
{
	struct si470x_device *radio = video_drvdata(file);
	int retval = -EINVAL;

	/* abort if qc->id is below V4L2_CID_BASE */
	if (qc->id < V4L2_CID_BASE)
		goto done;

	/* search video control */
	switch (qc->id) {
	case V4L2_CID_AUDIO_VOLUME:
		return v4l2_ctrl_query_fill(qc, 0, 15, 1, 15);
	case V4L2_CID_AUDIO_MUTE:
		return v4l2_ctrl_query_fill(qc, 0, 1, 1, 1);
	}

	/* disable unsupported base controls */
	/* to satisfy kradio and such apps */
	if ((retval == -EINVAL) && (qc->id < V4L2_CID_LASTP1)) {
		qc->flags = V4L2_CTRL_FLAG_DISABLED;
		retval = 0;
	}

done:
	if (retval < 0)
		dev_warn(&radio->videodev->dev,
			"query controls failed with %d\n", retval);
	return retval;
}