#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct ieee80211_conf {int dummy; } ;
struct ath_hw {int rxchainmask; int /*<<< orphan*/ * nf_regs; TYPE_2__* caldata; } ;
struct ath_common {TYPE_1__* hw; } ;
struct ath9k_nfcal_hist {scalar_t__ privNF; } ;
struct ath9k_channel {int dummy; } ;
typedef  scalar_t__ s16 ;
typedef  int int32_t ;
struct TYPE_4__ {struct ath9k_nfcal_hist* nfCalHist; } ;
struct TYPE_3__ {struct ieee80211_conf conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANY ; 
 unsigned int AR5416_MAX_CHAINS ; 
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL ; 
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL_ENABLE_NF ; 
 int AR_PHY_AGC_CONTROL_NF ; 
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL_NO_UPDATE_NF ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 unsigned int NUM_NF_READINGS ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_get_default_nf (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  conf_is_ht40 (struct ieee80211_conf*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void ath9k_hw_loadnf(struct ath_hw *ah, struct ath9k_channel *chan)
{
	struct ath9k_nfcal_hist *h = NULL;
	unsigned i, j;
	int32_t val;
	u8 chainmask = (ah->rxchainmask << 3) | ah->rxchainmask;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ieee80211_conf *conf = &common->hw->conf;
	s16 default_nf = ath9k_hw_get_default_nf(ah, chan);

	if (ah->caldata)
		h = ah->caldata->nfCalHist;

	for (i = 0; i < NUM_NF_READINGS; i++) {
		if (chainmask & (1 << i)) {
			s16 nfval;

			if ((i >= AR5416_MAX_CHAINS) && !conf_is_ht40(conf))
				continue;

			if (h)
				nfval = h[i].privNF;
			else
				nfval = default_nf;

			val = REG_READ(ah, ah->nf_regs[i]);
			val &= 0xFFFFFE00;
			val |= (((u32) nfval << 1) & 0x1ff);
			REG_WRITE(ah, ah->nf_regs[i], val);
		}
	}

	/*
	 * Load software filtered NF value into baseband internal minCCApwr
	 * variable.
	 */
	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_ENABLE_NF);
	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_NO_UPDATE_NF);
	REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_NF);

	/*
	 * Wait for load to complete, should be fast, a few 10s of us.
	 * The max delay was changed from an original 250us to 10000us
	 * since 250us often results in NF load timeout and causes deaf
	 * condition during stress testing 12/12/2009
	 */
	for (j = 0; j < 10000; j++) {
		if ((REG_READ(ah, AR_PHY_AGC_CONTROL) &
		     AR_PHY_AGC_CONTROL_NF) == 0)
			break;
		udelay(10);
	}

	/*
	 * We timed out waiting for the noisefloor to load, probably due to an
	 * in-progress rx. Simply return here and allow the load plenty of time
	 * to complete before the next calibration interval.  We need to avoid
	 * trying to load -50 (which happens below) while the previous load is
	 * still in progress as this can cause rx deafness. Instead by returning
	 * here, the baseband nf cal will just be capped by our present
	 * noisefloor until the next calibration timer.
	 */
	if (j == 10000) {
		ath_dbg(common, ANY,
			"Timeout while waiting for nf to load: AR_PHY_AGC_CONTROL=0x%x\n",
			REG_READ(ah, AR_PHY_AGC_CONTROL));
		return;
	}

	/*
	 * Restore maxCCAPower register parameter again so that we're not capped
	 * by the median we just loaded.  This will be initial (and max) value
	 * of next noise floor calibration the baseband does.
	 */
	ENABLE_REGWRITE_BUFFER(ah);
	for (i = 0; i < NUM_NF_READINGS; i++) {
		if (chainmask & (1 << i)) {
			if ((i >= AR5416_MAX_CHAINS) && !conf_is_ht40(conf))
				continue;

			val = REG_READ(ah, ah->nf_regs[i]);
			val &= 0xFFFFFE00;
			val |= (((u32) (-50) << 1) & 0x1ff);
			REG_WRITE(ah, ah->nf_regs[i], val);
		}
	}
	REGWRITE_BUFFER_FLUSH(ah);
}