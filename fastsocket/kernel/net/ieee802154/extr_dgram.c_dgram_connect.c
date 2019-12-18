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
struct ieee802154_addr {int dummy; } ;
struct dgram_sock {int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  bound; } ;

/* Variables and functions */
 scalar_t__ AF_IEEE802154 ; 
 int EINVAL ; 
 int ENETUNREACH ; 
 struct dgram_sock* dgram_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int dgram_connect(struct sock *sk, struct sockaddr *uaddr,
			int len)
{
	struct sockaddr_ieee802154 *addr = (struct sockaddr_ieee802154 *)uaddr;
	struct dgram_sock *ro = dgram_sk(sk);
	int err = 0;

	if (len < sizeof(*addr))
		return -EINVAL;

	if (addr->family != AF_IEEE802154)
		return -EINVAL;

	lock_sock(sk);

	if (!ro->bound) {
		err = -ENETUNREACH;
		goto out;
	}

	memcpy(&ro->dst_addr, &addr->addr, sizeof(struct ieee802154_addr));

out:
	release_sock(sk);
	return err;
}