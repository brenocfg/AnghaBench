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
struct sk_buff {int dummy; } ;
struct iwl_test {TYPE_2__* trans; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  op_mode; } ;
struct TYPE_3__ {void (* event ) (int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 void stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static inline void
iwl_test_event(struct iwl_test *tst, struct sk_buff *skb)
{
	return tst->ops->event(tst->trans->op_mode, skb);
}