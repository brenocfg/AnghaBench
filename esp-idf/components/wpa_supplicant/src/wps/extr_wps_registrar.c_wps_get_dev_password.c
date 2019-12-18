#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wps_data {size_t dev_password_len; int /*<<< orphan*/ * dev_password; int /*<<< orphan*/  peer_dev; int /*<<< orphan*/  uuid_e; TYPE_2__* wps; TYPE_1__* nfc_pw_token; scalar_t__ pbc; } ;
struct TYPE_4__ {int /*<<< orphan*/  registrar; } ;
struct TYPE_3__ {size_t dev_pw_len; int /*<<< orphan*/ * dev_pw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 scalar_t__ os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_cb_pin_needed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wps_registrar_get_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int wps_get_dev_password(struct wps_data *wps)
{
	const u8 *pin;
	size_t pin_len = 0;

	os_free(wps->dev_password);
	wps->dev_password = NULL;

	if (wps->pbc) {
		wpa_printf(MSG_DEBUG,  "WPS: Use default PIN for PBC");
		pin = (const u8 *) "00000000";
		pin_len = 8;
#ifdef CONFIG_WPS_NFC
	} else if (wps->nfc_pw_token) {
		wpa_printf(MSG_DEBUG,  "WPS: Use OOB Device Password from NFC "
			   "Password Token");
		pin = wps->nfc_pw_token->dev_pw;
		pin_len = wps->nfc_pw_token->dev_pw_len;
#endif /* CONFIG_WPS_NFC */
	} else {
#ifdef CONFIG_WPS_PIN

		pin = wps_registrar_get_pin(wps->wps->registrar, wps->uuid_e,
					    &pin_len);
	}
	if (pin == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: No Device Password available for "
			   "the Enrollee");
		wps_cb_pin_needed(wps->wps->registrar, wps->uuid_e,
				  &wps->peer_dev);
		return -1;
#endif
	}

	wps->dev_password = (u8 *)os_malloc(pin_len);
	if (wps->dev_password == NULL)
		return -1;
	os_memcpy(wps->dev_password, pin, pin_len);
	wps->dev_password_len = pin_len;

	return 0;
}