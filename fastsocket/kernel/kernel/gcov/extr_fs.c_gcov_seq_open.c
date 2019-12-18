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
struct seq_file {struct gcov_iterator* private; } ;
struct inode {struct gcov_node* i_private; } ;
struct gcov_node {int dummy; } ;
struct gcov_iterator {int dummy; } ;
struct gcov_info {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct gcov_info* gcov_info_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcov_info_free (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_iter_free (struct gcov_iterator*) ; 
 struct gcov_iterator* gcov_iter_new (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_seq_ops ; 
 int /*<<< orphan*/  get_node_info (struct gcov_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_lock ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gcov_seq_open(struct inode *inode, struct file *file)
{
	struct gcov_node *node = inode->i_private;
	struct gcov_iterator *iter;
	struct seq_file *seq;
	struct gcov_info *info;
	int rc = -ENOMEM;

	mutex_lock(&node_lock);
	/*
	 * Read from a profiling data copy to minimize reference tracking
	 * complexity and concurrent access.
	 */
	info = gcov_info_dup(get_node_info(node));
	if (!info)
		goto out_unlock;
	iter = gcov_iter_new(info);
	if (!iter)
		goto err_free_info;
	rc = seq_open(file, &gcov_seq_ops);
	if (rc)
		goto err_free_iter_info;
	seq = file->private_data;
	seq->private = iter;
out_unlock:
	mutex_unlock(&node_lock);
	return rc;

err_free_iter_info:
	gcov_iter_free(iter);
err_free_info:
	gcov_info_free(info);
	goto out_unlock;
}