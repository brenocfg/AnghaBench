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
struct ath_common {int keymax; int crypt_caps; int /*<<< orphan*/  keymap; } ;

/* Variables and functions */
 int ATH_CRYPT_CAP_MIC_COMBINED ; 
 int IEEE80211_WEP_NKID ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath_reserve_key_cache_slot_tkip(struct ath_common *common)
{
	int i;

	for (i = IEEE80211_WEP_NKID; i < common->keymax / 2; i++) {
		if (test_bit(i, common->keymap) ||
		    test_bit(i + 64, common->keymap))
			continue; /* At least one part of TKIP key allocated */
		if (!(common->crypt_caps & ATH_CRYPT_CAP_MIC_COMBINED) &&
		    (test_bit(i + 32, common->keymap) ||
		     test_bit(i + 64 + 32, common->keymap)))
			continue; /* At least one part of TKIP key allocated */

		/* Found a free slot for a TKIP key */
		return i;
	}
	return -1;
}