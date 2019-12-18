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
typedef  int u8 ;
typedef  int u16 ;
struct wpa_sm {int /*<<< orphan*/  group_cipher; } ;
struct wpa_gtk_data {int gtk_len; int keyidx; int /*<<< orphan*/  gtk; int /*<<< orphan*/  tx; int /*<<< orphan*/  alg; int /*<<< orphan*/  key_rsc_len; } ;
struct wpa_eapol_ie_parse {int const* gtk; int gtk_len; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_KEY_INFO_ENCR_KEY_DATA ; 
 scalar_t__ ieee80211w_set_keys (struct wpa_sm*,struct wpa_eapol_ie_parse*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpa_supplicant_check_group_cipher (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_gtk_tx_bit_workaround (struct wpa_sm*,int) ; 
 int /*<<< orphan*/  wpa_supplicant_parse_ies (int const*,size_t,struct wpa_eapol_ie_parse*) ; 

int   wpa_supplicant_process_1_of_2_rsn(struct wpa_sm *sm,
                         const u8 *keydata,
                         size_t keydatalen,
                         u16 key_info,
                         struct wpa_gtk_data *gd)
{
    int maxkeylen;
    struct wpa_eapol_ie_parse ie;

    wpa_hexdump(MSG_DEBUG, "RSN: msg 1/2 key data", keydata, keydatalen);
    wpa_supplicant_parse_ies(keydata, keydatalen, &ie);
    if (ie.gtk && !(key_info & WPA_KEY_INFO_ENCR_KEY_DATA)) {
        #ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "WPA: GTK IE in unencrypted key data");
      #endif    
        return -1;
    }
    if (ie.gtk == NULL) {
         #ifdef DEBUG_PRINT        
        wpa_printf(MSG_DEBUG, "WPA: No GTK IE in Group Key msg 1/2");
       #endif     
        return -1;
    }
    maxkeylen = gd->gtk_len = ie.gtk_len - 2;

    if (wpa_supplicant_check_group_cipher(sm->group_cipher,
                          gd->gtk_len, maxkeylen,
                          &gd->key_rsc_len, &gd->alg))
        return -1;

    wpa_hexdump(MSG_DEBUG, "RSN: received GTK in group key handshake",
            ie.gtk, ie.gtk_len);
    gd->keyidx = ie.gtk[0] & 0x3;
    gd->tx = wpa_supplicant_gtk_tx_bit_workaround(sm,
                              !!(ie.gtk[0] & BIT(2)));
    if (ie.gtk_len - 2 > sizeof(gd->gtk)) {
         #ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "RSN: Too long GTK in GTK IE "
               "(len=%lu)", (unsigned long) ie.gtk_len - 2);
      #endif     
        return -1;
    }
    memcpy(gd->gtk, ie.gtk + 2, ie.gtk_len - 2);

    if (ieee80211w_set_keys(sm, &ie) < 0)
    {   
        #ifdef DEBUG_PRINT
        wpa_printf(MSG_DEBUG, "RSN: Failed to configure IGTK");
            #endif
    }       
    return 0;
}