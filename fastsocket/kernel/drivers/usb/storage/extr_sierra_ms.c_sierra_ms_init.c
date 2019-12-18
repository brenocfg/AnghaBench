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
struct usb_device {int dummy; } ;
struct us_data {TYPE_1__* pusb_intf; struct usb_device* pusb_dev; } ;
struct swoc_info {int dummy; } ;
struct scsi_device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  SWIMS_SET_MODE_Modem ; 
 scalar_t__ TRU_FORCE_MODEM ; 
 scalar_t__ TRU_FORCE_MS ; 
 int /*<<< orphan*/  US_DEBUGP (char*,...) ; 
 int /*<<< orphan*/  containsFullLinuxPackage (struct swoc_info*) ; 
 int /*<<< orphan*/  debug_swoc (struct swoc_info*) ; 
 int /*<<< orphan*/  dev_attr_truinst ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct swoc_info*) ; 
 struct swoc_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 struct scsi_device* scsi_get_host_dev (struct Scsi_Host*) ; 
 int sierra_get_swoc_info (struct usb_device*,struct swoc_info*) ; 
 int sierra_set_ms_mode (struct usb_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ swi_tru_install ; 
 struct Scsi_Host* us_to_host (struct us_data*) ; 

int sierra_ms_init(struct us_data *us)
{
	int result, retries;
	signed long delay_t;
	struct swoc_info *swocInfo;
	struct usb_device *udev;
	struct Scsi_Host *sh;
	struct scsi_device *sd;

	delay_t = 2;
	retries = 3;
	result = 0;
	udev = us->pusb_dev;

	sh = us_to_host(us);
	sd = scsi_get_host_dev(sh);

	US_DEBUGP("SWIMS: sierra_ms_init called\n");

	/* Force Modem mode */
	if (swi_tru_install == TRU_FORCE_MODEM) {
		US_DEBUGP("SWIMS: %s", "Forcing Modem Mode\n");
		result = sierra_set_ms_mode(udev, SWIMS_SET_MODE_Modem);
		if (result < 0)
			US_DEBUGP("SWIMS: Failed to switch to modem mode.\n");
		return -EIO;
	}
	/* Force Mass Storage mode (keep CD-Rom) */
	else if (swi_tru_install == TRU_FORCE_MS) {
		US_DEBUGP("SWIMS: %s", "Forcing Mass Storage Mode\n");
		goto complete;
	}
	/* Normal TRU-Install Logic */
	else {
		US_DEBUGP("SWIMS: %s", "Normal SWoC Logic\n");

		swocInfo = kmalloc(sizeof(struct swoc_info),
				GFP_KERNEL);
		if (!swocInfo) {
			US_DEBUGP("SWIMS: %s", "Allocation failure\n");
			return -ENOMEM;
		}

		retries = 3;
		do {
			retries--;
			result = sierra_get_swoc_info(udev, swocInfo);
			if (result < 0) {
				US_DEBUGP("SWIMS: %s", "Failed SWoC query\n");
				schedule_timeout_uninterruptible(2*HZ);
			}
		} while (retries && result < 0);

		if (result < 0) {
			US_DEBUGP("SWIMS: %s",
				  "Completely failed SWoC query\n");
			kfree(swocInfo);
			return -EIO;
		}

		debug_swoc(swocInfo);

		/* If there is not Linux software on the TRU-Install device
		 * then switch to modem mode
		 */
		if (!containsFullLinuxPackage(swocInfo)) {
			US_DEBUGP("SWIMS: %s",
				"Switching to Modem Mode\n");
			result = sierra_set_ms_mode(udev,
				SWIMS_SET_MODE_Modem);
			if (result < 0)
				US_DEBUGP("SWIMS: Failed to switch modem\n");
			kfree(swocInfo);
			return -EIO;
		}
		kfree(swocInfo);
	}
complete:
	result = device_create_file(&us->pusb_intf->dev, &dev_attr_truinst);

	return 0;
}