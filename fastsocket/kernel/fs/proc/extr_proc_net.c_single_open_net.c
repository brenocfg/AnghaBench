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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 struct net* get_proc_net (struct inode*) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 int single_open (struct file*,int (*) (struct seq_file*,void*),struct net*) ; 

int single_open_net(struct inode *inode, struct file *file,
		int (*show)(struct seq_file *, void *))
{
	int err;
	struct net *net;

	err = -ENXIO;
	net = get_proc_net(inode);
	if (net == NULL)
		goto err_net;

	err = single_open(file, show, net);
	if (err < 0)
		goto err_open;

	return 0;

err_open:
	put_net(net);
err_net:
	return err;
}