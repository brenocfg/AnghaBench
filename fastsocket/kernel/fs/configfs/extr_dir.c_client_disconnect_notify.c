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
struct config_item_type {TYPE_1__* ct_group_ops; } ;
struct config_item {struct config_item_type* ci_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disconnect_notify ) (int /*<<< orphan*/ ,struct config_item*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct config_item*) ; 
 int /*<<< orphan*/  to_config_group (struct config_item*) ; 

__attribute__((used)) static void client_disconnect_notify(struct config_item *parent_item,
				     struct config_item *item)
{
	struct config_item_type *type;

	type = parent_item->ci_type;
	BUG_ON(!type);

	if (type->ct_group_ops && type->ct_group_ops->disconnect_notify)
		type->ct_group_ops->disconnect_notify(to_config_group(parent_item),
						      item);
}