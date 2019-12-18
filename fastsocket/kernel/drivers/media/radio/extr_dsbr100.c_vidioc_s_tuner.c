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
struct v4l2_tuner {scalar_t__ index; } ;
struct file {int dummy; } ;
struct dsbr100_device {scalar_t__ removed; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 struct dsbr100_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_tuner(struct file *file, void *priv,
				struct v4l2_tuner *v)
{
	struct dsbr100_device *radio = video_drvdata(file);

	/* safety check */
	if (radio->removed)
		return -EIO;

	if (v->index > 0)
		return -EINVAL;

	return 0;
}