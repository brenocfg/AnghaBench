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
struct usbatm_data {struct usb_interface* usb_intf; struct cxacru_data* driver_data; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct cxacru_data {int poll_state; TYPE_1__ poll_work; int /*<<< orphan*/  adsl_state_serialize; int /*<<< orphan*/  poll_state_serialize; } ;
struct atm_dev {int /*<<< orphan*/ * esi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_REQUEST_CARD_GET_MAC_ADDRESS ; 
 int /*<<< orphan*/  CM_REQUEST_CHIP_ADSL_LINE_START ; 
 int /*<<< orphan*/  CREATE ; 
 int /*<<< orphan*/  CXACRU_ALL_FILES (int /*<<< orphan*/ ) ; 
#define  CXPOLL_POLLING 131 
#define  CXPOLL_SHUTDOWN 130 
#define  CXPOLL_STOPPED 129 
#define  CXPOLL_STOPPING 128 
 int /*<<< orphan*/  atm_err (struct usbatm_data*,char*,int) ; 
 int cxacru_cm (struct cxacru_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cxacru_poll_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxacru_remove_device_files (struct usbatm_data*,struct atm_dev*) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_err (struct usbatm_data*,char*,int) ; 

__attribute__((used)) static int cxacru_atm_start(struct usbatm_data *usbatm_instance,
		struct atm_dev *atm_dev)
{
	struct cxacru_data *instance = usbatm_instance->driver_data;
	struct usb_interface *intf = usbatm_instance->usb_intf;
	/*
	struct atm_dev *atm_dev = usbatm_instance->atm_dev;
	*/
	int ret;
	int start_polling = 1;

	dbg("cxacru_atm_start");

	/* Read MAC address */
	ret = cxacru_cm(instance, CM_REQUEST_CARD_GET_MAC_ADDRESS, NULL, 0,
			atm_dev->esi, sizeof(atm_dev->esi));
	if (ret < 0) {
		atm_err(usbatm_instance, "cxacru_atm_start: CARD_GET_MAC_ADDRESS returned %d\n", ret);
		return ret;
	}

	#define CXACRU_DEVICE_CREATE_FILE(_name) \
		ret = device_create_file(&intf->dev, &dev_attr_##_name); \
		if (unlikely(ret)) \
			goto fail_sysfs;
	CXACRU_ALL_FILES(CREATE);
	#undef CXACRU_DEVICE_CREATE_FILE

	/* start ADSL */
	mutex_lock(&instance->adsl_state_serialize);
	ret = cxacru_cm(instance, CM_REQUEST_CHIP_ADSL_LINE_START, NULL, 0, NULL, 0);
	if (ret < 0)
		atm_err(usbatm_instance, "cxacru_atm_start: CHIP_ADSL_LINE_START returned %d\n", ret);

	/* Start status polling */
	mutex_lock(&instance->poll_state_serialize);
	switch (instance->poll_state) {
	case CXPOLL_STOPPED:
		/* start polling */
		instance->poll_state = CXPOLL_POLLING;
		break;

	case CXPOLL_STOPPING:
		/* abort stop request */
		instance->poll_state = CXPOLL_POLLING;
	case CXPOLL_POLLING:
	case CXPOLL_SHUTDOWN:
		/* don't start polling */
		start_polling = 0;
	}
	mutex_unlock(&instance->poll_state_serialize);
	mutex_unlock(&instance->adsl_state_serialize);

	if (start_polling)
		cxacru_poll_status(&instance->poll_work.work);
	return 0;

fail_sysfs:
	usb_err(usbatm_instance, "cxacru_atm_start: device_create_file failed (%d)\n", ret);
	cxacru_remove_device_files(usbatm_instance, atm_dev);
	return ret;
}