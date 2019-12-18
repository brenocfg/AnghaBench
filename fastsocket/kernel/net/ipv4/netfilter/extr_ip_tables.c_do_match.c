#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_match_param {int /*<<< orphan*/  matchinfo; TYPE_1__* match; } ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {TYPE_1__* match; } ;
struct TYPE_6__ {TYPE_2__ kernel; } ;
struct ipt_entry_match {TYPE_3__ u; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* match ) (struct sk_buff const*,struct xt_match_param*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sk_buff const*,struct xt_match_param*) ; 

__attribute__((used)) static inline bool
do_match(struct ipt_entry_match *m, const struct sk_buff *skb,
	 struct xt_match_param *par)
{
	par->match     = m->u.kernel.match;
	par->matchinfo = m->data;

	/* Stop iteration if it doesn't match */
	if (!m->u.kernel.match->match(skb, par))
		return true;
	else
		return false;
}