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
struct wpa_eapol_key {int /*<<< orphan*/  key_data_length; struct wpa_eapol_key* key_iv; } ;
typedef  struct wpa_eapol_key u8 ;
typedef  int u16 ;
struct TYPE_2__ {struct wpa_eapol_key* kek; } ;
struct wpa_sm {TYPE_1__ ptk; int /*<<< orphan*/  ptk_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_GET_BE16 (int /*<<< orphan*/ ) ; 
 int WPA_KEY_INFO_TYPE_AES_128_CMAC ; 
 int WPA_KEY_INFO_TYPE_HMAC_MD5_RC4 ; 
 int WPA_KEY_INFO_TYPE_HMAC_SHA1_AES ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ aes_unwrap (struct wpa_eapol_key*,int,struct wpa_eapol_key*,struct wpa_eapol_key*) ; 
 int /*<<< orphan*/  memcpy (struct wpa_eapol_key*,struct wpa_eapol_key*,int) ; 
 scalar_t__ rc4_skip (struct wpa_eapol_key*,int,int,struct wpa_eapol_key*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,struct wpa_eapol_key*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int   wpa_supplicant_decrypt_key_data(struct wpa_sm *sm,
                       struct wpa_eapol_key *key, u16 ver)
{
    u16 keydatalen = WPA_GET_BE16(key->key_data_length);

    wpa_hexdump(MSG_DEBUG, "RSN: encrypted key data",
            (u8 *) (key + 1), keydatalen);
    if (!sm->ptk_set) {
        #ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "WPA: PTK not available, "
               "cannot decrypt EAPOL-Key key data.");
        #endif    
        return -1;
    }

    /* Decrypt key data here so that this operation does not need
     * to be implemented separately for each message type. */
    if (ver == WPA_KEY_INFO_TYPE_HMAC_MD5_RC4) {
        u8 ek[32];
        memcpy(ek, key->key_iv, 16);
        memcpy(ek + 16, sm->ptk.kek, 16);
        if (rc4_skip(ek, 32, 256, (u8 *) (key + 1), keydatalen)) {
            #ifdef DEBUG_PRINT
            wpa_printf(MSG_DEBUG, "WPA: RC4 failed");
            #endif
            return -1;
        }
    } else if (ver == WPA_KEY_INFO_TYPE_HMAC_SHA1_AES ||
           ver == WPA_KEY_INFO_TYPE_AES_128_CMAC) {
        u8 *buf;
        if (keydatalen % 8) {
            #ifdef DEBUG_PRINT    
            wpa_printf(MSG_DEBUG, "WPA: Unsupported "
                   "AES-WRAP len %d", keydatalen);
            #endif    
            return -1;
        }
        keydatalen -= 8; /* AES-WRAP adds 8 bytes */
        
        /*replaced by xxx to remove malloc*/
        buf = ((u8 *) (key+1))+ 8;
             /*
        buf = os_wifi_malloc(keydatalen);
        if (buf == NULL) {
            #ifdef DEBUG_PRINT    
            wpa_printf(MSG_DEBUG, "WPA: No memory for "
                   "AES-UNWRAP buffer");
             #endif    
            return -1;
        }
        */
        if (aes_unwrap(sm->ptk.kek, keydatalen / 8,
        				    (u8 *) (key + 1), buf)) {
            #ifdef DEBUG_PRINT    
        	wpa_printf(MSG_DEBUG, "WPA: AES unwrap failed - "
        			"could not decrypt EAPOL-Key key data");
            #endif    
        	return -1;
        }
        memcpy(key + 1, buf, keydatalen);
        WPA_PUT_BE16(key->key_data_length, keydatalen);
    } else {
        #ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "WPA: Unsupported key_info type %d",
               ver);
         #endif    
        return -1;
    }
    wpa_hexdump(MSG_DEBUG, "WPA: decrypted EAPOL-Key key data",
            (u8 *) (key + 1), keydatalen);
    return 0;
}