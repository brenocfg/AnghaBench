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
struct xt_target_param {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned int EBT_CONTINUE ; 
 int /*<<< orphan*/  audit_tg (struct sk_buff*,struct xt_target_param const*) ; 

__attribute__((used)) static unsigned int
audit_tg_ebt(struct sk_buff *skb, const struct xt_target_param *par)
{
	audit_tg(skb, par);
	return EBT_CONTINUE;
}