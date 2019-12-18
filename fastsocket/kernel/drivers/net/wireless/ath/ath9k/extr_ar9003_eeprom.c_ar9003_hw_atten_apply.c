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
struct ath_hw {int rxchainmask; int txchainmask; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 unsigned long AR_PHY_EXT_ATTEN_CTL_0 ; 
 unsigned long AR_PHY_EXT_ATTEN_CTL_1 ; 
 unsigned long AR_PHY_EXT_ATTEN_CTL_2 ; 
 int /*<<< orphan*/  AR_PHY_EXT_ATTEN_CTL_XATTEN1_DB ; 
 int /*<<< orphan*/  AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_hw_atten_chain_get (struct ath_hw*,int,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ar9003_hw_atten_chain_get_margin (struct ath_hw*,int,struct ath9k_channel*) ; 

__attribute__((used)) static void ar9003_hw_atten_apply(struct ath_hw *ah, struct ath9k_channel *chan)
{
	int i;
	u16 value;
	unsigned long ext_atten_reg[3] = {AR_PHY_EXT_ATTEN_CTL_0,
					  AR_PHY_EXT_ATTEN_CTL_1,
					  AR_PHY_EXT_ATTEN_CTL_2,
					 };

	if ((AR_SREV_9462(ah)) && (ah->rxchainmask == 0x2)) {
		value = ar9003_hw_atten_chain_get(ah, 1, chan);
		REG_RMW_FIELD(ah, ext_atten_reg[0],
			      AR_PHY_EXT_ATTEN_CTL_XATTEN1_DB, value);

		value = ar9003_hw_atten_chain_get_margin(ah, 1, chan);
		REG_RMW_FIELD(ah, ext_atten_reg[0],
			      AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN,
			      value);
	}

	/* Test value. if 0 then attenuation is unused. Don't load anything. */
	for (i = 0; i < 3; i++) {
		if (ah->txchainmask & BIT(i)) {
			value = ar9003_hw_atten_chain_get(ah, i, chan);
			REG_RMW_FIELD(ah, ext_atten_reg[i],
				      AR_PHY_EXT_ATTEN_CTL_XATTEN1_DB, value);

			value = ar9003_hw_atten_chain_get_margin(ah, i, chan);
			REG_RMW_FIELD(ah, ext_atten_reg[i],
				      AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN,
				      value);
		}
	}
}