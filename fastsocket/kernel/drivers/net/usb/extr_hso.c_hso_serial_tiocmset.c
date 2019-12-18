#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct hso_serial {int rts_state; int dtr_state; TYPE_4__* parent; int /*<<< orphan*/  serial_lock; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  usb; TYPE_3__* interface; } ;
struct TYPE_7__ {TYPE_2__* altsetting; } ;
struct TYPE_5__ {int bInterfaceNumber; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  D1 (char*) ; 
 int EINVAL ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 struct hso_serial* get_serial_by_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hso_serial_tiocmset(struct tty_struct *tty, struct file *file,
			       unsigned int set, unsigned int clear)
{
	int val = 0;
	unsigned long flags;
	int if_num;
	struct hso_serial *serial = get_serial_by_tty(tty);

	/* sanity check */
	if (!serial) {
		D1("no tty structures");
		return -EINVAL;
	}
	if_num = serial->parent->interface->altsetting->desc.bInterfaceNumber;

	spin_lock_irqsave(&serial->serial_lock, flags);
	if (set & TIOCM_RTS)
		serial->rts_state = 1;
	if (set & TIOCM_DTR)
		serial->dtr_state = 1;

	if (clear & TIOCM_RTS)
		serial->rts_state = 0;
	if (clear & TIOCM_DTR)
		serial->dtr_state = 0;

	if (serial->dtr_state)
		val |= 0x01;
	if (serial->rts_state)
		val |= 0x02;

	spin_unlock_irqrestore(&serial->serial_lock, flags);

	return usb_control_msg(serial->parent->usb,
			       usb_rcvctrlpipe(serial->parent->usb, 0), 0x22,
			       0x21, val, if_num, NULL, 0,
			       USB_CTRL_SET_TIMEOUT);
}