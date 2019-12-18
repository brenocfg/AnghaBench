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
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDE_DATA (struct inode*) ; 
 int /*<<< orphan*/  ap_control_proc_seqops ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ap_control_proc_open(struct inode *inode, struct file *file)
{
	int ret = seq_open(file, &ap_control_proc_seqops);
	if (ret == 0) {
		struct seq_file *m = file->private_data;
		m->private = PDE_DATA(inode);
	}
	return ret;
}