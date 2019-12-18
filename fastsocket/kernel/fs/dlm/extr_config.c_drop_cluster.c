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
struct TYPE_3__ {TYPE_2__** default_groups; } ;
struct dlm_cluster {TYPE_1__ group; } ;
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;
struct TYPE_4__ {struct config_item cg_item; } ;

/* Variables and functions */
 int /*<<< orphan*/ * comm_list ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 struct dlm_cluster* config_item_to_cluster (struct config_item*) ; 
 int /*<<< orphan*/ * space_list ; 

__attribute__((used)) static void drop_cluster(struct config_group *g, struct config_item *i)
{
	struct dlm_cluster *cl = config_item_to_cluster(i);
	struct config_item *tmp;
	int j;

	for (j = 0; cl->group.default_groups[j]; j++) {
		tmp = &cl->group.default_groups[j]->cg_item;
		cl->group.default_groups[j] = NULL;
		config_item_put(tmp);
	}

	space_list = NULL;
	comm_list = NULL;

	config_item_put(i);
}