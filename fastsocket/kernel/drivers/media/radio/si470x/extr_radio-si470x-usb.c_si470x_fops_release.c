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
struct si470x_device {scalar_t__ users; int /*<<< orphan*/  disconnect_lock; int /*<<< orphan*/  intf; int /*<<< orphan*/  read_queue; struct si470x_device* buffer; struct si470x_device* int_in_buffer; int /*<<< orphan*/  videodev; scalar_t__ disconnected; scalar_t__ int_in_urb; scalar_t__ int_in_running; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  kfree (struct si470x_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si470x_stop (struct si470x_device*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 
 struct si470x_device* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int si470x_fops_release(struct file *file)
{
	struct si470x_device *radio = video_drvdata(file);
	int retval = 0;

	/* safety check */
	if (!radio) {
		retval = -ENODEV;
		goto done;
	}

	mutex_lock(&radio->disconnect_lock);
	radio->users--;
	if (radio->users == 0) {
		/* shutdown interrupt handler */
		if (radio->int_in_running) {
			radio->int_in_running = 0;
		if (radio->int_in_urb)
			usb_kill_urb(radio->int_in_urb);
		}

		if (radio->disconnected) {
			video_unregister_device(radio->videodev);
			kfree(radio->int_in_buffer);
			kfree(radio->buffer);
			kfree(radio);
			goto unlock;
		}

		/* cancel read processes */
		wake_up_interruptible(&radio->read_queue);

		/* stop radio */
		retval = si470x_stop(radio);
		usb_autopm_put_interface(radio->intf);
	}
unlock:
	mutex_unlock(&radio->disconnect_lock);
done:
	return retval;
}