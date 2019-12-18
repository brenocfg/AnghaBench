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
struct kaweth_device {int* firmware_buf; TYPE_1__* dev; } ;
struct firmware {int size; int /*<<< orphan*/  data; } ;
typedef  void* __u8 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  KAWETH_COMMAND_SCAN ; 
 int /*<<< orphan*/  KAWETH_CONTROL_TIMEOUT ; 
 int KAWETH_FIRMWARE_BUF_SIZE ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dbg (char*,int,...) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int kaweth_control (struct kaweth_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kaweth_download_firmware(struct kaweth_device *kaweth,
				    const char *fwname,
				    __u8 interrupt,
				    __u8 type)
{
	const struct firmware *fw;
	int data_len;
	int ret;

	ret = request_firmware(&fw, fwname, &kaweth->dev->dev);
	if (ret) {
		err("Firmware request failed\n");
		return ret;
	}

	if (fw->size > KAWETH_FIRMWARE_BUF_SIZE) {
		err("Firmware too big: %zu", fw->size);
		return -ENOSPC;
	}
	data_len = fw->size;
	memcpy(kaweth->firmware_buf, fw->data, fw->size);

	release_firmware(fw);

	kaweth->firmware_buf[2] = (data_len & 0xFF) - 7;
	kaweth->firmware_buf[3] = data_len >> 8;
	kaweth->firmware_buf[4] = type;
	kaweth->firmware_buf[5] = interrupt;

	dbg("High: %i, Low:%i", kaweth->firmware_buf[3],
		   kaweth->firmware_buf[2]);

	dbg("Downloading firmware at %p to kaweth device at %p",
	    fw->data, kaweth);
	dbg("Firmware length: %d", data_len);

	return kaweth_control(kaweth,
		              usb_sndctrlpipe(kaweth->dev, 0),
			      KAWETH_COMMAND_SCAN,
			      USB_TYPE_VENDOR | USB_DIR_OUT | USB_RECIP_DEVICE,
			      0,
			      0,
			      (void *)kaweth->firmware_buf,
			      data_len,
			      KAWETH_CONTROL_TIMEOUT);
}