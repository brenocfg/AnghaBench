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
 int ATKD_LCD_OFF ; 
 int ATKD_LCD_ON ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
#define  KE_KEY 128 
 int /*<<< orphan*/  LCD_ON ; 
 int /*<<< orphan*/  acpi_bus_generate_netlink_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  acpi_bus_generate_proc_event (TYPE_3__*,int,scalar_t__) ; 
 struct key_entry* asus_get_entry_by_scancode (int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 TYPE_2__* hotk ; 
 int /*<<< orphan*/  input_report_key (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (scalar_t__) ; 
 int /*<<< orphan*/  lcd_blank (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_status (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asus_hotk_notify(struct acpi_device *device, u32 event)
{
	static struct key_entry *key;
	u16 count;

	/* TODO Find a better way to handle events count. */
	if (!hotk)
		return;

	/*
	 * We need to tell the backlight device when the backlight power is
	 * switched
	 */
	if (event == ATKD_LCD_ON) {
		write_status(NULL, 1, LCD_ON);
		lcd_blank(FB_BLANK_UNBLANK);
	} else if (event == ATKD_LCD_OFF) {
		write_status(NULL, 0, LCD_ON);
		lcd_blank(FB_BLANK_POWERDOWN);
	}

	count = hotk->event_count[event % 128]++;
	acpi_bus_generate_proc_event(hotk->device, event, count);
	acpi_bus_generate_netlink_event(hotk->device->pnp.device_class,
					dev_name(&hotk->device->dev), event,
					count);

	if (hotk->inputdev) {
		key = asus_get_entry_by_scancode(event);
		if (!key)
			return ;

		switch (key->type) {
		case KE_KEY:
			input_report_key(hotk->inputdev, key->keycode, 1);
			input_sync(hotk->inputdev);
			input_report_key(hotk->inputdev, key->keycode, 0);
			input_sync(hotk->inputdev);
			break;
		}
	}
}