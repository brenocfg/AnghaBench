#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {TYPE_2__* sk_prot; } ;
struct TYPE_5__ {int /*<<< orphan*/  primary_addr; } ;
struct sctp_association {TYPE_1__ peer; } ;
struct sctp6_sock {int /*<<< orphan*/  inet6; } ;
struct ipv6_pinfo {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pinet6; } ;
struct TYPE_7__ {int /*<<< orphan*/  v4mapped; } ;
struct TYPE_6__ {scalar_t__ (* init ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 TYPE_4__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  memcpy (struct ipv6_pinfo*,struct ipv6_pinfo*,int) ; 
 int /*<<< orphan*/  sctp_copy_sock (struct sock*,struct sock*,struct sctp_association*) ; 
 TYPE_3__* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/  sctp_v6_to_sk_daddr (int /*<<< orphan*/ *,struct sock*) ; 
 struct sock* sk_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  sk_common_release (struct sock*) ; 
 int /*<<< orphan*/  sk_refcnt_debug_inc (struct sock*) ; 
 int /*<<< orphan*/  sock_init_data (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct sock*) ; 

__attribute__((used)) static struct sock *sctp_v6_create_accept_sk(struct sock *sk,
					     struct sctp_association *asoc)
{
	struct sock *newsk;
	struct ipv6_pinfo *newnp, *np = inet6_sk(sk);
	struct sctp6_sock *newsctp6sk;

	newsk = sk_alloc(sock_net(sk), PF_INET6, GFP_KERNEL, sk->sk_prot);
	if (!newsk)
		goto out;

	sock_init_data(NULL, newsk);

	sctp_copy_sock(newsk, sk, asoc);
	sock_reset_flag(sk, SOCK_ZAPPED);

	newsctp6sk = (struct sctp6_sock *)newsk;
	inet_sk(newsk)->pinet6 = &newsctp6sk->inet6;

	sctp_sk(newsk)->v4mapped = sctp_sk(sk)->v4mapped;

	newnp = inet6_sk(newsk);

	memcpy(newnp, np, sizeof(struct ipv6_pinfo));

	/* Initialize sk's sport, dport, rcv_saddr and daddr for getsockname()
	 * and getpeername().
	 */
	sctp_v6_to_sk_daddr(&asoc->peer.primary_addr, newsk);

	sk_refcnt_debug_inc(newsk);

	if (newsk->sk_prot->init(newsk)) {
		sk_common_release(newsk);
		newsk = NULL;
	}

out:
	return newsk;
}