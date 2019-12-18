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
struct TYPE_2__ {scalar_t__ buffer_pos; scalar_t__ period_pos; } ;
struct ua101 {TYPE_1__ capture; int /*<<< orphan*/  states; int /*<<< orphan*/  alsa_capture_wait; int /*<<< orphan*/  mutex; } ;
struct snd_pcm_substream {struct ua101* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPTURE_URB_COMPLETED ; 
 int /*<<< orphan*/  DISCONNECTED ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  USB_CAPTURE_RUNNING ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int start_usb_capture (struct ua101*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int capture_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct ua101 *ua = substream->private_data;
	int err;

	mutex_lock(&ua->mutex);
	err = start_usb_capture(ua);
	mutex_unlock(&ua->mutex);
	if (err < 0)
		return err;

	/*
	 * The EHCI driver schedules the first packet of an iso stream at 10 ms
	 * in the future, i.e., no data is actually captured for that long.
	 * Take the wait here so that the stream is known to be actually
	 * running when the start trigger has been called.
	 */
	wait_event(ua->alsa_capture_wait,
		   test_bit(CAPTURE_URB_COMPLETED, &ua->states) ||
		   !test_bit(USB_CAPTURE_RUNNING, &ua->states));
	if (test_bit(DISCONNECTED, &ua->states))
		return -ENODEV;
	if (!test_bit(USB_CAPTURE_RUNNING, &ua->states))
		return -EIO;

	ua->capture.period_pos = 0;
	ua->capture.buffer_pos = 0;
	return 0;
}