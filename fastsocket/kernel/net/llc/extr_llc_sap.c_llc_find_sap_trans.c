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
struct llc_sap_state_trans {int /*<<< orphan*/  (* ev ) (struct llc_sap*,struct sk_buff*) ;} ;
struct llc_sap_state {struct llc_sap_state_trans** transitions; } ;
struct llc_sap {int state; } ;

/* Variables and functions */
 struct llc_sap_state* llc_sap_state_table ; 
 int /*<<< orphan*/  stub1 (struct llc_sap*,struct sk_buff*) ; 

__attribute__((used)) static struct llc_sap_state_trans *llc_find_sap_trans(struct llc_sap *sap,
						      struct sk_buff* skb)
{
	int i = 0;
	struct llc_sap_state_trans *rc = NULL;
	struct llc_sap_state_trans **next_trans;
	struct llc_sap_state *curr_state = &llc_sap_state_table[sap->state - 1];
	/*
	 * Search thru events for this state until list exhausted or until
	 * its obvious the event is not valid for the current state
	 */
	for (next_trans = curr_state->transitions; next_trans[i]->ev; i++)
		if (!next_trans[i]->ev(sap, skb)) {
			rc = next_trans[i]; /* got event match; return it */
			break;
		}
	return rc;
}