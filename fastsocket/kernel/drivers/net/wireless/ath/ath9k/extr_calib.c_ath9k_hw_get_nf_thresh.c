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
struct ath_hw {TYPE_1__* eep_ops; } ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_eeprom ) (struct ath_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EEP_NFTHRESH_2 ; 
 int /*<<< orphan*/  EEP_NFTHRESH_5 ; 
#define  IEEE80211_BAND_2GHZ 129 
#define  IEEE80211_BAND_5GHZ 128 
 int /*<<< orphan*/  stub1 (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ath_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath9k_hw_get_nf_thresh(struct ath_hw *ah,
				   enum ieee80211_band band,
				   int16_t *nft)
{
	switch (band) {
	case IEEE80211_BAND_5GHZ:
		*nft = (int8_t)ah->eep_ops->get_eeprom(ah, EEP_NFTHRESH_5);
		break;
	case IEEE80211_BAND_2GHZ:
		*nft = (int8_t)ah->eep_ops->get_eeprom(ah, EEP_NFTHRESH_2);
		break;
	default:
		BUG_ON(1);
		return false;
	}

	return true;
}