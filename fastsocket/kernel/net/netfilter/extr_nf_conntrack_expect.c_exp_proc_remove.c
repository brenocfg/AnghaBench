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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_net_remove (struct net*,char*) ; 

__attribute__((used)) static void exp_proc_remove(struct net *net)
{
#ifdef CONFIG_PROC_FS
	proc_net_remove(net, "nf_conntrack_expect");
#endif /* CONFIG_PROC_FS */
}