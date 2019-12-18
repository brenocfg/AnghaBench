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
struct iwl_scale_tbl_info {int /*<<< orphan*/ * win; } ;
struct iwl_priv {int dummy; } ;
struct iwl_lq_sta {int active_tbl; scalar_t__ table_count; scalar_t__ table_count_limit; scalar_t__ stay_in_tbl; scalar_t__ flush_timer; int /*<<< orphan*/  total_success; int /*<<< orphan*/  total_failed; int /*<<< orphan*/  search_better_tbl; int /*<<< orphan*/  max_success_limit; int /*<<< orphan*/  max_failure_limit; struct iwl_scale_tbl_info* lq_info; struct iwl_priv* drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_priv*,char*,...) ; 
 int IWL_RATE_COUNT ; 
 scalar_t__ IWL_RATE_SCALE_FLUSH_INTVL ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rs_rate_scale_clear_window (int /*<<< orphan*/ *) ; 
 int time_after (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void rs_stay_in_table(struct iwl_lq_sta *lq_sta, bool force_search)
{
	struct iwl_scale_tbl_info *tbl;
	int i;
	int active_tbl;
	int flush_interval_passed = 0;
	struct iwl_priv *priv;

	priv = lq_sta->drv;
	active_tbl = lq_sta->active_tbl;

	tbl = &(lq_sta->lq_info[active_tbl]);

	/* If we've been disallowing search, see if we should now allow it */
	if (lq_sta->stay_in_tbl) {

		/* Elapsed time using current modulation mode */
		if (lq_sta->flush_timer)
			flush_interval_passed =
			time_after(jiffies,
					(unsigned long)(lq_sta->flush_timer +
					IWL_RATE_SCALE_FLUSH_INTVL));

		/*
		 * Check if we should allow search for new modulation mode.
		 * If many frames have failed or succeeded, or we've used
		 * this same modulation for a long time, allow search, and
		 * reset history stats that keep track of whether we should
		 * allow a new search.  Also (below) reset all bitmaps and
		 * stats in active history.
		 */
		if (force_search ||
		    (lq_sta->total_failed > lq_sta->max_failure_limit) ||
		    (lq_sta->total_success > lq_sta->max_success_limit) ||
		    ((!lq_sta->search_better_tbl) && (lq_sta->flush_timer)
		     && (flush_interval_passed))) {
			IWL_DEBUG_RATE(priv, "LQ: stay is expired %d %d %d\n",
				     lq_sta->total_failed,
				     lq_sta->total_success,
				     flush_interval_passed);

			/* Allow search for new mode */
			lq_sta->stay_in_tbl = 0;	/* only place reset */
			lq_sta->total_failed = 0;
			lq_sta->total_success = 0;
			lq_sta->flush_timer = 0;

		/*
		 * Else if we've used this modulation mode enough repetitions
		 * (regardless of elapsed time or success/failure), reset
		 * history bitmaps and rate-specific stats for all rates in
		 * active table.
		 */
		} else {
			lq_sta->table_count++;
			if (lq_sta->table_count >=
			    lq_sta->table_count_limit) {
				lq_sta->table_count = 0;

				IWL_DEBUG_RATE(priv, "LQ: stay in table clear win\n");
				for (i = 0; i < IWL_RATE_COUNT; i++)
					rs_rate_scale_clear_window(
						&(tbl->win[i]));
			}
		}

		/* If transitioning to allow "search", reset all history
		 * bitmaps and stats in active table (this will become the new
		 * "search" table). */
		if (!lq_sta->stay_in_tbl) {
			for (i = 0; i < IWL_RATE_COUNT; i++)
				rs_rate_scale_clear_window(&(tbl->win[i]));
		}
	}
}