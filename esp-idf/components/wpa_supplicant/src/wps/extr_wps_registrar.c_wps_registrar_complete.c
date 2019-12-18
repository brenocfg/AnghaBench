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
struct wps_registrar {int /*<<< orphan*/  pbc_ignore_uuid; int /*<<< orphan*/  pbc_ignore_start; scalar_t__ pbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_UUID_LEN ; 
 int /*<<< orphan*/  os_get_time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ wps_registrar_invalidate_wildcard_pin (struct wps_registrar*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wps_registrar_pbc_completed (struct wps_registrar*) ; 
 int /*<<< orphan*/  wps_registrar_pin_completed (struct wps_registrar*) ; 
 int /*<<< orphan*/  wps_registrar_remove_pbc_session (struct wps_registrar*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void wps_registrar_complete(struct wps_registrar *registrar, const u8 *uuid_e,
			    const u8 *dev_pw, size_t dev_pw_len)
{
	if (registrar->pbc) {
		wps_registrar_remove_pbc_session(registrar,
						 uuid_e, NULL);
		wps_registrar_pbc_completed(registrar);
		os_get_time(&registrar->pbc_ignore_start);
		os_memcpy(registrar->pbc_ignore_uuid, uuid_e, WPS_UUID_LEN);
	} else {
#ifdef CONFIG_WPS_PIN
		wps_registrar_pin_completed(registrar);
#endif
	}
#ifdef CONFIG_WPS_PIN
	if (dev_pw &&
	    wps_registrar_invalidate_wildcard_pin(registrar, dev_pw,
						  dev_pw_len) == 0) {
		wpa_hexdump_key(MSG_DEBUG, "WPS: Invalidated wildcard PIN",
				dev_pw, dev_pw_len);
	}
#endif
}