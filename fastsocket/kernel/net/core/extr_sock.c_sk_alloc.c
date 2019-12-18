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
struct sock {int sk_family; int /*<<< orphan*/  sk_wmem_alloc; struct proto* sk_prot_creator; struct proto* sk_prot; } ;
struct proto {int dummy; } ;
struct net {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_ZERO ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_net (struct net*) ; 
 struct sock* sk_prot_alloc (struct proto*,int,int) ; 
 int /*<<< orphan*/  sock_lock_init (struct sock*) ; 
 int /*<<< orphan*/  sock_net_set (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_update_classid (struct sock*) ; 
 int /*<<< orphan*/  sock_update_netprioidx (struct sock*) ; 

struct sock *sk_alloc(struct net *net, int family, gfp_t priority,
		      struct proto *prot)
{
	struct sock *sk;

	sk = sk_prot_alloc(prot, priority | __GFP_ZERO, family);
	if (sk) {
		sk->sk_family = family;
		/*
		 * See comment in struct sock definition to understand
		 * why we need sk_prot_creator -acme
		 */
		sk->sk_prot = sk->sk_prot_creator = prot;
		sock_lock_init(sk);
		sock_net_set(sk, get_net(net));
		atomic_set(&sk->sk_wmem_alloc, 1);

		sock_update_classid(sk);
		sock_update_netprioidx(sk);
	}

	return sk;
}