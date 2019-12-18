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
struct stat_session {int dummy; } ;
struct seq_file {struct stat_session* private; } ;
struct inode {struct stat_session* i_private; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_stat_session (struct stat_session*) ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 
 int stat_seq_init (struct stat_session*) ; 
 int /*<<< orphan*/  trace_stat_seq_ops ; 

__attribute__((used)) static int tracing_stat_open(struct inode *inode, struct file *file)
{
	int ret;
	struct seq_file *m;
	struct stat_session *session = inode->i_private;

	ret = stat_seq_init(session);
	if (ret)
		return ret;

	ret = seq_open(file, &trace_stat_seq_ops);
	if (ret) {
		reset_stat_session(session);
		return ret;
	}

	m = file->private_data;
	m->private = session;
	return ret;
}