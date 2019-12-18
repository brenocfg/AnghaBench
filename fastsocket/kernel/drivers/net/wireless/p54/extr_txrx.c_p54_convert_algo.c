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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  P54_CRYPTO_AESCCMP ; 
 int /*<<< orphan*/  P54_CRYPTO_TKIPMICHAEL ; 
 int /*<<< orphan*/  P54_CRYPTO_WEP ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 

__attribute__((used)) static u8 p54_convert_algo(u32 cipher)
{
	switch (cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		return P54_CRYPTO_WEP;
	case WLAN_CIPHER_SUITE_TKIP:
		return P54_CRYPTO_TKIPMICHAEL;
	case WLAN_CIPHER_SUITE_CCMP:
		return P54_CRYPTO_AESCCMP;
	default:
		return 0;
	}
}