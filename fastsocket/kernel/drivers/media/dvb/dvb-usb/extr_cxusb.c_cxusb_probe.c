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
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  cxusb_aver_a868r_properties ; 
 int /*<<< orphan*/  cxusb_bluebird_dee1601_properties ; 
 int /*<<< orphan*/  cxusb_bluebird_dtt7579_properties ; 
 int /*<<< orphan*/  cxusb_bluebird_dualdig4_properties ; 
 int /*<<< orphan*/  cxusb_bluebird_dualdig4_rev2_properties ; 
 int /*<<< orphan*/  cxusb_bluebird_lgh064f_properties ; 
 int /*<<< orphan*/  cxusb_bluebird_lgz201_properties ; 
 int /*<<< orphan*/  cxusb_bluebird_nano2_needsfirmware_properties ; 
 int /*<<< orphan*/  cxusb_bluebird_nano2_properties ; 
 int /*<<< orphan*/  cxusb_d680_dmb_properties ; 
 int /*<<< orphan*/  cxusb_medion_properties ; 
 int /*<<< orphan*/  cxusb_mygica_d689_properties ; 
 scalar_t__ dvb_usb_device_init (struct usb_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxusb_probe(struct usb_interface *intf,
		       const struct usb_device_id *id)
{
	if (0 == dvb_usb_device_init(intf, &cxusb_medion_properties,
				     THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &cxusb_bluebird_lgh064f_properties,
				     THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &cxusb_bluebird_dee1601_properties,
				     THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &cxusb_bluebird_lgz201_properties,
				     THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &cxusb_bluebird_dtt7579_properties,
				     THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &cxusb_bluebird_dualdig4_properties,
				     THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &cxusb_bluebird_nano2_properties,
				     THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf,
				&cxusb_bluebird_nano2_needsfirmware_properties,
				     THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &cxusb_aver_a868r_properties,
				     THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf,
				     &cxusb_bluebird_dualdig4_rev2_properties,
				     THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &cxusb_d680_dmb_properties,
				     THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &cxusb_mygica_d689_properties,
				     THIS_MODULE, NULL, adapter_nr) ||
	    0)
		return 0;

	return -EINVAL;
}