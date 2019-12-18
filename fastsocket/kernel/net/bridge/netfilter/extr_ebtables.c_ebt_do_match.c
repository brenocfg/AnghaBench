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
struct xt_match_param {int /*<<< orphan*/  matchinfo; TYPE_1__* match; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {TYPE_1__* match; } ;
struct ebt_entry_match {TYPE_2__ u; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {scalar_t__ (* match ) (struct sk_buff const*,struct xt_match_param*) ;} ;

/* Variables and functions */
 int EBT_MATCH ; 
 int EBT_NOMATCH ; 
 scalar_t__ stub1 (struct sk_buff const*,struct xt_match_param*) ; 

__attribute__((used)) static inline int ebt_do_match (struct ebt_entry_match *m,
   const struct sk_buff *skb, struct xt_match_param *par)
{
	par->match     = m->u.match;
	par->matchinfo = m->data;
	return m->u.match->match(skb, par) ? EBT_MATCH : EBT_NOMATCH;
}