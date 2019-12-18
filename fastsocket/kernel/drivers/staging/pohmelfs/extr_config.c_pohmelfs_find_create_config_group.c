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
struct pohmelfs_config_group {unsigned int idx; int /*<<< orphan*/  group_entry; scalar_t__ num_entry; int /*<<< orphan*/  config_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct pohmelfs_config_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pohmelfs_config_list ; 
 struct pohmelfs_config_group* pohmelfs_find_config_group (unsigned int) ; 

__attribute__((used)) static struct pohmelfs_config_group *pohmelfs_find_create_config_group(unsigned int idx)
{
	struct pohmelfs_config_group *g;

	g = pohmelfs_find_config_group(idx);
	if (g)
		return g;

	g = kzalloc(sizeof(struct pohmelfs_config_group), GFP_KERNEL);
	if (!g)
		return NULL;

	INIT_LIST_HEAD(&g->config_list);
	g->idx = idx;
	g->num_entry = 0;

	list_add_tail(&g->group_entry, &pohmelfs_config_list);

	return g;
}