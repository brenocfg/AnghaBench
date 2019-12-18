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
typedef  int /*<<< orphan*/  u16 ;
struct ath_hw {int misc_mode; } ;
struct ath_common {int keymax; int /*<<< orphan*/  crypt_caps; } ;

/* Variables and functions */
 int AR_KEYTABLE_SIZE ; 
 int AR_PCU_MIC_NEW_LOC_ENA ; 
 int /*<<< orphan*/  ATH_CRYPT_CAP_MIC_COMBINED ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_hw_keyreset (struct ath_common*,int /*<<< orphan*/ ) ; 

void ath9k_cmn_init_crypto(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	int i = 0;

	/* Get the hardware key cache size. */
	common->keymax = AR_KEYTABLE_SIZE;

	/*
	 * Check whether the separate key cache entries
	 * are required to handle both tx+rx MIC keys.
	 * With split mic keys the number of stations is limited
	 * to 27 otherwise 59.
	 */
	if (ah->misc_mode & AR_PCU_MIC_NEW_LOC_ENA)
		common->crypt_caps |= ATH_CRYPT_CAP_MIC_COMBINED;

	/*
	 * Reset the key cache since some parts do not
	 * reset the contents on initial power up.
	 */
	for (i = 0; i < common->keymax; i++)
		ath_hw_keyreset(common, (u16) i);
}