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
struct dlm_space {int /*<<< orphan*/  members_lock; int /*<<< orphan*/  members_count; int /*<<< orphan*/  members; } ;
struct config_item {int dummy; } ;
struct dlm_node {int nodeid; int weight; int new; struct config_item item; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  ci_parent; } ;
struct config_group {TYPE_1__ cg_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct config_item* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  config_item_init_type_name (struct config_item*,char const*,int /*<<< orphan*/ *) ; 
 struct dlm_space* config_item_to_space (int /*<<< orphan*/ ) ; 
 struct dlm_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_type ; 

__attribute__((used)) static struct config_item *make_node(struct config_group *g, const char *name)
{
	struct dlm_space *sp = config_item_to_space(g->cg_item.ci_parent);
	struct dlm_node *nd;

	nd = kzalloc(sizeof(struct dlm_node), GFP_NOFS);
	if (!nd)
		return ERR_PTR(-ENOMEM);

	config_item_init_type_name(&nd->item, name, &node_type);
	nd->nodeid = -1;
	nd->weight = 1;  /* default weight of 1 if none is set */
	nd->new = 1;     /* set to 0 once it's been read by dlm_nodeid_list() */

	mutex_lock(&sp->members_lock);
	list_add(&nd->list, &sp->members);
	sp->members_count++;
	mutex_unlock(&sp->members_lock);

	return &nd->item;
}