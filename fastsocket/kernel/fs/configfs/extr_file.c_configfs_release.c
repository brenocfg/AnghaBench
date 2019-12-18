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
struct module {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {TYPE_2__* dentry; } ;
struct file {struct configfs_buffer* private_data; TYPE_1__ f_path; } ;
struct configfs_buffer {int /*<<< orphan*/  mutex; scalar_t__ page; } ;
struct configfs_attribute {struct module* ca_owner; } ;
struct config_item {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct configfs_buffer*) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct configfs_attribute* to_attr (TYPE_2__*) ; 
 struct config_item* to_item (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int configfs_release(struct inode * inode, struct file * filp)
{
	struct config_item * item = to_item(filp->f_path.dentry->d_parent);
	struct configfs_attribute * attr = to_attr(filp->f_path.dentry);
	struct module * owner = attr->ca_owner;
	struct configfs_buffer * buffer = filp->private_data;

	if (item)
		config_item_put(item);
	/* After this point, attr should not be accessed. */
	module_put(owner);

	if (buffer) {
		if (buffer->page)
			free_page((unsigned long)buffer->page);
		mutex_destroy(&buffer->mutex);
		kfree(buffer);
	}
	return 0;
}