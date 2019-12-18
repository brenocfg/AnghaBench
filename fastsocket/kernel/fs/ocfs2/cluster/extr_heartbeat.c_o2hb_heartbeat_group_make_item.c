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
struct config_item {int dummy; } ;
struct o2hb_region {struct config_item hr_item; int /*<<< orphan*/  hr_all_item; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct config_item* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  config_item_init_type_name (struct config_item*,char const*,int /*<<< orphan*/ *) ; 
 struct o2hb_region* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2hb_all_regions ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  o2hb_region_type ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct config_item *o2hb_heartbeat_group_make_item(struct config_group *group,
							  const char *name)
{
	struct o2hb_region *reg = NULL;

	reg = kzalloc(sizeof(struct o2hb_region), GFP_KERNEL);
	if (reg == NULL)
		return ERR_PTR(-ENOMEM);

	config_item_init_type_name(&reg->hr_item, name, &o2hb_region_type);

	spin_lock(&o2hb_live_lock);
	list_add_tail(&reg->hr_all_item, &o2hb_all_regions);
	spin_unlock(&o2hb_live_lock);

	return &reg->hr_item;
}