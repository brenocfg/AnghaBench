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
 scalar_t__ const WPS_Beacon ; 
 scalar_t__ const WPS_WSC_DONE ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_validate_msg_type(const u8 *msg_type, int mandatory)
{
	if (msg_type == NULL) {
		if (mandatory) {
			wpa_printf(MSG_INFO, "WPS-STRICT: Message Type "
				   "attribute missing");
			return -1;
		}
		return 0;
	}
	if (*msg_type < WPS_Beacon || *msg_type > WPS_WSC_DONE) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid Message Type "
			   "attribute value 0x%x", *msg_type);
		return -1;
	}
	return 0;
}