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
struct seq_file {struct ftrace_event_call* private; } ;
struct inode {struct ftrace_event_call* i_private; } ;
struct ftrace_event_call {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_format_seq_ops ; 

__attribute__((used)) static int trace_format_open(struct inode *inode, struct file *file)
{
	struct ftrace_event_call *call = inode->i_private;
	struct seq_file *m;
	int ret;

	ret = seq_open(file, &trace_format_seq_ops);
	if (ret < 0)
		return ret;

	m = file->private_data;
	m->private = call;

	return 0;
}