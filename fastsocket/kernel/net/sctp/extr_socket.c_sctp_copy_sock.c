#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_sndtimeo; int /*<<< orphan*/  sk_rcvtimeo; int /*<<< orphan*/  sk_lingertime; int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_sndbuf; TYPE_1__* sk_prot; int /*<<< orphan*/  sk_backlog_rcv; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_family; int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_shutdown; int /*<<< orphan*/  sk_reuse; int /*<<< orphan*/  sk_no_check; int /*<<< orphan*/  sk_flags; int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;
struct sctp_association {int next_tsn; TYPE_2__ peer; } ;
struct inet_sock {int id; int mc_loop; int mc_ttl; int /*<<< orphan*/ * mc_list; scalar_t__ mc_index; int /*<<< orphan*/  uc_ttl; int /*<<< orphan*/  pmtudisc; int /*<<< orphan*/  dport; int /*<<< orphan*/  rcv_saddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  sport; } ;
struct TYPE_3__ {int /*<<< orphan*/  backlog_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_sock_destruct ; 
 int jiffies ; 

void sctp_copy_sock(struct sock *newsk, struct sock *sk,
		    struct sctp_association *asoc)
{
	struct inet_sock *inet = inet_sk(sk);
	struct inet_sock *newinet = inet_sk(newsk);

	newsk->sk_type = sk->sk_type;
	newsk->sk_bound_dev_if = sk->sk_bound_dev_if;
	newsk->sk_flags = sk->sk_flags;
	newsk->sk_no_check = sk->sk_no_check;
	newsk->sk_reuse = sk->sk_reuse;

	newsk->sk_shutdown = sk->sk_shutdown;
	newsk->sk_destruct = inet_sock_destruct;
	newsk->sk_family = sk->sk_family;
	newsk->sk_protocol = IPPROTO_SCTP;
	newsk->sk_backlog_rcv = sk->sk_prot->backlog_rcv;
	newsk->sk_sndbuf = sk->sk_sndbuf;
	newsk->sk_rcvbuf = sk->sk_rcvbuf;
	newsk->sk_lingertime = sk->sk_lingertime;
	newsk->sk_rcvtimeo = sk->sk_rcvtimeo;
	newsk->sk_sndtimeo = sk->sk_sndtimeo;

	newinet = inet_sk(newsk);

	/* Initialize sk's sport, dport, rcv_saddr and daddr for
	 * getsockname() and getpeername()
	 */
	newinet->sport = inet->sport;
	newinet->saddr = inet->saddr;
	newinet->rcv_saddr = inet->rcv_saddr;
	newinet->dport = htons(asoc->peer.port);
	newinet->pmtudisc = inet->pmtudisc;
	newinet->id = asoc->next_tsn ^ jiffies;

	newinet->uc_ttl = inet->uc_ttl;
	newinet->mc_loop = 1;
	newinet->mc_ttl = 1;
	newinet->mc_index = 0;
	newinet->mc_list = NULL;
}