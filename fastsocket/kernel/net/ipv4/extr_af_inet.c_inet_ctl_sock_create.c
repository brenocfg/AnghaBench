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
struct sock {TYPE_1__* sk_prot; int /*<<< orphan*/  sk_allocation; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unhash ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  sk_change_net (struct sock*,struct net*) ; 
 int sock_create_kern (unsigned short,unsigned short,unsigned char,struct socket**) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

int inet_ctl_sock_create(struct sock **sk, unsigned short family,
			 unsigned short type, unsigned char protocol,
			 struct net *net)
{
	struct socket *sock;
	int rc = sock_create_kern(family, type, protocol, &sock);

	if (rc == 0) {
		*sk = sock->sk;
		(*sk)->sk_allocation = GFP_ATOMIC;
		/*
		 * Unhash it so that IP input processing does not even see it,
		 * we do not wish this socket to see incoming packets.
		 */
		(*sk)->sk_prot->unhash(*sk);

		sk_change_net(*sk, net);
	}
	return rc;
}