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
struct seq_file {struct cpu_private* private; } ;
struct inode {struct cpu_private* i_private; } ;
struct file {struct seq_file* private_data; } ;
struct cpu_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_seq_ops ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpu_seq_open(struct inode *inode, struct file *file)
{
	struct cpu_private *priv = inode->i_private;
	struct seq_file *seq;
	int err;

	err = seq_open(file, &cpu_seq_ops);
	if (!err) {
		seq = file->private_data;
		seq->private = priv;
	}

	return err;
}