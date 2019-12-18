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
struct seq_operations {int dummy; } ;
struct seq_net_private {struct net* net; } ;
struct net {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int ENXIO ; 
 struct seq_net_private* __seq_open_private (struct file*,struct seq_operations const*,int) ; 
 struct net* get_proc_net (struct inode*) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 

int seq_open_net(struct inode *ino, struct file *f,
		 const struct seq_operations *ops, int size)
{
	struct net *net;
	struct seq_net_private *p;

	BUG_ON(size < sizeof(*p));

	net = get_proc_net(ino);
	if (net == NULL)
		return -ENXIO;

	p = __seq_open_private(f, ops, size);
	if (p == NULL) {
		put_net(net);
		return -ENOMEM;
	}
#ifdef CONFIG_NET_NS
	p->net = net;
#endif
	return 0;
}