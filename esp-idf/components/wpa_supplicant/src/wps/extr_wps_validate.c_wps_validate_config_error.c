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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_validate_config_error(const u8 *config_error, int mandatory)
{
	u16 val;

	if (config_error == NULL) {
		if (mandatory) {
			wpa_printf(MSG_INFO, "WPS-STRICT: Configuration Error "
				   "attribute missing");
			return -1;
		}
		return 0;
	}
	val = WPA_GET_BE16(config_error);
	if (val > 18) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid Configuration Error "
			   "attribute value 0x%04x", val);
		return -1;
	}
	return 0;
}