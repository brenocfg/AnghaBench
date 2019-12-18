#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int* ciphers_pairwise; int n_ciphers_pairwise; } ;
struct TYPE_4__ {TYPE_3__ crypto; } ;
struct TYPE_5__ {TYPE_1__ connect; } ;
struct wireless_dev {TYPE_2__ wext; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int IW_AUTH_CIPHER_AES_CMAC ; 
 int IW_AUTH_CIPHER_CCMP ; 
 int IW_AUTH_CIPHER_TKIP ; 
 int IW_AUTH_CIPHER_WEP104 ; 
 int IW_AUTH_CIPHER_WEP40 ; 
 int NL80211_MAX_NR_CIPHER_SUITES ; 
 int WLAN_CIPHER_SUITE_AES_CMAC ; 
 int WLAN_CIPHER_SUITE_CCMP ; 
 int WLAN_CIPHER_SUITE_TKIP ; 
 int WLAN_CIPHER_SUITE_WEP104 ; 
 int WLAN_CIPHER_SUITE_WEP40 ; 

__attribute__((used)) static int cfg80211_set_cipher_pairwise(struct wireless_dev *wdev, u32 cipher)
{
	int nr_ciphers = 0;
	u32 *ciphers_pairwise = wdev->wext.connect.crypto.ciphers_pairwise;

	if (cipher & IW_AUTH_CIPHER_WEP40) {
		ciphers_pairwise[nr_ciphers] = WLAN_CIPHER_SUITE_WEP40;
		nr_ciphers++;
	}

	if (cipher & IW_AUTH_CIPHER_WEP104) {
		ciphers_pairwise[nr_ciphers] = WLAN_CIPHER_SUITE_WEP104;
		nr_ciphers++;
	}

	if (cipher & IW_AUTH_CIPHER_TKIP) {
		ciphers_pairwise[nr_ciphers] = WLAN_CIPHER_SUITE_TKIP;
		nr_ciphers++;
	}

	if (cipher & IW_AUTH_CIPHER_CCMP) {
		ciphers_pairwise[nr_ciphers] = WLAN_CIPHER_SUITE_CCMP;
		nr_ciphers++;
	}

	if (cipher & IW_AUTH_CIPHER_AES_CMAC) {
		ciphers_pairwise[nr_ciphers] = WLAN_CIPHER_SUITE_AES_CMAC;
		nr_ciphers++;
	}

	BUILD_BUG_ON(NL80211_MAX_NR_CIPHER_SUITES < 5);

	wdev->wext.connect.crypto.n_ciphers_pairwise = nr_ciphers;

	return 0;
}