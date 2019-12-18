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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct hid_blacklist {int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_QUIRK_NO_INIT_REPORTS ; 
 scalar_t__ const USB_DEVICE_ID_NCR_FIRST ; 
 scalar_t__ const USB_DEVICE_ID_NCR_LAST ; 
 scalar_t__ const USB_VENDOR_ID_NCR ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dquirks_rwsem ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 struct hid_blacklist* usbhid_exists_dquirk (scalar_t__ const,scalar_t__ const) ; 
 struct hid_blacklist* usbhid_exists_squirk (scalar_t__ const,scalar_t__ const) ; 

u32 usbhid_lookup_quirk(const u16 idVendor, const u16 idProduct)
{
	u32 quirks = 0;
	const struct hid_blacklist *bl_entry = NULL;

	/* NCR devices must not be queried for reports */
	if (idVendor == USB_VENDOR_ID_NCR &&
			idProduct >= USB_DEVICE_ID_NCR_FIRST &&
			idProduct <= USB_DEVICE_ID_NCR_LAST)
			return HID_QUIRK_NO_INIT_REPORTS;

	down_read(&dquirks_rwsem);
	bl_entry = usbhid_exists_dquirk(idVendor, idProduct);
	if (!bl_entry)
		bl_entry = usbhid_exists_squirk(idVendor, idProduct);
	if (bl_entry)
		quirks = bl_entry->quirks;
	up_read(&dquirks_rwsem);

	return quirks;
}