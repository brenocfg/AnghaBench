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
struct gru_thread_state {size_t ts_ctxnum; int ts_blade; struct gru_state* ts_gru; } ;
struct gru_state {int /*<<< orphan*/  gs_lock; int /*<<< orphan*/  gs_context_map; int /*<<< orphan*/ ** gs_gts; int /*<<< orphan*/  gs_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t NULLCTX ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clear_bit (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_context ; 
 int /*<<< orphan*/  free_gru_resources (struct gru_state*,struct gru_thread_state*) ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,struct gru_thread_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grudev ; 
 int /*<<< orphan*/  gts_drop (struct gru_thread_state*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gru_free_gru_context(struct gru_thread_state *gts)
{
	struct gru_state *gru;

	gru = gts->ts_gru;
	gru_dbg(grudev, "gts %p, gid %d\n", gts, gru->gs_gid);

	spin_lock(&gru->gs_lock);
	gru->gs_gts[gts->ts_ctxnum] = NULL;
	free_gru_resources(gru, gts);
	BUG_ON(test_bit(gts->ts_ctxnum, &gru->gs_context_map) == 0);
	__clear_bit(gts->ts_ctxnum, &gru->gs_context_map);
	gts->ts_ctxnum = NULLCTX;
	gts->ts_gru = NULL;
	gts->ts_blade = -1;
	spin_unlock(&gru->gs_lock);

	gts_drop(gts);
	STAT(free_context);
}