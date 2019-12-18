#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ hotkey_mask; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int*,char*,char*) ; 
 int /*<<< orphan*/  hkey_handle ; 
 int hotkey_acpi_mask ; 
 int hotkey_all_mask ; 
 int hotkey_source_mask ; 
 int hotkey_user_mask ; 
 TYPE_1__ tp_features ; 

__attribute__((used)) static int hotkey_mask_get(void)
{
	if (tp_features.hotkey_mask) {
		u32 m = 0;

		if (!acpi_evalf(hkey_handle, &m, "DHKN", "d"))
			return -EIO;

		hotkey_acpi_mask = m;
	} else {
		/* no mask support doesn't mean no event support... */
		hotkey_acpi_mask = hotkey_all_mask;
	}

	/* sync userspace-visible mask */
	hotkey_user_mask &= (hotkey_acpi_mask | hotkey_source_mask);

	return 0;
}