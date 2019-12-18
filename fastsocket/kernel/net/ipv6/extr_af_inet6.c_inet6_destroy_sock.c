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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ipv6_txoptions {int /*<<< orphan*/  tot_len; } ;
struct ipv6_pinfo {int /*<<< orphan*/  opt; int /*<<< orphan*/  pktoptions; } ;

/* Variables and functions */
 int /*<<< orphan*/  fl6_free_socklist (struct sock*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct ipv6_txoptions*,int /*<<< orphan*/ ) ; 
 void* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void inet6_destroy_sock(struct sock *sk)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct sk_buff *skb;
	struct ipv6_txoptions *opt;

	/* Release rx options */

	if ((skb = xchg(&np->pktoptions, NULL)) != NULL)
		kfree_skb(skb);

	/* Free flowlabels */
	fl6_free_socklist(sk);

	/* Free tx options */

	if ((opt = xchg(&np->opt, NULL)) != NULL)
		sock_kfree_s(sk, opt, opt->tot_len);
}