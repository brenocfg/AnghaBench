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
struct config_item_type {int dummy; } ;
struct TYPE_2__ {struct config_item_type* ci_type; } ;
struct config_group {TYPE_1__ cg_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_group_init (struct config_group*) ; 
 int /*<<< orphan*/  config_item_set_name (TYPE_1__*,char const*) ; 

void config_group_init_type_name(struct config_group *group, const char *name,
			 struct config_item_type *type)
{
	config_item_set_name(&group->cg_item, name);
	group->cg_item.ci_type = type;
	config_group_init(group);
}