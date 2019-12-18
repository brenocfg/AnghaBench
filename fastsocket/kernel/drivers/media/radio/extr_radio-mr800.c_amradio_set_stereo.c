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
struct amradio_device {int* buffer; int stereo; int /*<<< orphan*/  lock; int /*<<< orphan*/  usbdev; scalar_t__ removed; } ;

/* Variables and functions */
 int AMRADIO_SET_MONO ; 
 int BUFFER_LENGTH ; 
 int EIO ; 
 int /*<<< orphan*/  USB_TIMEOUT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndintpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int amradio_set_stereo(struct amradio_device *radio, char argument)
{
	int retval;
	int size;

	/* safety check */
	if (radio->removed)
		return -EIO;

	mutex_lock(&radio->lock);

	radio->buffer[0] = 0x00;
	radio->buffer[1] = 0x55;
	radio->buffer[2] = 0xaa;
	radio->buffer[3] = 0x00;
	radio->buffer[4] = AMRADIO_SET_MONO;
	radio->buffer[5] = argument;
	radio->buffer[6] = 0x00;
	radio->buffer[7] = 0x00;

	retval = usb_bulk_msg(radio->usbdev, usb_sndintpipe(radio->usbdev, 2),
		(void *) (radio->buffer), BUFFER_LENGTH, &size, USB_TIMEOUT);

	if (retval < 0 || size != BUFFER_LENGTH) {
		radio->stereo = -1;
		mutex_unlock(&radio->lock);
		return retval;
	}

	radio->stereo = 1;

	mutex_unlock(&radio->lock);

	return retval;
}