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
struct seq_file {struct fscache_objlist_data* private; } ;
struct inode {int dummy; } ;
struct fscache_objlist_data {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fscache_objlist_config (struct fscache_objlist_data*) ; 
 int /*<<< orphan*/  fscache_objlist_ops ; 
 struct fscache_objlist_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_release (struct inode*,struct file*) ; 

__attribute__((used)) static int fscache_objlist_open(struct inode *inode, struct file *file)
{
	struct fscache_objlist_data *data;
	struct seq_file *m;
	int ret;

	ret = seq_open(file, &fscache_objlist_ops);
	if (ret < 0)
		return ret;

	m = file->private_data;

	/* buffer for key extraction */
	data = kmalloc(sizeof(struct fscache_objlist_data), GFP_KERNEL);
	if (!data) {
		seq_release(inode, file);
		return -ENOMEM;
	}

	/* get the configuration key */
	fscache_objlist_config(data);

	m->private = data;
	return 0;
}