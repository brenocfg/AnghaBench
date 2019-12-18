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
typedef  int u32 ;
struct xt_tgchk_param {TYPE_1__* target; struct xt_NFQ_info_v2* targinfo; } ;
struct xt_NFQ_info_v2 {int queues_total; int queuenum; int bypass; } ;
struct TYPE_2__ {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static bool nfqueue_tg_check(const struct xt_tgchk_param *par)
{
	const struct xt_NFQ_info_v2 *info = par->targinfo;
	u32 maxid;

	if (info->queues_total == 0) {
		pr_err("NFQUEUE: number of total queues is 0\n");
		return false;
	}
	maxid = info->queues_total - 1 + info->queuenum;
	if (maxid > 0xffff) {
		pr_err("NFQUEUE: number of queues (%u) out of range (got %u)\n",
		       info->queues_total, maxid);
		return false;
	}
	if (par->target->revision == 2 && info->bypass > 1)
		return false;
	return true;
}