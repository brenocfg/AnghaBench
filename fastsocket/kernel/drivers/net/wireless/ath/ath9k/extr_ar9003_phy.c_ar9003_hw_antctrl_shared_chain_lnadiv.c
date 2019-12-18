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
typedef  int u8 ;
typedef  int u32 ;
struct ath_hw {int shared_chain_lnadiv; scalar_t__ curchan; TYPE_1__* eep_ops; } ;
struct TYPE_2__ {int (* get_eeprom ) (struct ath_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AR_ANT_DIV_CTRL_ALL ; 
 int AR_ANT_DIV_CTRL_ALL_S ; 
 int AR_ANT_DIV_ENABLE ; 
 int /*<<< orphan*/  AR_BTCOEX_WL_LNADIV ; 
 int AR_BTCOEX_WL_LNADIV_FORCE_ON ; 
 int AR_FAST_DIV_ENABLE ; 
 int AR_FAST_DIV_ENABLE_S ; 
 int AR_PHY_ANT_DIV_ALT_GAINTB ; 
 int AR_PHY_ANT_DIV_ALT_LNACONF ; 
 int AR_PHY_ANT_DIV_ALT_LNACONF_S ; 
 int AR_PHY_ANT_DIV_LNA1 ; 
 int AR_PHY_ANT_DIV_LNA2 ; 
 int AR_PHY_ANT_DIV_LNADIV ; 
 int AR_PHY_ANT_DIV_LNADIV_S ; 
 int AR_PHY_ANT_DIV_MAIN_GAINTB ; 
 int AR_PHY_ANT_DIV_MAIN_LNACONF ; 
 int AR_PHY_ANT_DIV_MAIN_LNACONF_S ; 
 int AR_PHY_ANT_SW_RX_PROT_S ; 
 int /*<<< orphan*/  AR_PHY_CCK_DETECT ; 
 int /*<<< orphan*/  AR_PHY_MC_GAIN_CTRL ; 
 int /*<<< orphan*/  AR_PHY_RESTART ; 
 int AR_PHY_RESTART_ENABLE_DIV_M2FLAG ; 
 int /*<<< orphan*/  AR_SREV_9565 (struct ath_hw*) ; 
 int /*<<< orphan*/  EEP_ANT_DIV_CTL1 ; 
 scalar_t__ IS_CHAN_2GHZ (scalar_t__) ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ath_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9003_hw_antctrl_shared_chain_lnadiv(struct ath_hw *ah,
						  bool enable)
{
	u8 ant_div_ctl1;
	u32 regval;

	if (!AR_SREV_9565(ah))
		return;

	ah->shared_chain_lnadiv = enable;
	ant_div_ctl1 = ah->eep_ops->get_eeprom(ah, EEP_ANT_DIV_CTL1);

	regval = REG_READ(ah, AR_PHY_MC_GAIN_CTRL);
	regval &= (~AR_ANT_DIV_CTRL_ALL);
	regval |= (ant_div_ctl1 & 0x3f) << AR_ANT_DIV_CTRL_ALL_S;
	regval &= ~AR_PHY_ANT_DIV_LNADIV;
	regval |= ((ant_div_ctl1 >> 6) & 0x1) << AR_PHY_ANT_DIV_LNADIV_S;

	if (enable)
		regval |= AR_ANT_DIV_ENABLE;

	REG_WRITE(ah, AR_PHY_MC_GAIN_CTRL, regval);

	regval = REG_READ(ah, AR_PHY_CCK_DETECT);
	regval &= ~AR_FAST_DIV_ENABLE;
	regval |= ((ant_div_ctl1 >> 7) & 0x1) << AR_FAST_DIV_ENABLE_S;

	if (enable)
		regval |= AR_FAST_DIV_ENABLE;

	REG_WRITE(ah, AR_PHY_CCK_DETECT, regval);

	if (enable) {
		REG_SET_BIT(ah, AR_PHY_MC_GAIN_CTRL,
			    (1 << AR_PHY_ANT_SW_RX_PROT_S));
		if (ah->curchan && IS_CHAN_2GHZ(ah->curchan))
			REG_SET_BIT(ah, AR_PHY_RESTART,
				    AR_PHY_RESTART_ENABLE_DIV_M2FLAG);
		REG_SET_BIT(ah, AR_BTCOEX_WL_LNADIV,
			    AR_BTCOEX_WL_LNADIV_FORCE_ON);
	} else {
		REG_CLR_BIT(ah, AR_PHY_MC_GAIN_CTRL, AR_ANT_DIV_ENABLE);
		REG_CLR_BIT(ah, AR_PHY_MC_GAIN_CTRL,
			    (1 << AR_PHY_ANT_SW_RX_PROT_S));
		REG_CLR_BIT(ah, AR_PHY_CCK_DETECT, AR_FAST_DIV_ENABLE);
		REG_CLR_BIT(ah, AR_BTCOEX_WL_LNADIV,
			    AR_BTCOEX_WL_LNADIV_FORCE_ON);

		regval = REG_READ(ah, AR_PHY_MC_GAIN_CTRL);
		regval &= ~(AR_PHY_ANT_DIV_MAIN_LNACONF |
			AR_PHY_ANT_DIV_ALT_LNACONF |
			AR_PHY_ANT_DIV_MAIN_GAINTB |
			AR_PHY_ANT_DIV_ALT_GAINTB);
		regval |= (AR_PHY_ANT_DIV_LNA1 << AR_PHY_ANT_DIV_MAIN_LNACONF_S);
		regval |= (AR_PHY_ANT_DIV_LNA2 << AR_PHY_ANT_DIV_ALT_LNACONF_S);
		REG_WRITE(ah, AR_PHY_MC_GAIN_CTRL, regval);
	}
}