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
struct wps_credential {scalar_t__ auth_type; scalar_t__ encr_type; size_t key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WPS_ENCR_NONE ; 
 scalar_t__ WPS_WIFI_AUTH_OPEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wps_process_cred_network_key(struct wps_credential *cred,
					const u8 *key, size_t key_len)
{
	if (key == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: Credential did not include "
			   "Network Key");
		if (cred->auth_type == WPS_WIFI_AUTH_OPEN &&
		    cred->encr_type == WPS_ENCR_NONE) {
			wpa_printf(MSG_DEBUG,  "WPS: Workaround - Allow "
				   "missing mandatory Network Key attribute "
				   "for open network");
			return 0;
		}
		return -1;
	}

	wpa_hexdump_key(MSG_DEBUG, "WPS: Network Key", key, key_len);
	if (key_len <= sizeof(cred->key)) {
		os_memcpy(cred->key, key, key_len);
		cred->key_len = key_len;
	}

	return 0;
}