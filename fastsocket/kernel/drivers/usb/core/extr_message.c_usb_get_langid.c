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
struct usb_device {int have_langid; int string_langid; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODATA ; 
 int EPIPE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int usb_string_sub (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int usb_get_langid(struct usb_device *dev, unsigned char *tbuf)
{
	int err;

	if (dev->have_langid)
		return 0;

	if (dev->string_langid < 0)
		return -EPIPE;

	err = usb_string_sub(dev, 0, 0, tbuf);

	/* If the string was reported but is malformed, default to english
	 * (0x0409) */
	if (err == -ENODATA || (err > 0 && err < 4)) {
		dev->string_langid = 0x0409;
		dev->have_langid = 1;
		dev_err(&dev->dev,
			"string descriptor 0 malformed (err = %d), "
			"defaulting to 0x%04x\n",
				err, dev->string_langid);
		return 0;
	}

	/* In case of all other errors, we assume the device is not able to
	 * deal with strings at all. Set string_langid to -1 in order to
	 * prevent any string to be retrieved from the device */
	if (err < 0) {
		dev_err(&dev->dev, "string descriptor 0 read error: %d\n",
					err);
		dev->string_langid = -1;
		return -EPIPE;
	}

	/* always use the first langid listed */
	dev->string_langid = tbuf[2] | (tbuf[3] << 8);
	dev->have_langid = 1;
	dev_dbg(&dev->dev, "default language 0x%04x\n",
				dev->string_langid);
	return 0;
}