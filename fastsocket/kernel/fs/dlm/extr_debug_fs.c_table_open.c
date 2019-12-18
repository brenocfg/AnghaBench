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
struct seq_file {int /*<<< orphan*/  private; } ;
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {struct seq_file* private_data; int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  format1_fops ; 
 int /*<<< orphan*/  format1_seq_ops ; 
 int /*<<< orphan*/  format2_fops ; 
 int /*<<< orphan*/  format2_seq_ops ; 
 int /*<<< orphan*/  format3_fops ; 
 int /*<<< orphan*/  format3_seq_ops ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int table_open(struct inode *inode, struct file *file)
{
	struct seq_file *seq;
	int ret = -1;

	if (file->f_op == &format1_fops)
		ret = seq_open(file, &format1_seq_ops);
	else if (file->f_op == &format2_fops)
		ret = seq_open(file, &format2_seq_ops);
	else if (file->f_op == &format3_fops)
		ret = seq_open(file, &format3_seq_ops);

	if (ret)
		return ret;

	seq = file->private_data;
	seq->private = inode->i_private; /* the dlm_ls */
	return 0;
}