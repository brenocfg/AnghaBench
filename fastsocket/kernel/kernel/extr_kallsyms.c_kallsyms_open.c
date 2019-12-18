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
struct seq_file {struct kallsym_iter* private; } ;
struct kallsym_iter {int dummy; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kallsyms_op ; 
 int /*<<< orphan*/  kfree (struct kallsym_iter*) ; 
 struct kallsym_iter* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_iter (struct kallsym_iter*,int /*<<< orphan*/ ) ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kallsyms_open(struct inode *inode, struct file *file)
{
	/*
	 * We keep iterator in m->private, since normal case is to
	 * s_start from where we left off, so we avoid doing
	 * using get_symbol_offset for every symbol.
	 */
	struct kallsym_iter *iter;
	int ret;

	iter = kmalloc(sizeof(*iter), GFP_KERNEL);
	if (!iter)
		return -ENOMEM;
	reset_iter(iter, 0);

	ret = seq_open(file, &kallsyms_op);
	if (ret == 0)
		((struct seq_file *)file->private_data)->private = iter;
	else
		kfree(iter);
	return ret;
}