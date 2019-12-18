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
struct ar9170 {int cmd_seq; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  carl9170_usb_cancel_urbs (struct ar9170*) ; 
 int carl9170_usb_init_rx_bulk_urbs (struct ar9170*) ; 
 int carl9170_usb_load_firmware (struct ar9170*) ; 
 int carl9170_usb_open (struct ar9170*) ; 
 int carl9170_usb_send_rx_irq_urb (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_usb_stop (struct ar9170*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int carl9170_usb_init_device(struct ar9170 *ar)
{
	int err;

	/*
	 * The carl9170 firmware let's the driver know when it's
	 * ready for action. But we have to be prepared to gracefully
	 * handle all spurious [flushed] messages after each (re-)boot.
	 * Thus the command response counter remains disabled until it
	 * can be safely synchronized.
	 */
	ar->cmd_seq = -2;

	err = carl9170_usb_send_rx_irq_urb(ar);
	if (err)
		goto err_out;

	err = carl9170_usb_init_rx_bulk_urbs(ar);
	if (err)
		goto err_unrx;

	err = carl9170_usb_open(ar);
	if (err)
		goto err_unrx;

	mutex_lock(&ar->mutex);
	err = carl9170_usb_load_firmware(ar);
	mutex_unlock(&ar->mutex);
	if (err)
		goto err_stop;

	return 0;

err_stop:
	carl9170_usb_stop(ar);

err_unrx:
	carl9170_usb_cancel_urbs(ar);

err_out:
	return err;
}