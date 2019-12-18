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
struct TYPE_2__ {int idProduct; } ;
struct usb_device {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;
struct firmware {int dummy; } ;
typedef  int /*<<< orphan*/  lme2510c_s7395 ;
typedef  int /*<<< orphan*/  lme2510c_lg ;

/* Variables and functions */
 int ENODEV ; 
 int dvb_usb_lme2510_firmware ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/  lme_coldreset (struct usb_device*) ; 
 int /*<<< orphan*/  lme_firmware ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lme_firmware_switch(struct usb_device *udev, int cold)
{
	const struct firmware *fw = NULL;
	char lme2510c_s7395[] = "dvb-usb-lme2510c-s7395.fw";
	char lme2510c_lg[] = "dvb-usb-lme2510c-lg.fw";
	char *firm_msg[] = {"Loading", "Switching to"};
	int ret;

	cold = (cold > 0) ? (cold & 1) : 0;

	if (udev->descriptor.idProduct == 0x1122)
		return 0;

	switch (dvb_usb_lme2510_firmware) {
	case 0:
	default:
		memcpy(&lme_firmware, lme2510c_s7395, sizeof(lme2510c_s7395));
		ret = request_firmware(&fw, lme_firmware, &udev->dev);
		if (ret == 0) {
			info("FRM %s S7395 Firmware", firm_msg[cold]);
			break;
		}
		if (cold == 0)
			dvb_usb_lme2510_firmware = 1;
		else
			cold = 0;
	case 1:
		memcpy(&lme_firmware, lme2510c_lg, sizeof(lme2510c_lg));
		ret = request_firmware(&fw, lme_firmware, &udev->dev);
		if (ret == 0) {
			info("FRM %s LG Firmware", firm_msg[cold]);
			break;
		}
		info("FRM No Firmware Found - please install");
		dvb_usb_lme2510_firmware = 0;
		cold = 0;
		break;
	}

	release_firmware(fw);

	if (cold) {
		lme_coldreset(udev);
		return -ENODEV;
	}

	return ret;
}