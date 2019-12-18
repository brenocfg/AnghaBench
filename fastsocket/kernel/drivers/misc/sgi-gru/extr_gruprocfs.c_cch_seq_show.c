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
struct seq_file {int dummy; } ;
struct gru_thread_state {int ts_cbr_au_count; size_t ts_user_options; int /*<<< orphan*/  ts_tgid_owner; TYPE_2__* ts_gms; } ;
struct gru_state {int /*<<< orphan*/  gs_blade_id; int /*<<< orphan*/  gs_gid; struct gru_thread_state** gs_gts; } ;
struct TYPE_4__ {TYPE_1__* ms_asids; } ;
struct TYPE_3__ {int /*<<< orphan*/  mt_asid; } ;

/* Variables and functions */
 struct gru_state* GID_TO_GRU (long) ; 
 int GRU_CBR_AU_SIZE ; 
 int GRU_DSR_AU_BYTES ; 
 int GRU_NUM_CCH ; 
 size_t GRU_OPT_MISS_MASK ; 
 scalar_t__ is_kernel_context (struct gru_thread_state*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*,...) ; 

__attribute__((used)) static int cch_seq_show(struct seq_file *file, void *data)
{
	long gid = *(long *)data;
	int i;
	struct gru_state *gru = GID_TO_GRU(gid);
	struct gru_thread_state *ts;
	const char *mode[] = { "??", "UPM", "INTR", "OS_POLL" };

	if (gid == 0)
		seq_printf(file, "#%5s%5s%6s%7s%9s%6s%8s%8s\n", "gid", "bid",
			   "ctx#", "asid", "pid", "cbrs", "dsbytes", "mode");
	if (gru)
		for (i = 0; i < GRU_NUM_CCH; i++) {
			ts = gru->gs_gts[i];
			if (!ts)
				continue;
			seq_printf(file, " %5d%5d%6d%7d%9d%6d%8d%8s\n",
				   gru->gs_gid, gru->gs_blade_id, i,
				   is_kernel_context(ts) ? 0 : ts->ts_gms->ms_asids[gid].mt_asid,
				   is_kernel_context(ts) ? 0 : ts->ts_tgid_owner,
				   ts->ts_cbr_au_count * GRU_CBR_AU_SIZE,
				   ts->ts_cbr_au_count * GRU_DSR_AU_BYTES,
				   mode[ts->ts_user_options &
					GRU_OPT_MISS_MASK]);
		}

	return 0;
}