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
struct vhost_net {int /*<<< orphan*/  dev; } ;
struct socket {int /*<<< orphan*/  file; } ;
struct inode {int dummy; } ;
struct file {struct vhost_net* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vhost_net*) ; 
 int /*<<< orphan*/  vhost_dev_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_net_flush (struct vhost_net*) ; 
 int /*<<< orphan*/  vhost_net_stop (struct vhost_net*,struct socket**,struct socket**) ; 

__attribute__((used)) static int vhost_net_release(struct inode *inode, struct file *f)
{
	struct vhost_net *n = f->private_data;
	struct socket *tx_sock;
	struct socket *rx_sock;

	vhost_net_stop(n, &tx_sock, &rx_sock);
	vhost_net_flush(n);
	vhost_dev_cleanup(&n->dev);
	if (tx_sock)
		fput(tx_sock->file);
	if (rx_sock)
		fput(rx_sock->file);
	/* We do an extra flush before freeing memory,
	 * since jobs can re-queue themselves. */
	vhost_net_flush(n);
	kfree(n);
	return 0;
}