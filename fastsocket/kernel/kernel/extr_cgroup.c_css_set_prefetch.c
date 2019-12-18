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
struct list_head {int dummy; } ;
struct css_set {int dummy; } ;
struct cgroup {int dummy; } ;
struct cg_list_entry {int /*<<< orphan*/  links; struct css_set* cg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct css_set* find_css_set (struct css_set*,struct cgroup*) ; 
 struct cg_list_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  put_css_set (struct css_set*) ; 

__attribute__((used)) static int css_set_prefetch(struct cgroup *cgrp, struct css_set *cg,
			    struct list_head *newcg_list)
{
	struct css_set *newcg;
	struct cg_list_entry *cg_entry;

	/* ensure a new css_set will exist for this thread */
	newcg = find_css_set(cg, cgrp);
	if (!newcg)
		return -ENOMEM;
	/* add it to the list */
	cg_entry = kmalloc(sizeof(struct cg_list_entry), GFP_KERNEL);
	if (!cg_entry) {
		put_css_set(newcg);
		return -ENOMEM;
	}
	cg_entry->cg = newcg;
	list_add(&cg_entry->links, newcg_list);
	return 0;
}