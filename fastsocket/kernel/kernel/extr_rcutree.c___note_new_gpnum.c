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
struct rcu_state {int dummy; } ;
struct rcu_node {scalar_t__ gpnum; } ;
struct rcu_data {scalar_t__ gpnum; int qs_pending; scalar_t__ passed_quiesc; } ;

/* Variables and functions */

__attribute__((used)) static void __note_new_gpnum(struct rcu_state *rsp, struct rcu_node *rnp, struct rcu_data *rdp)
{
	if (rdp->gpnum != rnp->gpnum) {
		rdp->qs_pending = 1;
		rdp->passed_quiesc = 0;
		rdp->gpnum = rnp->gpnum;
	}
}