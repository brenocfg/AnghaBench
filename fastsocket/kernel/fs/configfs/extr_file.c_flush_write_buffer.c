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
struct dentry {int /*<<< orphan*/  d_parent; } ;
struct configfs_item_operations {int (* store_attribute ) (struct config_item*,struct configfs_attribute*,int /*<<< orphan*/ ,size_t) ;} ;
struct configfs_buffer {int /*<<< orphan*/  page; struct configfs_item_operations* ops; } ;
struct configfs_attribute {int dummy; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int stub1 (struct config_item*,struct configfs_attribute*,int /*<<< orphan*/ ,size_t) ; 
 struct configfs_attribute* to_attr (struct dentry*) ; 
 struct config_item* to_item (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
flush_write_buffer(struct dentry * dentry, struct configfs_buffer * buffer, size_t count)
{
	struct configfs_attribute * attr = to_attr(dentry);
	struct config_item * item = to_item(dentry->d_parent);
	struct configfs_item_operations * ops = buffer->ops;

	return ops->store_attribute(item,attr,buffer->page,count);
}