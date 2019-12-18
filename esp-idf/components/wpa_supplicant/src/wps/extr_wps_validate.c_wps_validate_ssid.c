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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wps_validate_ssid(const u8 *ssid, size_t ssid_len, int mandatory)
{
	if (ssid == NULL) {
		if (mandatory) {
			wpa_printf(MSG_INFO, "WPS-STRICT: SSID "
				   "attribute missing");
			return -1;
		}
		return 0;
	}
	if (ssid_len == 0 || ssid[ssid_len - 1] == 0) {
		wpa_hexdump_ascii(MSG_INFO, "WPS-STRICT: Invalid SSID "
				  "attribute value", ssid, ssid_len);
		return -1;
	}
	return 0;
}