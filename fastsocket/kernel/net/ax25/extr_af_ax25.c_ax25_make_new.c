#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_type; int /*<<< orphan*/  sk_destruct; TYPE_1__* sk_protinfo; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_sndbuf; int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_priority; int /*<<< orphan*/  sk_prot; } ;
struct ax25_dev {int dummy; } ;
typedef  int /*<<< orphan*/  ax25_digi ;
struct TYPE_5__ {struct sock* sk; int /*<<< orphan*/ * digipeat; int /*<<< orphan*/  source_addr; struct ax25_dev* ax25_dev; int /*<<< orphan*/  window; int /*<<< orphan*/  paclen; int /*<<< orphan*/  idle; int /*<<< orphan*/  n2; int /*<<< orphan*/  t3; int /*<<< orphan*/  t2; int /*<<< orphan*/  t1; int /*<<< orphan*/  rtt; int /*<<< orphan*/  iamdigi; int /*<<< orphan*/  pidincl; int /*<<< orphan*/  backoff; int /*<<< orphan*/  modulus; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PF_AX25 ; 
#define  SOCK_DGRAM 129 
#define  SOCK_SEQPACKET 128 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
 int /*<<< orphan*/  ax25_cb_put (TYPE_1__*) ; 
 TYPE_1__* ax25_create_cb () ; 
 int /*<<< orphan*/  ax25_free_sock ; 
 TYPE_1__* ax25_sk (struct sock*) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct sock* sk_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_free (struct sock*) ; 
 int /*<<< orphan*/  sock_copy_flags (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  sock_init_data (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

struct sock *ax25_make_new(struct sock *osk, struct ax25_dev *ax25_dev)
{
	struct sock *sk;
	ax25_cb *ax25, *oax25;

	sk = sk_alloc(sock_net(osk), PF_AX25, GFP_ATOMIC,	osk->sk_prot);
	if (sk == NULL)
		return NULL;

	if ((ax25 = ax25_create_cb()) == NULL) {
		sk_free(sk);
		return NULL;
	}

	switch (osk->sk_type) {
	case SOCK_DGRAM:
		break;
	case SOCK_SEQPACKET:
		break;
	default:
		sk_free(sk);
		ax25_cb_put(ax25);
		return NULL;
	}

	sock_init_data(NULL, sk);

	sk->sk_type     = osk->sk_type;
	sk->sk_priority = osk->sk_priority;
	sk->sk_protocol = osk->sk_protocol;
	sk->sk_rcvbuf   = osk->sk_rcvbuf;
	sk->sk_sndbuf   = osk->sk_sndbuf;
	sk->sk_state    = TCP_ESTABLISHED;
	sock_copy_flags(sk, osk);

	oax25 = ax25_sk(osk);

	ax25->modulus = oax25->modulus;
	ax25->backoff = oax25->backoff;
	ax25->pidincl = oax25->pidincl;
	ax25->iamdigi = oax25->iamdigi;
	ax25->rtt     = oax25->rtt;
	ax25->t1      = oax25->t1;
	ax25->t2      = oax25->t2;
	ax25->t3      = oax25->t3;
	ax25->n2      = oax25->n2;
	ax25->idle    = oax25->idle;
	ax25->paclen  = oax25->paclen;
	ax25->window  = oax25->window;

	ax25->ax25_dev    = ax25_dev;
	ax25->source_addr = oax25->source_addr;

	if (oax25->digipeat != NULL) {
		ax25->digipeat = kmemdup(oax25->digipeat, sizeof(ax25_digi),
					 GFP_ATOMIC);
		if (ax25->digipeat == NULL) {
			sk_free(sk);
			ax25_cb_put(ax25);
			return NULL;
		}
	}

	sk->sk_protinfo = ax25;
	sk->sk_destruct = ax25_free_sock;
	ax25->sk    = sk;

	return sk;
}