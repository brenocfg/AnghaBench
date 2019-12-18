#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct asus_hotk {int dummy; } ;
struct acpi_device {TYPE_1__* driver_data; int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int ledd_status; int light_level; struct TYPE_4__* name; scalar_t__ light_switch; struct acpi_device* device; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_HOTK_CLASS ; 
 int /*<<< orphan*/  ASUS_HOTK_DEVICE_NAME ; 
 int /*<<< orphan*/  ASUS_LAPTOP_VERSION ; 
 int /*<<< orphan*/  BT_ON ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPS_ON ; 
 int /*<<< orphan*/  LCD_ON ; 
 int /*<<< orphan*/  WL_ON ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 int /*<<< orphan*/  asus_hotk_add_fs () ; 
 int asus_hotk_check () ; 
 int asus_hotk_found ; 
 int /*<<< orphan*/ * bt_switch_handle ; 
 TYPE_1__* hotk ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 scalar_t__ kled_set_handle ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ls_level_handle ; 
 scalar_t__ ls_switch_handle ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int read_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_kled_lvl (int) ; 
 int /*<<< orphan*/  set_light_sens_level (int) ; 
 int /*<<< orphan*/  set_light_sens_switch (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wl_switch_handle ; 
 int /*<<< orphan*/  write_status (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asus_hotk_add(struct acpi_device *device)
{
	int result;

	if (!device)
		return -EINVAL;

	pr_notice("Asus Laptop Support version %s\n",
	       ASUS_LAPTOP_VERSION);

	hotk = kzalloc(sizeof(struct asus_hotk), GFP_KERNEL);
	if (!hotk)
		return -ENOMEM;

	hotk->handle = device->handle;
	strcpy(acpi_device_name(device), ASUS_HOTK_DEVICE_NAME);
	strcpy(acpi_device_class(device), ASUS_HOTK_CLASS);
	device->driver_data = hotk;
	hotk->device = device;

	result = asus_hotk_check();
	if (result)
		goto end;

	asus_hotk_add_fs();

	asus_hotk_found = 1;

	/* WLED and BLED are on by default */
	write_status(bt_switch_handle, 1, BT_ON);
	write_status(wl_switch_handle, 1, WL_ON);

	/* If the h/w switch is off, we need to check the real status */
	write_status(NULL, read_status(BT_ON), BT_ON);
	write_status(NULL, read_status(WL_ON), WL_ON);

	/* LCD Backlight is on by default */
	write_status(NULL, 1, LCD_ON);

	/* Keyboard Backlight is on by default */
	if (kled_set_handle)
		set_kled_lvl(1);

	/* LED display is off by default */
	hotk->ledd_status = 0xFFF;

	/* Set initial values of light sensor and level */
	hotk->light_switch = 0;	/* Default to light sensor disabled */
	hotk->light_level = 5;	/* level 5 for sensor sensitivity */

	if (ls_switch_handle)
		set_light_sens_switch(hotk->light_switch);

	if (ls_level_handle)
		set_light_sens_level(hotk->light_level);

	/* GPS is on by default */
	write_status(NULL, 1, GPS_ON);

end:
	if (result) {
		kfree(hotk->name);
		kfree(hotk);
	}

	return result;
}