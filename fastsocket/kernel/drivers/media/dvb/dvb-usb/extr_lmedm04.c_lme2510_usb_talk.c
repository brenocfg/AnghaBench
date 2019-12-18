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
typedef  int /*<<< orphan*/  u8 ;
struct lme2510_state {int /*<<< orphan*/ * usb_buffer; } ;
struct dvb_usb_device {int /*<<< orphan*/  usb_mutex; int /*<<< orphan*/  udev; struct lme2510_state* priv; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int lme2510_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int lme2510_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lme2510_usb_talk(struct dvb_usb_device *d,
		u8 *wbuf, int wlen, u8 *rbuf, int rlen)
{
	struct lme2510_state *st = d->priv;
	u8 *buff;
	int ret = 0;

	if (st->usb_buffer == NULL) {
		st->usb_buffer = kmalloc(512, GFP_KERNEL);
		if (st->usb_buffer == NULL) {
			info("MEM Error no memory");
			return -ENOMEM;
		}
	}
	buff = st->usb_buffer;

	/* the read/write capped at 512 */
	memcpy(buff, wbuf, (wlen > 512) ? 512 : wlen);

	ret = mutex_lock_interruptible(&d->usb_mutex);

	if (ret < 0)
		return -EAGAIN;

	ret |= usb_clear_halt(d->udev, usb_sndbulkpipe(d->udev, 0x01));

	ret |= lme2510_bulk_write(d->udev, buff, wlen , 0x01);

	msleep(10);

	ret |= usb_clear_halt(d->udev, usb_rcvbulkpipe(d->udev, 0x01));

	ret |= lme2510_bulk_read(d->udev, buff, (rlen > 512) ?
			512 : rlen , 0x01);

	if (rlen > 0)
		memcpy(rbuf, buff, rlen);

	mutex_unlock(&d->usb_mutex);

	return (ret < 0) ? -ENODEV : 0;
}