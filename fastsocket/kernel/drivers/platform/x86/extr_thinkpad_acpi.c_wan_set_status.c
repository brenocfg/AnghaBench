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
typedef  enum tpacpi_rfkill_state { ____Placeholder_tpacpi_rfkill_state } tpacpi_rfkill_state ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TPACPI_DBG_RFKILL ; 
 int TPACPI_RFK_RADIO_ON ; 
 int TP_ACPI_WANCARD_RADIOSSW ; 
 int TP_ACPI_WANCARD_RESUMECTRL ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ dbg_wwanemul ; 
 int /*<<< orphan*/  hkey_handle ; 
 int tpacpi_wwan_emulstate ; 
 int /*<<< orphan*/  vdbg_printk (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int wan_set_status(enum tpacpi_rfkill_state state)
{
	int status;

	vdbg_printk(TPACPI_DBG_RFKILL,
		"will attempt to %s wwan\n",
		(state == TPACPI_RFK_RADIO_ON) ? "enable" : "disable");

#ifdef CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
	if (dbg_wwanemul) {
		tpacpi_wwan_emulstate = (state == TPACPI_RFK_RADIO_ON);
		return 0;
	}
#endif

	if (state == TPACPI_RFK_RADIO_ON)
		status = TP_ACPI_WANCARD_RADIOSSW
			 | TP_ACPI_WANCARD_RESUMECTRL;
	else
		status = 0;

	if (!acpi_evalf(hkey_handle, NULL, "SWAN", "vd", status))
		return -EIO;

	return 0;
}