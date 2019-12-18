#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct acpi_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* methods; } ;
struct TYPE_3__ {scalar_t__ display_set; scalar_t__ brightness_set; scalar_t__ brightness_get; scalar_t__ brightness_down; scalar_t__ brightness_up; scalar_t__ lcd_status; scalar_t__ mt_lcd_switch; scalar_t__ mt_bt_switch; scalar_t__ mt_ledd; scalar_t__ mt_tled; scalar_t__ mt_mled; scalar_t__ mt_wled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_BRN ; 
 int /*<<< orphan*/  PROC_BT ; 
 int /*<<< orphan*/  PROC_DISP ; 
 int /*<<< orphan*/  PROC_INFO ; 
 int /*<<< orphan*/  PROC_LCD ; 
 int /*<<< orphan*/  PROC_LEDD ; 
 int /*<<< orphan*/  PROC_MLED ; 
 int /*<<< orphan*/  PROC_TLED ; 
 int /*<<< orphan*/  PROC_WLED ; 
 scalar_t__ acpi_device_dir (struct acpi_device*) ; 
 TYPE_2__* hotk ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int asus_hotk_remove_fs(struct acpi_device *device)
{
	if (acpi_device_dir(device)) {
		remove_proc_entry(PROC_INFO, acpi_device_dir(device));
		if (hotk->methods->mt_wled)
			remove_proc_entry(PROC_WLED, acpi_device_dir(device));
		if (hotk->methods->mt_mled)
			remove_proc_entry(PROC_MLED, acpi_device_dir(device));
		if (hotk->methods->mt_tled)
			remove_proc_entry(PROC_TLED, acpi_device_dir(device));
		if (hotk->methods->mt_ledd)
			remove_proc_entry(PROC_LEDD, acpi_device_dir(device));
		if (hotk->methods->mt_bt_switch)
			remove_proc_entry(PROC_BT, acpi_device_dir(device));
		if (hotk->methods->mt_lcd_switch && hotk->methods->lcd_status)
			remove_proc_entry(PROC_LCD, acpi_device_dir(device));
		if ((hotk->methods->brightness_up
		     && hotk->methods->brightness_down)
		    || (hotk->methods->brightness_get
			&& hotk->methods->brightness_set))
			remove_proc_entry(PROC_BRN, acpi_device_dir(device));
		if (hotk->methods->display_set)
			remove_proc_entry(PROC_DISP, acpi_device_dir(device));
	}
	return 0;
}