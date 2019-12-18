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
typedef  int /*<<< orphan*/  wchar_t ;
struct usb_device {scalar_t__ state; int /*<<< orphan*/  dev; int /*<<< orphan*/  string_langid; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 unsigned char USB_DT_STRING ; 
 scalar_t__ USB_STATE_SUSPENDED ; 
 int /*<<< orphan*/  UTF16_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char,int,char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int usb_get_langid (struct usb_device*,unsigned char*) ; 
 int usb_string_sub (struct usb_device*,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int utf16s_to_utf8s (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,size_t) ; 

int usb_string(struct usb_device *dev, int index, char *buf, size_t size)
{
	unsigned char *tbuf;
	int err;

	if (dev->state == USB_STATE_SUSPENDED)
		return -EHOSTUNREACH;
	if (size <= 0 || !buf || !index)
		return -EINVAL;
	buf[0] = 0;
	tbuf = kmalloc(256, GFP_NOIO);
	if (!tbuf)
		return -ENOMEM;

	err = usb_get_langid(dev, tbuf);
	if (err < 0)
		goto errout;

	err = usb_string_sub(dev, dev->string_langid, index, tbuf);
	if (err < 0)
		goto errout;

	size--;		/* leave room for trailing NULL char in output buffer */
	err = utf16s_to_utf8s((wchar_t *) &tbuf[2], (err - 2) / 2,
			UTF16_LITTLE_ENDIAN, buf, size);
	buf[err] = 0;

	if (tbuf[1] != USB_DT_STRING)
		dev_dbg(&dev->dev,
			"wrong descriptor type %02x for string %d (\"%s\")\n",
			tbuf[1], index, buf);

 errout:
	kfree(tbuf);
	return err;
}