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

/* Variables and functions */
 int /*<<< orphan*/  DMI_PRODUCT_NAME ; 
 int /*<<< orphan*/  DMI_SYS_VENDOR ; 
 char* dmi_get_system_info (int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static bool compliance_mode_recovery_timer_quirk_check(void)
{
	const char *dmi_product_name, *dmi_sys_vendor;

	dmi_product_name = dmi_get_system_info(DMI_PRODUCT_NAME);
	dmi_sys_vendor = dmi_get_system_info(DMI_SYS_VENDOR);
	if (!dmi_product_name || !dmi_sys_vendor)
		return false;

	if (!(strstr(dmi_sys_vendor, "Hewlett-Packard")))
		return false;

	if (strstr(dmi_product_name, "Z420") ||
			strstr(dmi_product_name, "Z620") ||
			strstr(dmi_product_name, "Z820") ||
			strstr(dmi_product_name, "Z1 Workstation"))
		return true;

	return false;
}