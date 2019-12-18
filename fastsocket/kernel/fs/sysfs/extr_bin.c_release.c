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
struct inode {int dummy; } ;
struct file {struct bin_buffer* private_data; } ;
struct bin_buffer {struct bin_buffer* buffer; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bin_buffer*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_bin_lock ; 

__attribute__((used)) static int release(struct inode * inode, struct file * file)
{
	struct bin_buffer *bb = file->private_data;

	mutex_lock(&sysfs_bin_lock);
	hlist_del(&bb->list);
	mutex_unlock(&sysfs_bin_lock);

	kfree(bb->buffer);
	kfree(bb);
	return 0;
}