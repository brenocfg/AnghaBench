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
struct dsbr100_device {TYPE_1__* usbdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  curfreq; scalar_t__ removed; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int dsbr100_setfreq (struct dsbr100_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dsbr100_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
				struct v4l2_frequency *f)
{
	struct dsbr100_device *radio = video_drvdata(file);
	int retval;

	/* safety check */
	if (radio->removed)
		return -EIO;

	mutex_lock(&radio->lock);
	radio->curfreq = f->frequency;
	mutex_unlock(&radio->lock);

	retval = dsbr100_setfreq(radio);
	if (retval < 0)
		dev_warn(&radio->usbdev->dev, "Set frequency failed\n");
	return 0;
}