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
struct task_struct {unsigned int il_next; } ;
struct TYPE_2__ {int /*<<< orphan*/  nodes; } ;
struct mempolicy {TYPE_1__ v; } ;

/* Variables and functions */
 unsigned int MAX_NUMNODES ; 
 struct task_struct* current ; 
 unsigned int first_node (int /*<<< orphan*/ ) ; 
 unsigned int next_node (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned interleave_nodes(struct mempolicy *policy)
{
	unsigned nid, next;
	struct task_struct *me = current;

	nid = me->il_next;
	next = next_node(nid, policy->v.nodes);
	if (next >= MAX_NUMNODES)
		next = first_node(policy->v.nodes);
	if (next < MAX_NUMNODES)
		me->il_next = next;
	return nid;
}