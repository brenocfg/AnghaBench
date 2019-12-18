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
struct bnx2x {int stats_state; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  panic; } ;
typedef  enum bnx2x_stats_state { ____Placeholder_bnx2x_stats_state } bnx2x_stats_state ;
typedef  enum bnx2x_stats_event { ____Placeholder_bnx2x_stats_event } bnx2x_stats_event ;
struct TYPE_2__ {int next_state; void (* action ) (struct bnx2x*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_STATS ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int STATS_EVENT_UPDATE ; 
 TYPE_1__** bnx2x_stats_stm ; 
 scalar_t__ netif_msg_timer (struct bnx2x*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void bnx2x_stats_handle(struct bnx2x *bp, enum bnx2x_stats_event event)
{
	enum bnx2x_stats_state state;
	void (*action)(struct bnx2x *bp);
	if (unlikely(bp->panic))
		return;

	spin_lock_bh(&bp->stats_lock);
	state = bp->stats_state;
	bp->stats_state = bnx2x_stats_stm[state][event].next_state;
	action = bnx2x_stats_stm[state][event].action;
	spin_unlock_bh(&bp->stats_lock);

	action(bp);

	if ((event != STATS_EVENT_UPDATE) || netif_msg_timer(bp))
		DP(BNX2X_MSG_STATS, "state %d -> event %d -> state %d\n",
		   state, event, bp->stats_state);
}