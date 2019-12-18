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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rcvcallb_skb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ;} ;
struct cardstate {int /*<<< orphan*/  myid; TYPE_1__ iif; } ;
struct bc_state {int /*<<< orphan*/  trans_down; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static inline void gigaset_rcv_skb(struct sk_buff *skb,
				   struct cardstate *cs,
				   struct bc_state *bcs)
{
	cs->iif.rcvcallb_skb(cs->myid, bcs->channel, skb);
	bcs->trans_down++;
}