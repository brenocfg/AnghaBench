#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct key_entry {int type; int /*<<< orphan*/  keycode; } ;
struct acpi_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_class; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; TYPE_1__ pnp; } ;
struct TYPE_5__ {scalar_t__ inputdev; TYPE_3__* device; int /*<<< orphan*/ * event_count; } ;

/* Variables and functions */
 int ACPI_MAX_SYS_NOTIFY ; 
 int ENODEV ; 
#define  KE_KEY 128 
 int NOTIFY_BRN_MAX ; 
 int NOTIFY_BRN_MIN ; 
 int /*<<< orphan*/  acpi_bus_generate_netlink_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  acpi_bus_generate_proc_event (TYPE_3__*,int,scalar_t__) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct key_entry* eepc_get_entry_by_scancode (int) ; 
 TYPE_2__* ehotk ; 
 int /*<<< orphan*/  input_report_key (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (scalar_t__) ; 
 int notify_brn () ; 

__attribute__((used)) static void eeepc_hotk_notify(struct acpi_device *device, u32 event)
{
	static struct key_entry *key;
	u16 count;
	int brn = -ENODEV;

	if (!ehotk)
		return;
	if (event > ACPI_MAX_SYS_NOTIFY)
		return;
	if (event >= NOTIFY_BRN_MIN && event <= NOTIFY_BRN_MAX)
		brn = notify_brn();
	count = ehotk->event_count[event % 128]++;
	acpi_bus_generate_proc_event(ehotk->device, event, count);
	acpi_bus_generate_netlink_event(ehotk->device->pnp.device_class,
					dev_name(&ehotk->device->dev), event,
					count);
	if (ehotk->inputdev) {
		if (brn != -ENODEV) {
			/* brightness-change events need special
			 * handling for conversion to key events
			 */
			if (brn < 0)
				brn = event;
			else
				brn += NOTIFY_BRN_MIN;
			if (event < brn)
				event = NOTIFY_BRN_MIN; /* brightness down */
			else if (event > brn)
				event = NOTIFY_BRN_MIN + 2; /* ... up */
			else
				event = NOTIFY_BRN_MIN + 1; /* ... unchanged */
		}
		key = eepc_get_entry_by_scancode(event);
		if (key) {
			switch (key->type) {
			case KE_KEY:
				input_report_key(ehotk->inputdev, key->keycode,
						 1);
				input_sync(ehotk->inputdev);
				input_report_key(ehotk->inputdev, key->keycode,
						 0);
				input_sync(ehotk->inputdev);
				break;
			}
		}
	}
}