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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_validate_ap_setup_locked(const u8 *ap_setup_locked,
					int mandatory)
{
	if (ap_setup_locked == NULL) {
		if (mandatory) {
			wpa_printf(MSG_INFO, "WPS-STRICT: AP Setup Locked "
				   "attribute missing");
			return -1;
		}
		return 0;
	}
	if (*ap_setup_locked > 1) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid AP Setup Locked "
			   "attribute value 0x%x", *ap_setup_locked);
		return -1;
	}
	return 0;
}