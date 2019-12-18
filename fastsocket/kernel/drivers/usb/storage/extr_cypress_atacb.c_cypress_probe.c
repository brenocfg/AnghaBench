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
struct us_data {char* protocol_name; int /*<<< orphan*/  proto_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  cypress_atacb_passthrough ; 
 int cypress_unusual_dev_list ; 
 struct usb_device_id const* cypress_usb_ids ; 
 int usb_stor_probe1 (struct us_data**,struct usb_interface*,struct usb_device_id const*,int) ; 
 int usb_stor_probe2 (struct us_data*) ; 

__attribute__((used)) static int cypress_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	struct us_data *us;
	int result;

	result = usb_stor_probe1(&us, intf, id,
			(id - cypress_usb_ids) + cypress_unusual_dev_list);
	if (result)
		return result;

	us->protocol_name = "Transparent SCSI with Cypress ATACB";
	us->proto_handler = cypress_atacb_passthrough;

	result = usb_stor_probe2(us);
	return result;
}