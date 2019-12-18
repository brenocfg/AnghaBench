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
struct x25_sock {int /*<<< orphan*/  accptapprv; int /*<<< orphan*/  cudmatchlength; int /*<<< orphan*/  dte_facilities; int /*<<< orphan*/  qbitincl; int /*<<< orphan*/  facilities; int /*<<< orphan*/  t2; int /*<<< orphan*/  t23; int /*<<< orphan*/  t22; int /*<<< orphan*/  t21; } ;
struct sock {scalar_t__ sk_type; int /*<<< orphan*/  sk_backlog_rcv; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_sndbuf; int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_priority; } ;

/* Variables and functions */
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
 int /*<<< orphan*/  sock_copy_flags (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 struct sock* x25_alloc_socket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x25_init_timers (struct sock*) ; 
 struct x25_sock* x25_sk (struct sock*) ; 

__attribute__((used)) static struct sock *x25_make_new(struct sock *osk)
{
	struct sock *sk = NULL;
	struct x25_sock *x25, *ox25;

	if (osk->sk_type != SOCK_SEQPACKET)
		goto out;

	if ((sk = x25_alloc_socket(sock_net(osk))) == NULL)
		goto out;

	x25 = x25_sk(sk);

	sk->sk_type        = osk->sk_type;
	sk->sk_priority    = osk->sk_priority;
	sk->sk_protocol    = osk->sk_protocol;
	sk->sk_rcvbuf      = osk->sk_rcvbuf;
	sk->sk_sndbuf      = osk->sk_sndbuf;
	sk->sk_state       = TCP_ESTABLISHED;
	sk->sk_backlog_rcv = osk->sk_backlog_rcv;
	sock_copy_flags(sk, osk);

	ox25 = x25_sk(osk);
	x25->t21        = ox25->t21;
	x25->t22        = ox25->t22;
	x25->t23        = ox25->t23;
	x25->t2         = ox25->t2;
	x25->facilities = ox25->facilities;
	x25->qbitincl   = ox25->qbitincl;
	x25->dte_facilities = ox25->dte_facilities;
	x25->cudmatchlength = ox25->cudmatchlength;
	x25->accptapprv = ox25->accptapprv;

	x25_init_timers(sk);
out:
	return sk;
}