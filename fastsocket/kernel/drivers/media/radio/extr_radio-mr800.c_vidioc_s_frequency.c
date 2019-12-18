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
struct v4l2_frequency {int /*<<< orphan*/  frequency; } ;
struct file {int dummy; } ;
struct amradio_device {TYPE_1__* videodev; int /*<<< orphan*/  curfreq; int /*<<< orphan*/  lock; scalar_t__ removed; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  amradio_dev_warn (int /*<<< orphan*/ *,char*) ; 
 int amradio_setfreq (struct amradio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct amradio_device* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
				struct v4l2_frequency *f)
{
	struct amradio_device *radio = video_get_drvdata(video_devdata(file));
	int retval;

	/* safety check */
	if (radio->removed)
		return -EIO;

	mutex_lock(&radio->lock);
	radio->curfreq = f->frequency;
	mutex_unlock(&radio->lock);

	retval = amradio_setfreq(radio, radio->curfreq);
	if (retval < 0)
		amradio_dev_warn(&radio->videodev->dev,
			"set frequency failed\n");
	return 0;
}