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
struct config_item_type {int dummy; } ;
struct config_item {struct config_item_type* ci_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_init (struct config_item*) ; 
 int /*<<< orphan*/  config_item_set_name (struct config_item*,char const*) ; 

void config_item_init_type_name(struct config_item *item,
				const char *name,
				struct config_item_type *type)
{
	config_item_set_name(item, name);
	item->ci_type = type;
	config_item_init(item);
}