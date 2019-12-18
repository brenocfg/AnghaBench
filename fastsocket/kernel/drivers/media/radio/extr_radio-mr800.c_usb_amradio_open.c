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
struct amradio_device {int users; int muted; TYPE_1__* videodev; int /*<<< orphan*/  curfreq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMRADIO_START ; 
 int EIO ; 
 int /*<<< orphan*/  WANT_STEREO ; 
 int /*<<< orphan*/  amradio_dev_warn (int /*<<< orphan*/ *,char*) ; 
 int amradio_set_mute (struct amradio_device*,int /*<<< orphan*/ ) ; 
 int amradio_set_stereo (struct amradio_device*,int /*<<< orphan*/ ) ; 
 int amradio_setfreq (struct amradio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct amradio_device* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_amradio_open(struct file *file)
{
	struct amradio_device *radio = video_get_drvdata(video_devdata(file));
	int retval;

	lock_kernel();

	radio->users = 1;
	radio->muted = 1;

	retval = amradio_set_mute(radio, AMRADIO_START);
	if (retval < 0) {
		amradio_dev_warn(&radio->videodev->dev,
			"radio did not start up properly\n");
		radio->users = 0;
		unlock_kernel();
		return -EIO;
	}

	retval = amradio_set_stereo(radio, WANT_STEREO);
	if (retval < 0)
		amradio_dev_warn(&radio->videodev->dev,
			"set stereo failed\n");

	retval = amradio_setfreq(radio, radio->curfreq);
	if (retval < 0)
		amradio_dev_warn(&radio->videodev->dev,
			"set frequency failed\n");

	unlock_kernel();
	return 0;
}