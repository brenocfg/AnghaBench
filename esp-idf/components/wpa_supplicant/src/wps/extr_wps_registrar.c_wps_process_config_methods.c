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
struct wps_data {int use_psk_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int WPS_CONFIG_DISPLAY ; 
 int WPS_CONFIG_ETHERNET ; 
 int WPS_CONFIG_EXT_NFC_TOKEN ; 
 int WPS_CONFIG_INT_NFC_TOKEN ; 
 int WPS_CONFIG_KEYPAD ; 
 int WPS_CONFIG_LABEL ; 
 int WPS_CONFIG_NFC_INTERFACE ; 
 int WPS_CONFIG_PUSHBUTTON ; 
 int WPS_CONFIG_USBA ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_process_config_methods(struct wps_data *wps, const u8 *methods)
{
	u16 m;

	if (methods == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: No Config Methods received");
		return -1;
	}

	m = WPA_GET_BE16(methods);

	wpa_printf(MSG_DEBUG,  "WPS: Enrollee Config Methods 0x%x"
		   "%s%s%s%s%s%s%s%s%s", m,
		   m & WPS_CONFIG_USBA ? " [USBA]" : "",
		   m & WPS_CONFIG_ETHERNET ? " [Ethernet]" : "",
		   m & WPS_CONFIG_LABEL ? " [Label]" : "",
		   m & WPS_CONFIG_DISPLAY ? " [Display]" : "",
		   m & WPS_CONFIG_EXT_NFC_TOKEN ? " [Ext NFC Token]" : "",
		   m & WPS_CONFIG_INT_NFC_TOKEN ? " [Int NFC Token]" : "",
		   m & WPS_CONFIG_NFC_INTERFACE ? " [NFC]" : "",
		   m & WPS_CONFIG_PUSHBUTTON ? " [PBC]" : "",
		   m & WPS_CONFIG_KEYPAD ? " [Keypad]" : "");

	if (!(m & WPS_CONFIG_DISPLAY) && !wps->use_psk_key) {
		/*
		 * The Enrollee does not have a display so it is unlikely to be
		 * able to show the passphrase to a user and as such, could
		 * benefit from receiving PSK to reduce key derivation time.
		 */
		wpa_printf(MSG_DEBUG,  "WPS: Prefer PSK format key due to "
			   "Enrollee not supporting display");
		wps->use_psk_key = 1;
	}

	return 0;
}