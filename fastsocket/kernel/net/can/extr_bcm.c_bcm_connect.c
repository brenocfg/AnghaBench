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
struct socket {struct sock* sk; } ;
struct sockaddr_can {scalar_t__ can_ifindex; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct net_device {scalar_t__ type; scalar_t__ ifindex; } ;
struct bcm_sock {int bound; int /*<<< orphan*/  procname; int /*<<< orphan*/  bcm_proc_read; scalar_t__ ifindex; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_CAN ; 
 int EISCONN ; 
 int ENODEV ; 
 int /*<<< orphan*/  bcm_proc_fops ; 
 struct bcm_sock* bcm_sk (struct sock*) ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  proc_create_data (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *,struct sock*) ; 
 scalar_t__ proc_dir ; 
 int /*<<< orphan*/  sock_i_ino (struct sock*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_connect(struct socket *sock, struct sockaddr *uaddr, int len,
		       int flags)
{
	struct sockaddr_can *addr = (struct sockaddr_can *)uaddr;
	struct sock *sk = sock->sk;
	struct bcm_sock *bo = bcm_sk(sk);

	if (bo->bound)
		return -EISCONN;

	/* bind a device to this socket */
	if (addr->can_ifindex) {
		struct net_device *dev;

		dev = dev_get_by_index(&init_net, addr->can_ifindex);
		if (!dev)
			return -ENODEV;

		if (dev->type != ARPHRD_CAN) {
			dev_put(dev);
			return -ENODEV;
		}

		bo->ifindex = dev->ifindex;
		dev_put(dev);

	} else {
		/* no interface reference for ifindex = 0 ('any' CAN device) */
		bo->ifindex = 0;
	}

	bo->bound = 1;

	if (proc_dir) {
		/* unique socket address as filename */
		sprintf(bo->procname, "%lu", sock_i_ino(sk));
		bo->bcm_proc_read = proc_create_data(bo->procname, 0644,
						     proc_dir,
						     &bcm_proc_fops, sk);
	}

	return 0;
}