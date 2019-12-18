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
struct TYPE_2__ {int /*<<< orphan*/ * seq; } ;
struct wpa_sm {scalar_t__ group_cipher; int key_entry_valid; scalar_t__ pairwise_cipher; int /*<<< orphan*/  bssid; TYPE_1__ install_gtk; } ;
struct wpa_gtk_data {int gtk_len; int keyidx; int tx; int key_rsc_len; int alg; int /*<<< orphan*/ * gtk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WPA_CIPHER_NONE ; 
 scalar_t__ WPA_CIPHER_TKIP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpa_sm_set_key (TYPE_1__*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 

int   wpa_supplicant_install_gtk(struct wpa_sm *sm,
                      struct wpa_gtk_data *gd)
{
    u8 *_gtk = gd->gtk;
    u8 gtk_buf[32];
       u8 *key_rsc=(sm->install_gtk).seq;
       
    wpa_hexdump(MSG_DEBUG, "WPA: Group Key", gd->gtk, gd->gtk_len);

    #ifdef DEBUG_PRINT    
    wpa_printf(MSG_DEBUG, "WPA: Installing GTK to the driver "
           "(keyidx=%d tx=%d len=%d).\n", gd->keyidx, gd->tx,
           gd->gtk_len);
    #endif    
    wpa_hexdump(MSG_DEBUG, "WPA: RSC", key_rsc, gd->key_rsc_len);
    if (sm->group_cipher == WPA_CIPHER_TKIP) {
        /* Swap Tx/Rx keys for Michael MIC */
        memcpy(gtk_buf, gd->gtk, 16);
        memcpy(gtk_buf + 16, gd->gtk + 16, 8);
        memcpy(gtk_buf + 24, gd->gtk + 24, 8);
        _gtk = gtk_buf;
    }
    //now only use keycache entry1 for group key
    sm->key_entry_valid = gd->keyidx;
    if (sm->pairwise_cipher == WPA_CIPHER_NONE) {
        if (wpa_sm_set_key(&(sm->install_gtk), gd->alg,
                   sm->bssid, //(u8 *) "\xff\xff\xff\xff\xff\xff",
                   gd->keyidx, 1, key_rsc, gd->key_rsc_len,
                   _gtk, gd->gtk_len,sm->key_entry_valid) < 0) {
            #ifdef DEBUG_PRINT           
            wpa_printf(MSG_DEBUG, "WPA: Failed to set "
                   "GTK to the driver (Group only).");
            #endif    
            return -1;
        }
    } else if (wpa_sm_set_key(&(sm->install_gtk), gd->alg,
                  sm->bssid, //(u8 *) "\xff\xff\xff\xff\xff\xff",
                  gd->keyidx, gd->tx, key_rsc, gd->key_rsc_len,
                  _gtk, gd->gtk_len, sm->key_entry_valid) < 0) {
        #ifdef DEBUG_PRINT          
        wpa_printf(MSG_DEBUG, "WPA: Failed to set GTK to "
               "the driver (alg=%d keylen=%d keyidx=%d)",
               gd->alg, gd->gtk_len, gd->keyidx);
        #endif    
        return -1;
    }

    return 0;
}