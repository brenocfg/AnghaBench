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
struct sockaddr_ieee802154 {scalar_t__ family; int /*<<< orphan*/  addr; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct net_device {scalar_t__ type; } ;
struct ieee802154_addr {int dummy; } ;
struct dgram_sock {int bound; int /*<<< orphan*/  src_addr; } ;

/* Variables and functions */
 scalar_t__ AF_IEEE802154 ; 
 scalar_t__ ARPHRD_IEEE802154 ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct dgram_sock* dgram_sk (struct sock*) ; 
 struct net_device* ieee802154_get_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int dgram_bind(struct sock *sk, struct sockaddr *uaddr, int len)
{
	struct sockaddr_ieee802154 *addr = (struct sockaddr_ieee802154 *)uaddr;
	struct dgram_sock *ro = dgram_sk(sk);
	int err = -EINVAL;
	struct net_device *dev;

	lock_sock(sk);

	ro->bound = 0;

	if (len < sizeof(*addr))
		goto out;

	if (addr->family != AF_IEEE802154)
		goto out;

	dev = ieee802154_get_dev(sock_net(sk), &addr->addr);
	if (!dev) {
		err = -ENODEV;
		goto out;
	}

	if (dev->type != ARPHRD_IEEE802154) {
		err = -ENODEV;
		goto out_put;
	}

	memcpy(&ro->src_addr, &addr->addr, sizeof(struct ieee802154_addr));

	ro->bound = 1;
	err = 0;
out_put:
	dev_put(dev);
out:
	release_sock(sk);

	return err;
}