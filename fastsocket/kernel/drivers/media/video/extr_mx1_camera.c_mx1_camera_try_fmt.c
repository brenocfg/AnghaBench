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
struct v4l2_format {int dummy; } ;
struct soc_camera_device {int dummy; } ;

/* Variables and functions */
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 int /*<<< orphan*/  try_fmt ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_format*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int mx1_camera_try_fmt(struct soc_camera_device *icd,
			      struct v4l2_format *f)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	/* TODO: limit to mx1 hardware capabilities */

	/* limit to sensor capabilities */
	return v4l2_subdev_call(sd, video, try_fmt, f);
}