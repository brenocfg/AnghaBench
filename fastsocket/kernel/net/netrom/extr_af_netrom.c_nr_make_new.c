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
struct sock {scalar_t__ sk_type; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_sndbuf; int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_priority; int /*<<< orphan*/  sk_prot; } ;
struct nr_sock {int /*<<< orphan*/  bpqext; int /*<<< orphan*/  device; int /*<<< orphan*/  window; int /*<<< orphan*/  idle; int /*<<< orphan*/  t4; int /*<<< orphan*/  n2; int /*<<< orphan*/  t2; int /*<<< orphan*/  t1; int /*<<< orphan*/  frag_queue; int /*<<< orphan*/  reseq_queue; int /*<<< orphan*/  ack_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PF_NETROM ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
 int /*<<< orphan*/  nr_init_timers (struct sock*) ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 struct sock* sk_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_copy_flags (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  sock_init_data (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static struct sock *nr_make_new(struct sock *osk)
{
	struct sock *sk;
	struct nr_sock *nr, *onr;

	if (osk->sk_type != SOCK_SEQPACKET)
		return NULL;

	sk = sk_alloc(sock_net(osk), PF_NETROM, GFP_ATOMIC, osk->sk_prot);
	if (sk == NULL)
		return NULL;

	nr = nr_sk(sk);

	sock_init_data(NULL, sk);

	sk->sk_type     = osk->sk_type;
	sk->sk_priority = osk->sk_priority;
	sk->sk_protocol = osk->sk_protocol;
	sk->sk_rcvbuf   = osk->sk_rcvbuf;
	sk->sk_sndbuf   = osk->sk_sndbuf;
	sk->sk_state    = TCP_ESTABLISHED;
	sock_copy_flags(sk, osk);

	skb_queue_head_init(&nr->ack_queue);
	skb_queue_head_init(&nr->reseq_queue);
	skb_queue_head_init(&nr->frag_queue);

	nr_init_timers(sk);

	onr = nr_sk(osk);

	nr->t1      = onr->t1;
	nr->t2      = onr->t2;
	nr->n2      = onr->n2;
	nr->t4      = onr->t4;
	nr->idle    = onr->idle;
	nr->window  = onr->window;

	nr->device  = onr->device;
	nr->bpqext  = onr->bpqext;

	return sk;
}