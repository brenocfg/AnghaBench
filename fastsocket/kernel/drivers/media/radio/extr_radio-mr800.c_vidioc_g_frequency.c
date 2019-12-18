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
struct v4l2_frequency {int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct amradio_device {int /*<<< orphan*/  curfreq; scalar_t__ removed; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct amradio_device* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
				struct v4l2_frequency *f)
{
	struct amradio_device *radio = video_get_drvdata(video_devdata(file));

	/* safety check */
	if (radio->removed)
		return -EIO;

	f->type = V4L2_TUNER_RADIO;
	f->frequency = radio->curfreq;
	return 0;
}