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
struct xt_target_param {int /*<<< orphan*/  targinfo; TYPE_1__* target; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {TYPE_1__* watcher; } ;
struct ebt_entry_watcher {TYPE_2__ u; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* target ) (struct sk_buff*,struct xt_target_param*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct xt_target_param*) ; 

__attribute__((used)) static inline int
ebt_do_watcher(const struct ebt_entry_watcher *w, struct sk_buff *skb,
	       struct xt_target_param *par)
{
	par->target   = w->u.watcher;
	par->targinfo = w->data;
	w->u.watcher->target(skb, par);
	/* watchers don't give a verdict */
	return 0;
}