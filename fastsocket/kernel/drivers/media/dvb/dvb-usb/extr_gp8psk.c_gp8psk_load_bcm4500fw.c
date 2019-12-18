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
typedef  int u8 ;
typedef  int u16 ;
struct firmware {int* data; int size; } ;
struct dvb_usb_device {TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  LOAD_BCM4500 ; 
 int /*<<< orphan*/  bcm4500_firmware ; 
 scalar_t__ dvb_usb_generic_write (struct dvb_usb_device*,int*,int) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 scalar_t__ gp8psk_usb_out_op (struct dvb_usb_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gp8psk_load_bcm4500fw(struct dvb_usb_device *d)
{
	int ret;
	const struct firmware *fw = NULL;
	const u8 *ptr;
	u8 *buf;
	if ((ret = request_firmware(&fw, bcm4500_firmware,
					&d->udev->dev)) != 0) {
		err("did not find the bcm4500 firmware file. (%s) "
			"Please see linux/Documentation/dvb/ for more details on firmware-problems. (%d)",
			bcm4500_firmware,ret);
		return ret;
	}

	ret = -EINVAL;

	if (gp8psk_usb_out_op(d, LOAD_BCM4500,1,0,NULL, 0))
		goto out_rel_fw;

	info("downloading bcm4500 firmware from file '%s'",bcm4500_firmware);

	ptr = fw->data;
	buf = kmalloc(64, GFP_KERNEL | GFP_DMA);
	if (!buf) {
		ret = -ENOMEM;
		goto out_rel_fw;
	}

	while (ptr[0] != 0xff) {
		u16 buflen = ptr[0] + 4;
		if (ptr + buflen >= fw->data + fw->size) {
			err("failed to load bcm4500 firmware.");
			goto out_free;
		}
		memcpy(buf, ptr, buflen);
		if (dvb_usb_generic_write(d, buf, buflen)) {
			err("failed to load bcm4500 firmware.");
			goto out_free;
		}
		ptr += buflen;
	}

	ret = 0;

out_free:
	kfree(buf);
out_rel_fw:
	release_firmware(fw);

	return ret;
}