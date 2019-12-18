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
 int EIO ; 
 int TPACPI_RFK_RADIO_OFF ; 
 int TPACPI_RFK_RADIO_ON ; 
 int TP_ACPI_BLUETOOTH_RADIOSSW ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int*,char*,char*) ; 
 scalar_t__ dbg_bluetoothemul ; 
 int /*<<< orphan*/  hkey_handle ; 
 scalar_t__ tpacpi_bluetooth_emulstate ; 

__attribute__((used)) static int bluetooth_get_status(void)
{
	int status;

#ifdef CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	if (dbg_bluetoothemul)
		return (tpacpi_bluetooth_emulstate) ?
		       TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF;
#endif

	if (!acpi_evalf(hkey_handle, &status, "GBDC", "d"))
		return -EIO;

	return ((status & TP_ACPI_BLUETOOTH_RADIOSSW) != 0) ?
			TPACPI_RFK_RADIO_ON : TPACPI_RFK_RADIO_OFF;
}