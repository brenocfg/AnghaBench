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
typedef  int u32 ;
struct tps_key_entry {int /*<<< orphan*/  keycode; } ;
struct topstar_hkey {int /*<<< orphan*/  inputdev; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct topstar_hkey* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 struct tps_key_entry* tps_get_key_by_scancode (int) ; 

__attribute__((used)) static void acpi_topstar_notify(struct acpi_device *device, u32 event)
{
	struct tps_key_entry *key;
	static bool dup_evnt[2];
	bool *dup;
	struct topstar_hkey *hkey = acpi_driver_data(device);

	/* 0x83 and 0x84 key events comes duplicated... */
	if (event == 0x83 || event == 0x84) {
		dup = &dup_evnt[event - 0x83];
		if (*dup) {
			*dup = false;
			return;
		}
		*dup = true;
	}

	/*
	 * 'G key' generate two event codes, convert to only
	 * one event/key code for now (3G switch?)
	 */
	if (event == 0x97)
		event = 0x96;

	key = tps_get_key_by_scancode(event);
	if (key) {
		input_report_key(hkey->inputdev, key->keycode, 1);
		input_sync(hkey->inputdev);
		input_report_key(hkey->inputdev, key->keycode, 0);
		input_sync(hkey->inputdev);
		return;
	}

	/* Known non hotkey events don't handled or that we don't care yet */
	if (event == 0x8e || event == 0x8f || event == 0x90)
		return;

	pr_info("unknown event = 0x%02x\n", event);
}