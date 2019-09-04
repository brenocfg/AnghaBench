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
struct pfi_kif {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ptr; } ;
struct pf_state {scalar_t__ timeout; struct pfi_kif* rt_kif; TYPE_2__ rule; } ;
struct TYPE_3__ {scalar_t__ rt; int direction; } ;

/* Variables and functions */
 scalar_t__ PFTM_PURGE ; 
 int PF_DROP ; 
 int PF_IN ; 
 int PF_OUT ; 
 int PF_PASS ; 
 scalar_t__ PF_REPLYTO ; 
 scalar_t__ PF_ROUTETO ; 

__attribute__((used)) static const int *
pf_state_lookup_aux(struct pf_state **state, struct pfi_kif *kif,
	int direction, int *action)
{
	if (*state == NULL || (*state)->timeout == PFTM_PURGE) {
		*action = PF_DROP;
		return (action);
	}

	if (direction == PF_OUT &&
	    (((*state)->rule.ptr->rt == PF_ROUTETO &&
	    (*state)->rule.ptr->direction == PF_OUT) ||
	    ((*state)->rule.ptr->rt == PF_REPLYTO &&
	    (*state)->rule.ptr->direction == PF_IN)) &&
	    (*state)->rt_kif != NULL && (*state)->rt_kif != kif) {
		*action = PF_PASS;
		return (action);
	}

	return (0);
}