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
struct wpa_gtk_data {int dummy; } ;
struct wpa_sm {scalar_t__ proto; int /*<<< orphan*/  key_info; struct wpa_gtk_data gd; } ;
struct wpa_eapol_key {int /*<<< orphan*/  key_data_length; int /*<<< orphan*/  key_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_REASON_UNSPECIFIED ; 
 int /*<<< orphan*/  WPA_GET_BE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPA_GROUP_HANDSHAKE ; 
 scalar_t__ WPA_PROTO_RSN ; 
 int /*<<< orphan*/  memset (struct wpa_gtk_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_sm_deauthenticate (struct wpa_sm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_sm_set_seq (struct wpa_sm*,struct wpa_eapol_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_sm_set_state (int /*<<< orphan*/ ) ; 
 int wpa_supplicant_process_1_of_2_rsn (struct wpa_sm*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_gtk_data*) ; 
 int wpa_supplicant_process_1_of_2_wpa (struct wpa_sm*,struct wpa_eapol_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct wpa_gtk_data*) ; 
 scalar_t__ wpa_supplicant_send_2_of_2 (struct wpa_sm*,struct wpa_eapol_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void   wpa_supplicant_process_1_of_2(struct wpa_sm *sm,
                      const unsigned char *src_addr,
                      struct wpa_eapol_key *key,
                      int extra_len, u16 ver)
{
    u16 key_info, keydatalen;
    int  ret;
    struct wpa_gtk_data *gd=&(sm->gd);

    memset(gd, 0, sizeof(struct wpa_gtk_data));

    wpa_printf(MSG_DEBUG, "WPA 1/2 Group Key Handshake\n");
    
    key_info = WPA_GET_BE16(key->key_info);
    keydatalen = WPA_GET_BE16(key->key_data_length);

    if (sm->proto == WPA_PROTO_RSN) {
        ret = wpa_supplicant_process_1_of_2_rsn(sm,
                            (const u8 *) (key + 1),
                            keydatalen, key_info,
                            gd);
    } else {
        ret = wpa_supplicant_process_1_of_2_wpa(sm, key, keydatalen,
                            key_info, extra_len,
                            ver, gd);
    }

    wpa_sm_set_state(WPA_GROUP_HANDSHAKE);

    if (ret)
        goto failed;

    /*before callback, set seq for add param difficult in callback*/ 
    wpa_sm_set_seq(sm, key, 0);
    sm->key_info=key_info;

    if (wpa_supplicant_send_2_of_2(sm, key, ver, key_info))
        goto failed;

    return;

failed:
    wpa_sm_deauthenticate(sm, WLAN_REASON_UNSPECIFIED);
}