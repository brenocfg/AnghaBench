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
struct TYPE_2__ {int /*<<< orphan*/  context_stolen; } ;
struct gru_thread_state {int ts_user_blade_id; int ts_cbr_au_count; int ts_dsr_au_count; int /*<<< orphan*/  ts_steal_jiffies; TYPE_1__ ustats; } ;
struct gru_state {int /*<<< orphan*/  gs_dsr_map; int /*<<< orphan*/  gs_cbr_map; int /*<<< orphan*/  gs_gid; int /*<<< orphan*/  gs_lock; struct gru_thread_state** gs_gts; } ;
struct gru_blade_state {int bs_lru_ctxnum; int /*<<< orphan*/  bs_lock; struct gru_state* bs_lru_gru; } ;

/* Variables and functions */
 int GRU_NUM_CCH ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 scalar_t__ check_gru_resources (struct gru_state*,int,int,int) ; 
 struct gru_blade_state** gru_base ; 
 scalar_t__ gru_check_chiplet_assignment (struct gru_state*,struct gru_thread_state*) ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,struct gru_thread_state*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_unload_context (struct gru_thread_state*,int) ; 
 int /*<<< orphan*/  grudev ; 
 int /*<<< orphan*/  gts_stolen (struct gru_thread_state*,struct gru_blade_state*) ; 
 int /*<<< orphan*/  hweight64 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_gts_stealable (struct gru_thread_state*,struct gru_blade_state*) ; 
 scalar_t__ is_kernel_context (struct gru_thread_state*) ; 
 int /*<<< orphan*/  jiffies ; 
 int next_ctxnum (int) ; 
 struct gru_state* next_gru (struct gru_blade_state*,struct gru_state*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  steal_context_failed ; 
 int uv_numa_blade_id () ; 

void gru_steal_context(struct gru_thread_state *gts)
{
	struct gru_blade_state *blade;
	struct gru_state *gru, *gru0;
	struct gru_thread_state *ngts = NULL;
	int ctxnum, ctxnum0, flag = 0, cbr, dsr;
	int blade_id;

	blade_id = gts->ts_user_blade_id;
	if (blade_id < 0)
		blade_id = uv_numa_blade_id();
	cbr = gts->ts_cbr_au_count;
	dsr = gts->ts_dsr_au_count;

	blade = gru_base[blade_id];
	spin_lock(&blade->bs_lock);

	ctxnum = next_ctxnum(blade->bs_lru_ctxnum);
	gru = blade->bs_lru_gru;
	if (ctxnum == 0)
		gru = next_gru(blade, gru);
	blade->bs_lru_gru = gru;
	blade->bs_lru_ctxnum = ctxnum;
	ctxnum0 = ctxnum;
	gru0 = gru;
	while (1) {
		if (gru_check_chiplet_assignment(gru, gts)) {
			if (check_gru_resources(gru, cbr, dsr, GRU_NUM_CCH))
				break;
			spin_lock(&gru->gs_lock);
			for (; ctxnum < GRU_NUM_CCH; ctxnum++) {
				if (flag && gru == gru0 && ctxnum == ctxnum0)
					break;
				ngts = gru->gs_gts[ctxnum];
				/*
				* We are grabbing locks out of order, so trylock is
				* needed. GTSs are usually not locked, so the odds of
				* success are high. If trylock fails, try to steal a
				* different GSEG.
				*/
				if (ngts && is_gts_stealable(ngts, blade))
					break;
				ngts = NULL;
			}
			spin_unlock(&gru->gs_lock);
			if (ngts || (flag && gru == gru0 && ctxnum == ctxnum0))
				break;
		}
		if (flag && gru == gru0)
			break;
		flag = 1;
		ctxnum = 0;
		gru = next_gru(blade, gru);
	}
	spin_unlock(&blade->bs_lock);

	if (ngts) {
		gts->ustats.context_stolen++;
		ngts->ts_steal_jiffies = jiffies;
		gru_unload_context(ngts, is_kernel_context(ngts) ? 0 : 1);
		gts_stolen(ngts, blade);
	} else {
		STAT(steal_context_failed);
	}
	gru_dbg(grudev,
		"stole gid %d, ctxnum %d from gts %p. Need cb %d, ds %d;"
		" avail cb %ld, ds %ld\n",
		gru->gs_gid, ctxnum, ngts, cbr, dsr, hweight64(gru->gs_cbr_map),
		hweight64(gru->gs_dsr_map));
}