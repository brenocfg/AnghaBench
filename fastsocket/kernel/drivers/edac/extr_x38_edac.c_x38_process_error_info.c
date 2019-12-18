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
typedef  int u64 ;
struct x38_error_info {int errsts; int errsts2; int* eccerrlog; } ;
struct mem_ctl_info {int dummy; } ;

/* Variables and functions */
 int X38_ECCERRLOG_CE ; 
 int X38_ECCERRLOG_UE ; 
 int X38_ERRSTS_BITS ; 
 int /*<<< orphan*/  eccerrlog_row (int,int) ; 
 int /*<<< orphan*/  eccerrlog_syndrome (int) ; 
 int /*<<< orphan*/  edac_mc_handle_ce (struct mem_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_mc_handle_ce_no_info (struct mem_ctl_info*,char*) ; 
 int /*<<< orphan*/  edac_mc_handle_ue (struct mem_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int x38_channel_num ; 

__attribute__((used)) static void x38_process_error_info(struct mem_ctl_info *mci,
				struct x38_error_info *info)
{
	int channel;
	u64 log;

	if (!(info->errsts & X38_ERRSTS_BITS))
		return;

	if ((info->errsts ^ info->errsts2) & X38_ERRSTS_BITS) {
		edac_mc_handle_ce_no_info(mci, "UE overwrote CE");
		info->errsts = info->errsts2;
	}

	for (channel = 0; channel < x38_channel_num; channel++) {
		log = info->eccerrlog[channel];
		if (log & X38_ECCERRLOG_UE) {
			edac_mc_handle_ue(mci, 0, 0,
				eccerrlog_row(channel, log), "x38 UE");
		} else if (log & X38_ECCERRLOG_CE) {
			edac_mc_handle_ce(mci, 0, 0,
				eccerrlog_syndrome(log),
				eccerrlog_row(channel, log), 0, "x38 CE");
		}
	}
}