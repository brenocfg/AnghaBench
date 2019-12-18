#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_mode; } ;
struct TYPE_4__ {TYPE_3__* dentry; } ;
struct file {int f_mode; struct configfs_buffer* private_data; TYPE_1__ f_path; } ;
struct configfs_item_operations {int /*<<< orphan*/  show_attribute; int /*<<< orphan*/  store_attribute; } ;
struct configfs_buffer {int needs_read_fill; struct configfs_item_operations* ops; int /*<<< orphan*/  mutex; } ;
struct configfs_attribute {int /*<<< orphan*/  ca_owner; } ;
struct config_item {TYPE_2__* ci_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  d_parent; } ;
struct TYPE_5__ {struct configfs_item_operations* ct_item_ops; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IRUGO ; 
 int S_IWUGO ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 struct config_item* configfs_get_config_item (int /*<<< orphan*/ ) ; 
 struct configfs_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct configfs_attribute* to_attr (TYPE_3__*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_perm(struct inode * inode, struct file * file)
{
	struct config_item *item = configfs_get_config_item(file->f_path.dentry->d_parent);
	struct configfs_attribute * attr = to_attr(file->f_path.dentry);
	struct configfs_buffer * buffer;
	struct configfs_item_operations * ops = NULL;
	int error = 0;

	if (!item || !attr)
		goto Einval;

	/* Grab the module reference for this attribute if we have one */
	if (!try_module_get(attr->ca_owner)) {
		error = -ENODEV;
		goto Done;
	}

	if (item->ci_type)
		ops = item->ci_type->ct_item_ops;
	else
		goto Eaccess;

	/* File needs write support.
	 * The inode's perms must say it's ok,
	 * and we must have a store method.
	 */
	if (file->f_mode & FMODE_WRITE) {

		if (!(inode->i_mode & S_IWUGO) || !ops->store_attribute)
			goto Eaccess;

	}

	/* File needs read support.
	 * The inode's perms must say it's ok, and we there
	 * must be a show method for it.
	 */
	if (file->f_mode & FMODE_READ) {
		if (!(inode->i_mode & S_IRUGO) || !ops->show_attribute)
			goto Eaccess;
	}

	/* No error? Great, allocate a buffer for the file, and store it
	 * it in file->private_data for easy access.
	 */
	buffer = kzalloc(sizeof(struct configfs_buffer),GFP_KERNEL);
	if (!buffer) {
		error = -ENOMEM;
		goto Enomem;
	}
	mutex_init(&buffer->mutex);
	buffer->needs_read_fill = 1;
	buffer->ops = ops;
	file->private_data = buffer;
	goto Done;

 Einval:
	error = -EINVAL;
	goto Done;
 Eaccess:
	error = -EACCES;
 Enomem:
	module_put(attr->ca_owner);
 Done:
	if (error && item)
		config_item_put(item);
	return error;
}