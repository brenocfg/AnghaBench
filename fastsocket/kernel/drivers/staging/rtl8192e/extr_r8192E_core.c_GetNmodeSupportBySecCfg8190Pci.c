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
struct r8192_priv {struct ieee80211_device* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int capability; } ;
struct ieee80211_device {int wpa_ie_len; size_t tx_keyidx; int* wpa_ie; scalar_t__ host_encrypt; TYPE_1__ current_network; struct ieee80211_crypt_data** crypt; } ;
struct ieee80211_crypt_data {TYPE_2__* ops; } ;
struct TYPE_6__ {scalar_t__ GroupEncAlgorithm; scalar_t__ PairwiseEncAlgorithm; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ TKIP_Encryption ; 
 scalar_t__ WEP104_Encryption ; 
 scalar_t__ WEP40_Encryption ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int /*<<< orphan*/  ccmp_ie ; 
 int /*<<< orphan*/  ccmp_rsn_ie ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcmp (int*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* pSecInfo ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool GetNmodeSupportBySecCfg8190Pci(struct net_device*dev)
{
#if 1
	struct r8192_priv* priv = ieee80211_priv(dev);
	struct ieee80211_device* ieee = priv->ieee80211;
        int wpa_ie_len= ieee->wpa_ie_len;
        struct ieee80211_crypt_data* crypt;
        int encrypt;

        crypt = ieee->crypt[ieee->tx_keyidx];
        encrypt = (ieee->current_network.capability & WLAN_CAPABILITY_PRIVACY) || (ieee->host_encrypt && crypt && crypt->ops && (0 == strcmp(crypt->ops->name,"WEP")));

	/* simply judge  */
	if(encrypt && (wpa_ie_len == 0)) {
		/* wep encryption, no N mode setting */
		return false;
//	} else if((wpa_ie_len != 0)&&(memcmp(&(ieee->wpa_ie[14]),ccmp_ie,4))) {
	} else if((wpa_ie_len != 0)) {
		/* parse pairwise key type */
		//if((pairwisekey = WEP40)||(pairwisekey = WEP104)||(pairwisekey = TKIP))
		if (((ieee->wpa_ie[0] == 0xdd) && (!memcmp(&(ieee->wpa_ie[14]),ccmp_ie,4))) || ((ieee->wpa_ie[0] == 0x30) && (!memcmp(&ieee->wpa_ie[10],ccmp_rsn_ie, 4))))
			return true;
		else
			return false;
	} else {
		//RT_TRACE(COMP_ERR,"In %s The GroupEncAlgorithm is [4]\n",__FUNCTION__ );
		return true;
	}

#if 0
        //In here we discuss with SD4 David. He think we still can send TKIP in broadcast group key in MCS rate.
        //We can't force in G mode if Pairwie key is AES and group key is TKIP
        if((pSecInfo->GroupEncAlgorithm == WEP104_Encryption) || (pSecInfo->GroupEncAlgorithm == WEP40_Encryption)  ||
           (pSecInfo->PairwiseEncAlgorithm == WEP104_Encryption) ||
           (pSecInfo->PairwiseEncAlgorithm == WEP40_Encryption) || (pSecInfo->PairwiseEncAlgorithm == TKIP_Encryption))
        {
                return  false;
        }
        else
                return true;
#endif
	return true;
#endif
}