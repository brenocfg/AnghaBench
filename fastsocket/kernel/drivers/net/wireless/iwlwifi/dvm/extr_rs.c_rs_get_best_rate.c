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
typedef  int u16 ;
struct iwl_scale_tbl_info {int* expected_tpt; int /*<<< orphan*/  lq_type; TYPE_1__* win; } ;
struct iwl_priv {int dummy; } ;
struct iwl_lq_sta {size_t active_tbl; int last_tpt; struct iwl_scale_tbl_info* lq_info; } ;
typedef  size_t s8 ;
typedef  int s32 ;
struct TYPE_2__ {int success_ratio; } ;

/* Variables and functions */
 int IWL_RATE_DECREASE_TH ; 
 int IWL_RATE_HIGH_TH ; 
 int IWL_RATE_INVALID ; 
 int IWL_RATE_SCALE_SWITCH ; 
 int rs_get_adjacent_rate (struct iwl_priv*,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 rs_get_best_rate(struct iwl_priv *priv,
			    struct iwl_lq_sta *lq_sta,
			    struct iwl_scale_tbl_info *tbl,	/* "search" */
			    u16 rate_mask, s8 index)
{
	/* "active" values */
	struct iwl_scale_tbl_info *active_tbl =
	    &(lq_sta->lq_info[lq_sta->active_tbl]);
	s32 active_sr = active_tbl->win[index].success_ratio;
	s32 active_tpt = active_tbl->expected_tpt[index];

	/* expected "search" throughput */
	s32 *tpt_tbl = tbl->expected_tpt;

	s32 new_rate, high, low, start_hi;
	u16 high_low;
	s8 rate = index;

	new_rate = high = low = start_hi = IWL_RATE_INVALID;

	for (; ;) {
		high_low = rs_get_adjacent_rate(priv, rate, rate_mask,
						tbl->lq_type);

		low = high_low & 0xff;
		high = (high_low >> 8) & 0xff;

		/*
		 * Lower the "search" bit rate, to give new "search" mode
		 * approximately the same throughput as "active" if:
		 *
		 * 1) "Active" mode has been working modestly well (but not
		 *    great), and expected "search" throughput (under perfect
		 *    conditions) at candidate rate is above the actual
		 *    measured "active" throughput (but less than expected
		 *    "active" throughput under perfect conditions).
		 * OR
		 * 2) "Active" mode has been working perfectly or very well
		 *    and expected "search" throughput (under perfect
		 *    conditions) at candidate rate is above expected
		 *    "active" throughput (under perfect conditions).
		 */
		if ((((100 * tpt_tbl[rate]) > lq_sta->last_tpt) &&
		     ((active_sr > IWL_RATE_DECREASE_TH) &&
		      (active_sr <= IWL_RATE_HIGH_TH) &&
		      (tpt_tbl[rate] <= active_tpt))) ||
		    ((active_sr >= IWL_RATE_SCALE_SWITCH) &&
		     (tpt_tbl[rate] > active_tpt))) {

			/* (2nd or later pass)
			 * If we've already tried to raise the rate, and are
			 * now trying to lower it, use the higher rate. */
			if (start_hi != IWL_RATE_INVALID) {
				new_rate = start_hi;
				break;
			}

			new_rate = rate;

			/* Loop again with lower rate */
			if (low != IWL_RATE_INVALID)
				rate = low;

			/* Lower rate not available, use the original */
			else
				break;

		/* Else try to raise the "search" rate to match "active" */
		} else {
			/* (2nd or later pass)
			 * If we've already tried to lower the rate, and are
			 * now trying to raise it, use the lower rate. */
			if (new_rate != IWL_RATE_INVALID)
				break;

			/* Loop again with higher rate */
			else if (high != IWL_RATE_INVALID) {
				start_hi = high;
				rate = high;

			/* Higher rate not available, use the original */
			} else {
				new_rate = rate;
				break;
			}
		}
	}

	return new_rate;
}