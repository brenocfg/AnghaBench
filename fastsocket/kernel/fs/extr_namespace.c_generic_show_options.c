#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {TYPE_1__* mnt_sb; } ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  mangle (struct seq_file*,char const*) ; 
 char* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

int generic_show_options(struct seq_file *m, struct vfsmount *mnt)
{
	const char *options;

	rcu_read_lock();
	options = rcu_dereference(mnt->mnt_sb->s_options);

	if (options != NULL && options[0]) {
		seq_putc(m, ',');
		mangle(m, options);
	}
	rcu_read_unlock();

	return 0;
}