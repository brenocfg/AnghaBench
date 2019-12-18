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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct llc_station_state_trans {scalar_t__ (* ev_actions ) (struct sk_buff*) ;} ;
typedef  scalar_t__ (* llc_station_action_t ) (struct sk_buff*) ;

/* Variables and functions */
 scalar_t__ stub1 (struct sk_buff*) ; 

__attribute__((used)) static u16 llc_exec_station_trans_actions(struct llc_station_state_trans *trans,
					  struct sk_buff *skb)
{
	u16 rc = 0;
	llc_station_action_t *next_action = trans->ev_actions;

	for (; next_action && *next_action; next_action++)
		if ((*next_action)(skb))
			rc = 1;
	return rc;
}