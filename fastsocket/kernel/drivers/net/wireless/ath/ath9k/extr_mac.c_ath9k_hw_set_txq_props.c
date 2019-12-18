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
typedef  scalar_t__ u32 ;
struct ath_hw {struct ath9k_tx_queue_info* txq; } ;
struct ath_common {int dummy; } ;
struct ath9k_tx_queue_info {scalar_t__ tqi_type; int tqi_subtype; scalar_t__ tqi_aifs; scalar_t__ tqi_cwmin; scalar_t__ tqi_cwmax; scalar_t__ tqi_shretry; scalar_t__ tqi_lgretry; int /*<<< orphan*/  tqi_intFlags; int /*<<< orphan*/  tqi_readyTime; int /*<<< orphan*/  tqi_burstTime; int /*<<< orphan*/  tqi_cbrOverflowLimit; int /*<<< orphan*/  tqi_cbrPeriod; int /*<<< orphan*/  tqi_priority; int /*<<< orphan*/  tqi_qflags; int /*<<< orphan*/  tqi_ver; } ;

/* Variables and functions */
 scalar_t__ ATH9K_TXQ_USEDEFAULT ; 
 int /*<<< orphan*/  ATH9K_TXQ_USE_LOCKOUT_BKOFF_DIS ; 
 scalar_t__ ATH9K_TX_QUEUE_DATA ; 
 scalar_t__ ATH9K_TX_QUEUE_INACTIVE ; 
#define  ATH9K_WME_UPSD 128 
 scalar_t__ INIT_AIFS ; 
 int INIT_CWMAX ; 
 scalar_t__ INIT_LG_RETRY ; 
 scalar_t__ INIT_SH_RETRY ; 
 int /*<<< orphan*/  QUEUE ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 
 void* min (scalar_t__,unsigned int) ; 

bool ath9k_hw_set_txq_props(struct ath_hw *ah, int q,
			    const struct ath9k_tx_queue_info *qinfo)
{
	u32 cw;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_tx_queue_info *qi;

	qi = &ah->txq[q];
	if (qi->tqi_type == ATH9K_TX_QUEUE_INACTIVE) {
		ath_dbg(common, QUEUE,
			"Set TXQ properties, inactive queue: %u\n", q);
		return false;
	}

	ath_dbg(common, QUEUE, "Set queue properties for: %u\n", q);

	qi->tqi_ver = qinfo->tqi_ver;
	qi->tqi_subtype = qinfo->tqi_subtype;
	qi->tqi_qflags = qinfo->tqi_qflags;
	qi->tqi_priority = qinfo->tqi_priority;
	if (qinfo->tqi_aifs != ATH9K_TXQ_USEDEFAULT)
		qi->tqi_aifs = min(qinfo->tqi_aifs, 255U);
	else
		qi->tqi_aifs = INIT_AIFS;
	if (qinfo->tqi_cwmin != ATH9K_TXQ_USEDEFAULT) {
		cw = min(qinfo->tqi_cwmin, 1024U);
		qi->tqi_cwmin = 1;
		while (qi->tqi_cwmin < cw)
			qi->tqi_cwmin = (qi->tqi_cwmin << 1) | 1;
	} else
		qi->tqi_cwmin = qinfo->tqi_cwmin;
	if (qinfo->tqi_cwmax != ATH9K_TXQ_USEDEFAULT) {
		cw = min(qinfo->tqi_cwmax, 1024U);
		qi->tqi_cwmax = 1;
		while (qi->tqi_cwmax < cw)
			qi->tqi_cwmax = (qi->tqi_cwmax << 1) | 1;
	} else
		qi->tqi_cwmax = INIT_CWMAX;

	if (qinfo->tqi_shretry != 0)
		qi->tqi_shretry = min((u32) qinfo->tqi_shretry, 15U);
	else
		qi->tqi_shretry = INIT_SH_RETRY;
	if (qinfo->tqi_lgretry != 0)
		qi->tqi_lgretry = min((u32) qinfo->tqi_lgretry, 15U);
	else
		qi->tqi_lgretry = INIT_LG_RETRY;
	qi->tqi_cbrPeriod = qinfo->tqi_cbrPeriod;
	qi->tqi_cbrOverflowLimit = qinfo->tqi_cbrOverflowLimit;
	qi->tqi_burstTime = qinfo->tqi_burstTime;
	qi->tqi_readyTime = qinfo->tqi_readyTime;

	switch (qinfo->tqi_subtype) {
	case ATH9K_WME_UPSD:
		if (qi->tqi_type == ATH9K_TX_QUEUE_DATA)
			qi->tqi_intFlags = ATH9K_TXQ_USE_LOCKOUT_BKOFF_DIS;
		break;
	default:
		break;
	}

	return true;
}