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
struct ath_nf_limits {int /*<<< orphan*/  nominal; int /*<<< orphan*/  min; int /*<<< orphan*/  max; } ;
struct ath_hw {struct ath_nf_limits nf_5g; struct ath_nf_limits nf_2g; int /*<<< orphan*/  curchan; } ;
struct ath_common {int dummy; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  CALIBRATE ; 
 scalar_t__ IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 int NUM_NF_READINGS ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void ath9k_hw_nf_sanitize(struct ath_hw *ah, s16 *nf)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_nf_limits *limit;
	int i;

	if (IS_CHAN_2GHZ(ah->curchan))
		limit = &ah->nf_2g;
	else
		limit = &ah->nf_5g;

	for (i = 0; i < NUM_NF_READINGS; i++) {
		if (!nf[i])
			continue;

		ath_dbg(common, CALIBRATE,
			"NF calibrated [%s] [chain %d] is %d\n",
			(i >= 3 ? "ext" : "ctl"), i % 3, nf[i]);

		if (nf[i] > limit->max) {
			ath_dbg(common, CALIBRATE,
				"NF[%d] (%d) > MAX (%d), correcting to MAX\n",
				i, nf[i], limit->max);
			nf[i] = limit->max;
		} else if (nf[i] < limit->min) {
			ath_dbg(common, CALIBRATE,
				"NF[%d] (%d) < MIN (%d), correcting to NOM\n",
				i, nf[i], limit->min);
			nf[i] = limit->nominal;
		}
	}
}