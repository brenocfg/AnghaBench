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
typedef  int /*<<< orphan*/  u16 ;
struct wpa_ptk {int dummy; } ;
struct wpa_sm {scalar_t__ proto; int tptk_set; int key_install; int /*<<< orphan*/  anonce; int /*<<< orphan*/  assoc_wpa_ie_len; int /*<<< orphan*/  assoc_wpa_ie; int /*<<< orphan*/  const* snonce; int /*<<< orphan*/  bssid; scalar_t__ ptk_set; struct wpa_ptk tptk; scalar_t__ renew_snonce; } ;
struct wpa_eapol_key {int /*<<< orphan*/  key_nonce; int /*<<< orphan*/  key_data_length; } ;
struct wpa_eapol_ie_parse {int /*<<< orphan*/  const* pmkid; } ;
typedef  int /*<<< orphan*/  ie ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 size_t PMKID_LEN ; 
 int /*<<< orphan*/  WLAN_REASON_UNSPECIFIED ; 
 scalar_t__ WPA2_AUTH_ENT ; 
 int /*<<< orphan*/  WPA_FIRST_HALF_4WAY_HANDSHAKE ; 
 size_t WPA_GET_BE16 (int /*<<< orphan*/ ) ; 
 size_t WPA_NONCE_LEN ; 
 scalar_t__ WPA_PROTO_RSN ; 
 scalar_t__ esp_wifi_sta_get_prof_authmode_internal () ; 
 scalar_t__ esp_wifi_sta_prof_is_wpa2_internal () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (struct wpa_eapol_ie_parse*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_get_random (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  pmksa_cache_set_current (struct wpa_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_derive_ptk (struct wpa_sm*,unsigned char const*,struct wpa_eapol_key const*,struct wpa_ptk*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_sm_deauthenticate (struct wpa_sm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_sm_set_state (int /*<<< orphan*/ ) ; 
 int wpa_supplicant_get_pmk (struct wpa_sm*,unsigned char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_supplicant_parse_ies (int /*<<< orphan*/  const*,size_t,struct wpa_eapol_ie_parse*) ; 
 scalar_t__ wpa_supplicant_send_2_of_4 (struct wpa_sm*,int /*<<< orphan*/ ,struct wpa_eapol_key const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_ptk*) ; 

void   wpa_supplicant_process_1_of_4(struct wpa_sm *sm,
                      const unsigned char *src_addr,
                      const struct wpa_eapol_key *key,
                      u16 ver)
{
    struct wpa_eapol_ie_parse ie;
    struct wpa_ptk *ptk;
    int res;

    wpa_sm_set_state(WPA_FIRST_HALF_4WAY_HANDSHAKE);

    wpa_printf(MSG_DEBUG, "WPA 1/4-Way Handshake\n");

    memset(&ie, 0, sizeof(ie));

#ifndef CONFIG_NO_WPA2
    if (sm->proto == WPA_PROTO_RSN) {
        /* RSN: msg 1/4 should contain PMKID for the selected PMK */
        const u8 *_buf = (const u8 *) (key + 1);
        size_t len = WPA_GET_BE16(key->key_data_length);    
        wpa_hexdump(MSG_MSGDUMP, "RSN: msg 1/4 key data", _buf, len);
        wpa_supplicant_parse_ies(_buf, len, &ie);
        if (ie.pmkid) {
            wpa_hexdump(MSG_DEBUG, "RSN: PMKID from "
                    "Authenticator", ie.pmkid, PMKID_LEN);
        }
    }
#endif /* CONFIG_NO_WPA2 */
    res = wpa_supplicant_get_pmk(sm, src_addr, ie.pmkid);
       
    if (res == -2) {
          #ifdef DEBUG_PRINT    
         wpa_printf(MSG_DEBUG, "RSN: Do not reply to msg 1/4 - "
               "requesting full EAP authentication");
          #endif     
        return;
    }
    if (res)
        goto failed;

    if (esp_wifi_sta_prof_is_wpa2_internal() 
            && esp_wifi_sta_get_prof_authmode_internal() == WPA2_AUTH_ENT) {
        pmksa_cache_set_current(sm, NULL, sm->bssid, 0, 0);
    }

    if (sm->renew_snonce) {
        if (os_get_random(sm->snonce, WPA_NONCE_LEN)) {
         #ifdef DEBUG_PRINT            
            wpa_printf(MSG_DEBUG, "WPA: Failed to get random data for SNonce");
         #endif     
            goto failed;
        }
         
        sm->renew_snonce = 0;
        wpa_hexdump(MSG_DEBUG, "WPA: Renewed SNonce",
                sm->snonce, WPA_NONCE_LEN);
    }

    /* Calculate PTK which will be stored as a temporary PTK until it has
     * been verified when processing message 3/4. */
    ptk = &sm->tptk;
    wpa_derive_ptk(sm, src_addr, key, ptk);
    /* Supplicant: swap tx/rx Mic keys */
    sm->tptk_set = 1;
    sm->ptk_set = 0;
    sm->key_install = true;

    if (wpa_supplicant_send_2_of_4(sm, sm->bssid, key, ver, sm->snonce,
                       sm->assoc_wpa_ie, sm->assoc_wpa_ie_len,
                       ptk))
        goto failed;

    memcpy(sm->anonce, key->key_nonce, WPA_NONCE_LEN);
    return;

failed:
    wpa_sm_deauthenticate(sm, WLAN_REASON_UNSPECIFIED);
}