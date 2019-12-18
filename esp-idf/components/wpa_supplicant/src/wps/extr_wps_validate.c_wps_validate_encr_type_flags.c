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
 int WPS_ENCR_AES ; 
 int WPS_ENCR_TYPES ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_validate_encr_type_flags(const u8 *flags, int mandatory)
{
	u16 val;

	if (flags == NULL) {
		if (mandatory) {
			wpa_printf(MSG_INFO, "WPS-STRICT: Encryption Type "
				   "Flags attribute missing");
			return -1;
		}
		return 0;
	}
	val = WPA_GET_BE16(flags);
	if ((val & ~WPS_ENCR_TYPES) || !(val & WPS_ENCR_AES)) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid Encryption Type "
			   "Flags attribute value 0x%04x", val);
		return -1;
	}
	return 0;
}