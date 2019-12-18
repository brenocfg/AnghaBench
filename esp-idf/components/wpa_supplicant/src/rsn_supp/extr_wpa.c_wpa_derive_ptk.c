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
struct wpa_sm {scalar_t__ pairwise_cipher; int /*<<< orphan*/  key_mgmt; int /*<<< orphan*/  snonce; int /*<<< orphan*/  bssid; int /*<<< orphan*/  own_addr; int /*<<< orphan*/  pmk_len; int /*<<< orphan*/  pmk; } ;
struct wpa_ptk {int dummy; } ;
struct wpa_eapol_key {int /*<<< orphan*/  key_nonce; } ;

/* Variables and functions */
 scalar_t__ WPA_CIPHER_CCMP ; 
 int /*<<< orphan*/  wpa_key_mgmt_sha256 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_pmk_to_ptk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

int   wpa_derive_ptk(struct wpa_sm *sm, const unsigned char *src_addr,
              const struct wpa_eapol_key *key,
              struct wpa_ptk *ptk)
{
    size_t ptk_len = sm->pairwise_cipher == WPA_CIPHER_CCMP ? 48 : 64;

    wpa_pmk_to_ptk(sm->pmk, sm->pmk_len, "Pairwise key expansion",
               sm->own_addr, sm->bssid, sm->snonce, key->key_nonce,
               (u8 *) ptk, ptk_len,
               wpa_key_mgmt_sha256(sm->key_mgmt));
    return 0;
}