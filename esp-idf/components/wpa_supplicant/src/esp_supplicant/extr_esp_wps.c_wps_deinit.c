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
struct wps_data {struct wps_data* nfc_pw_token; int /*<<< orphan*/  peer_dev; int /*<<< orphan*/  dh_ctx; struct wps_data* dev_password; int /*<<< orphan*/ * last_msg; int /*<<< orphan*/ * dh_pubkey_r; int /*<<< orphan*/ * dh_pubkey_e; int /*<<< orphan*/ * dh_privkey; scalar_t__ registrar; scalar_t__ wps_pin_revealed; TYPE_1__* wps; } ;
struct TYPE_4__ {struct wps_data* wps; } ;
struct TYPE_3__ {int /*<<< orphan*/  registrar; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dh5_free (int /*<<< orphan*/ ) ; 
 TYPE_2__* gWpsSm ; 
 int /*<<< orphan*/  os_free (struct wps_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wps_dev_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wps_registrar_remove_nfc_pw_token (int /*<<< orphan*/ ,struct wps_data*) ; 

void wps_deinit(void)
{
    struct wps_data *data = gWpsSm->wps;

#ifdef CONFIG_WPS_NFC
    if (data->registrar && data->nfc_pw_token)
        wps_registrar_remove_nfc_pw_token(data->wps->registrar,
                                          data->nfc_pw_token);
#endif /* CONFIG_WPS_NFC */

    if (data->wps_pin_revealed) {
        wpa_printf(MSG_DEBUG,  "WPS: Full PIN information revealed and "
                   "negotiation failed");
    } else if (data->registrar)
        wpa_printf(MSG_DEBUG,  "WPS: register information revealed and "
                   "negotiation failed");
    wpabuf_free(data->dh_privkey);

#ifdef DESP32_WORKAROUND
    /*
     * due to the public key calculated when wps start, it will not calculate anymore even when we build M1 message, also calculate the key need take a long time
     * which would cause WPS fail, so we clean the key after WPS finished .
     */
    data->dh_privkey = NULL;
#endif //DESP32_WORKAROUND

    wpabuf_free(data->dh_pubkey_e);
    wpabuf_free(data->dh_pubkey_r);
    wpabuf_free(data->last_msg);
    os_free(data->dev_password);
    dh5_free(data->dh_ctx);
    wps_dev_deinit(&data->peer_dev);
#ifdef CONFIG_WPS_NFC
    os_free(data->nfc_pw_token);
#endif
    os_free(data);
}