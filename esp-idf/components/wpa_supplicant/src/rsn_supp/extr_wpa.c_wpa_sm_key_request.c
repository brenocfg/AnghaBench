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
struct TYPE_2__ {int /*<<< orphan*/  kck; } ;
struct wpa_sm {scalar_t__ pairwise_cipher; scalar_t__ proto; TYPE_1__ ptk; scalar_t__ ptk_set; int /*<<< orphan*/  request_counter; int /*<<< orphan*/  key_mgmt; } ;
struct wpa_eapol_key {int /*<<< orphan*/ * key_mic; int /*<<< orphan*/  key_data_length; int /*<<< orphan*/  replay_counter; int /*<<< orphan*/  key_length; int /*<<< orphan*/  key_info; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAPOL_KEY_TYPE_RSN ; 
 int /*<<< orphan*/  EAPOL_KEY_TYPE_WPA ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_EAPOL ; 
 int /*<<< orphan*/  IEEE802_1X_TYPE_EAPOL_KEY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WPA_CIPHER_CCMP ; 
 int WPA_KEY_INFO_ERROR ; 
 int WPA_KEY_INFO_KEY_TYPE ; 
 int WPA_KEY_INFO_MIC ; 
 int WPA_KEY_INFO_REQUEST ; 
 int WPA_KEY_INFO_SECURE ; 
 int WPA_KEY_INFO_TYPE_AES_128_CMAC ; 
 int WPA_KEY_INFO_TYPE_HMAC_MD5_RC4 ; 
 int WPA_KEY_INFO_TYPE_HMAC_SHA1_AES ; 
 scalar_t__ WPA_PROTO_RSN ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WPA_REPLAY_COUNTER_LEN ; 
 int /*<<< orphan*/  inc_byte_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_eapol_key_send (struct wpa_sm*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ wpa_key_mgmt_ft (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_sha256 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpa_sm_alloc_eapol (struct wpa_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,size_t*,void*) ; 
 int /*<<< orphan*/  wpa_sm_free_eapol (int /*<<< orphan*/ *) ; 
 scalar_t__ wpa_sm_get_bssid (struct wpa_sm*,int /*<<< orphan*/ *) ; 

void   wpa_sm_key_request(struct wpa_sm *sm, int error, int pairwise)
{
    size_t rlen;
    struct wpa_eapol_key *reply;
    int key_info, ver;
    u8 bssid[ETH_ALEN], *rbuf;

    if (wpa_key_mgmt_ft(sm->key_mgmt) || wpa_key_mgmt_sha256(sm->key_mgmt))
        ver = WPA_KEY_INFO_TYPE_AES_128_CMAC;
    else if (sm->pairwise_cipher == WPA_CIPHER_CCMP)
        ver = WPA_KEY_INFO_TYPE_HMAC_SHA1_AES;
    else
        ver = WPA_KEY_INFO_TYPE_HMAC_MD5_RC4;

    if (wpa_sm_get_bssid(sm, bssid) < 0) {
        #ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "Failed to read BSSID for EAPOL-Key "
               "request");
        #endif    
        return;
    }

    rbuf = wpa_sm_alloc_eapol(sm, IEEE802_1X_TYPE_EAPOL_KEY, NULL,
                  sizeof(*reply), &rlen, (void *) &reply);
    if (rbuf == NULL)
        return;

    reply->type = sm->proto == WPA_PROTO_RSN ?
        EAPOL_KEY_TYPE_RSN : EAPOL_KEY_TYPE_WPA;
    key_info = WPA_KEY_INFO_REQUEST | ver;
    if (sm->ptk_set)
        key_info |= WPA_KEY_INFO_MIC;
    if (error)
        key_info |= WPA_KEY_INFO_ERROR|WPA_KEY_INFO_SECURE;
    if (pairwise)
        key_info |= WPA_KEY_INFO_KEY_TYPE;
    WPA_PUT_BE16(reply->key_info, key_info);
    WPA_PUT_BE16(reply->key_length, 0);
    memcpy(reply->replay_counter, sm->request_counter,
          WPA_REPLAY_COUNTER_LEN);
    inc_byte_array(sm->request_counter, WPA_REPLAY_COUNTER_LEN);

    WPA_PUT_BE16(reply->key_data_length, 0);

   #ifdef DEBUG_PRINT    
    wpa_printf(MSG_DEBUG, "WPA: Sending EAPOL-Key Request (error=%d "
           "pairwise=%d ptk_set=%d len=%lu)",
           error, pairwise, sm->ptk_set, (unsigned long) rlen);
   #endif
    wpa_eapol_key_send(sm, sm->ptk.kck, ver, bssid, ETH_P_EAPOL,
               rbuf, rlen, key_info & WPA_KEY_INFO_MIC ?
               reply->key_mic : NULL);
    wpa_sm_free_eapol(rbuf);
}