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
struct file {int dummy; } ;
struct amradio_device {TYPE_1__* videodev; int /*<<< orphan*/  removed; int /*<<< orphan*/  lock; scalar_t__ users; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMRADIO_STOP ; 
 int ENODEV ; 
 int /*<<< orphan*/  amradio_dev_warn (int /*<<< orphan*/ *,char*) ; 
 int amradio_set_mute (struct amradio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct amradio_device* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_amradio_close(struct file *file)
{
	struct amradio_device *radio = video_get_drvdata(video_devdata(file));
	int retval;

	if (!radio)
		return -ENODEV;

	mutex_lock(&radio->lock);
	radio->users = 0;
	mutex_unlock(&radio->lock);

	if (!radio->removed) {
		retval = amradio_set_mute(radio, AMRADIO_STOP);
		if (retval < 0)
			amradio_dev_warn(&radio->videodev->dev,
				"amradio_stop failed\n");
	}

	return 0;
}