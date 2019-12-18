#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tfm; } ;
struct TYPE_5__ {int /*<<< orphan*/  tfm; } ;
struct TYPE_8__ {TYPE_3__ aes_cmac; TYPE_1__ ccmp; } ;
struct TYPE_6__ {scalar_t__ cipher; } ;
struct ieee80211_key {TYPE_4__ u; TYPE_2__ conf; } ;

/* Variables and functions */
 scalar_t__ WLAN_CIPHER_SUITE_AES_CMAC ; 
 scalar_t__ WLAN_CIPHER_SUITE_CCMP ; 
 int /*<<< orphan*/  ieee80211_aes_cmac_key_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_aes_key_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_key*) ; 

__attribute__((used)) static void ieee80211_key_free_common(struct ieee80211_key *key)
{
	if (key->conf.cipher == WLAN_CIPHER_SUITE_CCMP)
		ieee80211_aes_key_free(key->u.ccmp.tfm);
	if (key->conf.cipher == WLAN_CIPHER_SUITE_AES_CMAC)
		ieee80211_aes_cmac_key_free(key->u.aes_cmac.tfm);
	kfree(key);
}