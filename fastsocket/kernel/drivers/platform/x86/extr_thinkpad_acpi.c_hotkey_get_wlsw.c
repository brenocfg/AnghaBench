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
struct TYPE_2__ {int /*<<< orphan*/  hotkey_wlsw; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int TPACPI_RFK_RADIO_OFF ; 
 int TPACPI_RFK_RADIO_ON ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int*,char*,char*) ; 
 scalar_t__ dbg_wlswemul ; 
 int /*<<< orphan*/  hkey_handle ; 
 TYPE_1__ tp_features ; 
 scalar_t__ tpacpi_wlsw_emulstate ; 

__attribute__((used)) static int hotkey_get_wlsw(void)
{
	int status;

	if (!tp_features.hotkey_wlsw)
		return -ENODEV;

#ifdef CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	if (dbg_wlswemul)
		return (tpacpi_wlsw_emulstate) ?
				TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF;
#endif

	if (!acpi_evalf(hkey_handle, &status, "WLSW", "d"))
		return -EIO;

	return (status) ? TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF;
}