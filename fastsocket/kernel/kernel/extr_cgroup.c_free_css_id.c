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
struct css_id {int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  id; struct css_id* css; } ;
struct cgroup_subsys_state {struct css_id* id; } ;
struct cgroup_subsys {int /*<<< orphan*/  id_lock; int /*<<< orphan*/  idr; int /*<<< orphan*/  use_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __free_css_id_cb ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct css_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void free_css_id(struct cgroup_subsys *ss, struct cgroup_subsys_state *css)
{
	struct css_id *id = css->id;
	/* When this is called before css_id initialization, id can be NULL */
	if (!id)
		return;

	BUG_ON(!ss->use_id);

	rcu_assign_pointer(id->css, NULL);
	rcu_assign_pointer(css->id, NULL);
	spin_lock(&ss->id_lock);
	idr_remove(&ss->idr, id->id);
	spin_unlock(&ss->id_lock);
	call_rcu(&id->rcu_head, __free_css_id_cb);
}