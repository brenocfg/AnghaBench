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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_hashinfo {int dummy; } ;
struct tcf_common {int dummy; } ;
struct tc_action {struct tcf_common* priv; TYPE_1__* ops; } ;
struct TYPE_2__ {struct tcf_hashinfo* hinfo; } ;

/* Variables and functions */
 struct tcf_common* tcf_hash_lookup (int /*<<< orphan*/ ,struct tcf_hashinfo*) ; 

int tcf_hash_search(struct tc_action *a, u32 index)
{
	struct tcf_hashinfo *hinfo = a->ops->hinfo;
	struct tcf_common *p = tcf_hash_lookup(index, hinfo);

	if (p) {
		a->priv = p;
		return 1;
	}
	return 0;
}