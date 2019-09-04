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
struct pf_state_cmp {int dummy; } ;
struct pf_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fcounters; } ;

/* Variables and functions */
 size_t FCNT_STATE_SEARCH ; 
 struct pf_state* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pf_state*) ; 
 int /*<<< orphan*/  pf_state_tree_id ; 
 TYPE_1__ pf_status ; 
 int /*<<< orphan*/  tree_id ; 

struct pf_state *
pf_find_state_byid(struct pf_state_cmp *key)
{
	pf_status.fcounters[FCNT_STATE_SEARCH]++;

	return (RB_FIND(pf_state_tree_id, &tree_id,
	    (struct pf_state *)(void *)key));
}