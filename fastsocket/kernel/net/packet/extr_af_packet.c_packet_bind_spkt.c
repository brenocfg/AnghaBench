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
struct socket {struct sock* sk; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct sock {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 struct net_device* dev_get_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int packet_do_bind (struct sock*,struct net_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* pkt_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int packet_bind_spkt(struct socket *sock, struct sockaddr *uaddr,
			    int addr_len)
{
	struct sock *sk = sock->sk;
	char name[15];
	struct net_device *dev;
	int err = -ENODEV;

	/*
	 *	Check legality
	 */

	if (addr_len != sizeof(struct sockaddr))
		return -EINVAL;
	strlcpy(name, uaddr->sa_data, sizeof(name));

	dev = dev_get_by_name(sock_net(sk), name);
	if (dev) {
		err = packet_do_bind(sk, dev, pkt_sk(sk)->num);
		dev_put(dev);
	}
	return err;
}