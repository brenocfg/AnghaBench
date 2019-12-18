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
struct ieee80211_key_conf {int cipher; } ;
typedef  enum cipher { ____Placeholder_cipher } cipher ;

/* Variables and functions */
 int CIPHER_AES ; 
 int CIPHER_NONE ; 
 int CIPHER_TKIP ; 
 int CIPHER_WEP128 ; 
 int CIPHER_WEP64 ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 

enum cipher rt2x00crypto_key_to_cipher(struct ieee80211_key_conf *key)
{
	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
		return CIPHER_WEP64;
	case WLAN_CIPHER_SUITE_WEP104:
		return CIPHER_WEP128;
	case WLAN_CIPHER_SUITE_TKIP:
		return CIPHER_TKIP;
	case WLAN_CIPHER_SUITE_CCMP:
		return CIPHER_AES;
	default:
		return CIPHER_NONE;
	}
}