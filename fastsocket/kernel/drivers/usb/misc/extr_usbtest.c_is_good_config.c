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
struct usbtest_dev {scalar_t__ buf; } ;
struct usb_config_descriptor {int bDescriptorType; int bLength; int bmAttributes; int /*<<< orphan*/  wTotalLength; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct usbtest_dev*,char*) ; 
 int TBUF_SIZE ; 
#define  USB_DT_CONFIG 129 
#define  USB_DT_OTHER_SPEED_CONFIG 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  realworld ; 

__attribute__((used)) static int is_good_config(struct usbtest_dev *tdev, int len)
{
	struct usb_config_descriptor	*config;

	if (len < sizeof *config)
		return 0;
	config = (struct usb_config_descriptor *) tdev->buf;

	switch (config->bDescriptorType) {
	case USB_DT_CONFIG:
	case USB_DT_OTHER_SPEED_CONFIG:
		if (config->bLength != 9) {
			ERROR(tdev, "bogus config descriptor length\n");
			return 0;
		}
		/* this bit 'must be 1' but often isn't */
		if (!realworld && !(config->bmAttributes & 0x80)) {
			ERROR(tdev, "high bit of config attributes not set\n");
			return 0;
		}
		if (config->bmAttributes & 0x1f) {	/* reserved == 0 */
			ERROR(tdev, "reserved config bits set\n");
			return 0;
		}
		break;
	default:
		return 0;
	}

	if (le16_to_cpu(config->wTotalLength) == len)		/* read it all */
		return 1;
	if (le16_to_cpu(config->wTotalLength) >= TBUF_SIZE)		/* max partial read */
		return 1;
	ERROR(tdev, "bogus config descriptor read size\n");
	return 0;
}