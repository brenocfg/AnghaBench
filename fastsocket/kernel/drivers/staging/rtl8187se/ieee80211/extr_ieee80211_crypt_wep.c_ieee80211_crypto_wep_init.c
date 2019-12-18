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

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_crypt_wep ; 
 int ieee80211_register_crypto_ops (int /*<<< orphan*/ *) ; 

int ieee80211_crypto_wep_init(void)
{
	return ieee80211_register_crypto_ops(&ieee80211_crypt_wep);
}