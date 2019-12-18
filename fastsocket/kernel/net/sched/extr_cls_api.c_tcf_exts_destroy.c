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
struct tcf_proto {int dummy; } ;
struct tcf_exts {int /*<<< orphan*/ * action; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_ACT_UNBIND ; 
 int /*<<< orphan*/  tcf_action_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tcf_exts_destroy(struct tcf_proto *tp, struct tcf_exts *exts)
{
#ifdef CONFIG_NET_CLS_ACT
	if (exts->action) {
		tcf_action_destroy(exts->action, TCA_ACT_UNBIND);
		exts->action = NULL;
	}
#endif
}