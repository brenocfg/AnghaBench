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
typedef  scalar_t__ u16 ;
struct hid_blacklist {scalar_t__ const idVendor; scalar_t__ const idProduct; int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_hid (char*,int /*<<< orphan*/ ,scalar_t__ const,scalar_t__ const) ; 
 struct hid_blacklist* hid_blacklist ; 

__attribute__((used)) static const struct hid_blacklist *usbhid_exists_squirk(const u16 idVendor,
		const u16 idProduct)
{
	const struct hid_blacklist *bl_entry = NULL;
	int n = 0;

	for (; hid_blacklist[n].idVendor; n++)
		if (hid_blacklist[n].idVendor == idVendor &&
				hid_blacklist[n].idProduct == idProduct)
			bl_entry = &hid_blacklist[n];

	if (bl_entry != NULL)
		dbg_hid("Found squirk 0x%x for USB HID vendor 0x%hx prod 0x%hx\n",
				bl_entry->quirks, bl_entry->idVendor, 
				bl_entry->idProduct);
	return bl_entry;
}