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
struct proc_dir_entry {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  exp_file_ops ; 
 struct proc_dir_entry* proc_net_fops_create (struct net*,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exp_proc_init(struct net *net)
{
#ifdef CONFIG_PROC_FS
	struct proc_dir_entry *proc;

	proc = proc_net_fops_create(net, "nf_conntrack_expect", 0440, &exp_file_ops);
	if (!proc)
		return -ENOMEM;
#endif /* CONFIG_PROC_FS */
	return 0;
}