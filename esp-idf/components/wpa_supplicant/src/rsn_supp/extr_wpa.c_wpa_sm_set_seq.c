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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {scalar_t__* seq; } ;
struct TYPE_3__ {scalar_t__* seq; } ;
struct wpa_sm {scalar_t__ proto; TYPE_2__ install_gtk; TYPE_1__ install_ptk; } ;
struct wpa_eapol_key {scalar_t__* key_rsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_KEY_RSC_LEN ; 
 scalar_t__ WPA_PROTO_RSN ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  os_bzero (scalar_t__*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 

void   wpa_sm_set_seq(struct wpa_sm *sm, struct wpa_eapol_key *key, u8 isptk)
{    
    u8 *key_rsc, *seq;
    u8 null_rsc[WPA_KEY_RSC_LEN];
    
    os_bzero(null_rsc, WPA_KEY_RSC_LEN);

    if (sm->proto == WPA_PROTO_RSN) {
        key_rsc = null_rsc;
    } else {
        key_rsc = key->key_rsc;
        wpa_hexdump(MSG_DEBUG, "WPA: RSC", key_rsc, WPA_KEY_RSC_LEN);
    }

    seq=(isptk) ? (sm->install_ptk).seq : (sm->install_gtk).seq;  
    memcpy(seq, key_rsc, WPA_KEY_RSC_LEN);
}