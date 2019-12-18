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
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int dummy; } ;
struct v4l2_cropcap {struct v4l2_rect defrect; void* type; struct v4l2_rect c; } ;
struct v4l2_crop {struct v4l2_rect defrect; void* type; struct v4l2_rect c; } ;

/* Variables and functions */
 void* V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  cropcap ; 
 int /*<<< orphan*/  g_crop ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_cropcap*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int client_g_rect(struct v4l2_subdev *sd, struct v4l2_rect *rect)
{
	struct v4l2_crop crop;
	struct v4l2_cropcap cap;
	int ret;

	crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	ret = v4l2_subdev_call(sd, video, g_crop, &crop);
	if (!ret) {
		*rect = crop.c;
		return ret;
	}

	/* Camera driver doesn't support .g_crop(), assume default rectangle */
	cap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	ret = v4l2_subdev_call(sd, video, cropcap, &cap);
	if (ret < 0)
		return ret;

	*rect = cap.defrect;

	return ret;
}