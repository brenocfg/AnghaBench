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
struct tcf_proto {int dummy; } ;
struct flow_filter {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_destroy_filter (struct tcf_proto*,struct flow_filter*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_tree_lock (struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_tree_unlock (struct tcf_proto*) ; 

__attribute__((used)) static int flow_delete(struct tcf_proto *tp, unsigned long arg)
{
	struct flow_filter *f = (struct flow_filter *)arg;

	tcf_tree_lock(tp);
	list_del(&f->list);
	tcf_tree_unlock(tp);
	flow_destroy_filter(tp, f);
	return 0;
}