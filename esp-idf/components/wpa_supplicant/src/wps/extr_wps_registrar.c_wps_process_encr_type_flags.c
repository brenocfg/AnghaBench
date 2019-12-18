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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wps_data {int encr_type; TYPE_1__* wps; } ;
struct TYPE_2__ {int encr_types; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_process_encr_type_flags(struct wps_data *wps, const u8 *encr)
{
	u16 encr_types;

	if (encr == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: No Encryption Type flags "
			   "received");
		return -1;
	}

	encr_types = WPA_GET_BE16(encr);

	wpa_printf(MSG_DEBUG,  "WPS: Enrollee Encryption Type flags 0x%x",
		   encr_types);
	wps->encr_type = wps->wps->encr_types & encr_types;
	if (wps->encr_type == 0) {
		wpa_printf(MSG_DEBUG,  "WPS: No match in supported "
			   "encryption types (own 0x%x Enrollee 0x%x)",
			   wps->wps->encr_types, encr_types);
#ifdef WPS_WORKAROUNDS
		/*
		 * Some deployed implementations seem to advertise incorrect
		 * information in this attribute. For example, Linksys WRT350N
		 * seems to have a byteorder bug that breaks this negotiation.
		 * In order to interoperate with existing implementations,
		 * assume that the Enrollee supports everything we do.
		 */
		wpa_printf(MSG_DEBUG,  "WPS: Workaround - assume Enrollee "
			   "does not advertise supported encryption types "
			   "correctly");
		wps->encr_type = wps->wps->encr_types;
#else /* WPS_WORKAROUNDS */
		return -1;
#endif /* WPS_WORKAROUNDS */
	}

	return 0;
}