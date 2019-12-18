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
struct sk_buff {int dummy; } ;
struct llc_sap_state_trans {scalar_t__ (* ev_actions ) (struct llc_sap*,struct sk_buff*) ;} ;
struct llc_sap {int dummy; } ;
typedef  scalar_t__ (* llc_sap_action_t ) (struct llc_sap*,struct sk_buff*) ;

/* Variables and functions */
 scalar_t__ stub1 (struct llc_sap*,struct sk_buff*) ; 

__attribute__((used)) static int llc_exec_sap_trans_actions(struct llc_sap *sap,
				      struct llc_sap_state_trans *trans,
				      struct sk_buff *skb)
{
	int rc = 0;
	llc_sap_action_t *next_action = trans->ev_actions;

	for (; next_action && *next_action; next_action++)
		if ((*next_action)(sap, skb))
			rc = 1;
	return rc;
}