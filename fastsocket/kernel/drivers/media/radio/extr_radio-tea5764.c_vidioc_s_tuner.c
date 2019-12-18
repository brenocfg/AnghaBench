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
struct v4l2_tuner {scalar_t__ index; int /*<<< orphan*/  audmode; } ;
struct tea5764_device {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  tea5764_set_audout_mode (struct tea5764_device*,int /*<<< orphan*/ ) ; 
 struct tea5764_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_tuner(struct file *file, void *priv,
				struct v4l2_tuner *v)
{
	struct tea5764_device *radio = video_drvdata(file);

	if (v->index > 0)
		return -EINVAL;

	tea5764_set_audout_mode(radio, v->audmode);
	return 0;
}