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
struct configfs_attribute {int dummy; } ;
struct config_item {int /*<<< orphan*/  ci_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CONFIGFS_ITEM_ATTR ; 
 int configfs_add_file (int /*<<< orphan*/ ,struct configfs_attribute const*,int /*<<< orphan*/ ) ; 

int configfs_create_file(struct config_item * item, const struct configfs_attribute * attr)
{
	BUG_ON(!item || !item->ci_dentry || !attr);

	return configfs_add_file(item->ci_dentry, attr,
				 CONFIGFS_ITEM_ATTR);
}