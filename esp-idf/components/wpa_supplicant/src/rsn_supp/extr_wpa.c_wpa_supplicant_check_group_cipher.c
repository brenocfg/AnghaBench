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
typedef  enum wpa_alg { ____Placeholder_wpa_alg } wpa_alg ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_ALG_CCMP ; 
 int WPA_ALG_TKIP ; 
 int WPA_ALG_WEP104 ; 
 int WPA_ALG_WEP40 ; 
#define  WPA_CIPHER_CCMP 131 
#define  WPA_CIPHER_TKIP 130 
#define  WPA_CIPHER_WEP104 129 
#define  WPA_CIPHER_WEP40 128 
 int /*<<< orphan*/  wpa_cipher_txt (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

int   wpa_supplicant_check_group_cipher(int group_cipher,
                         int keylen, int maxkeylen,
                         int *key_rsc_len,
                         enum wpa_alg *alg)
{
    int ret = 0;

    switch (group_cipher) {
    case WPA_CIPHER_CCMP:
        if (keylen != 16 || maxkeylen < 16) {
            ret = -1;
            break;
        }
        *key_rsc_len = 6;
        *alg = WPA_ALG_CCMP;
        break;
    case WPA_CIPHER_TKIP:
        if (keylen != 32 || maxkeylen < 32) {
            ret = -1;
            break;
        }
        *key_rsc_len = 6;
        *alg = WPA_ALG_TKIP;
        break;
    case WPA_CIPHER_WEP104:
        if (keylen != 13 || maxkeylen < 13) {
            ret = -1;
            break;
        }
        *key_rsc_len = 0;
        *alg = WPA_ALG_WEP104;
        break;
    case WPA_CIPHER_WEP40:
        if (keylen != 5 || maxkeylen < 5) {
            ret = -1;
            break;
        }
        *key_rsc_len = 0;
        *alg = WPA_ALG_WEP40;
        break;
    default:
        #ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "WPA: Unsupported Group Cipher %d",
               group_cipher);
        #endif
        return -1;
    }

    if (ret < 0 ) {
        #ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "WPA: Unsupported %s Group Cipher key "
               "length %d (%d).",
               wpa_cipher_txt(group_cipher), keylen, maxkeylen);
        #endif    
    }

    return ret;
}