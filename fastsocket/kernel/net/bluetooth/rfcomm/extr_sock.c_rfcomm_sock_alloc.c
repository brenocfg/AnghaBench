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
struct socket {int dummy; } ;
struct sock {int sk_sndbuf; int sk_rcvbuf; int sk_protocol; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_sndtimeo; int /*<<< orphan*/  sk_destruct; } ;
struct rfcomm_dlc {struct sock* owner; int /*<<< orphan*/  state_change; int /*<<< orphan*/  data_ready; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  accept_q; } ;
struct TYPE_3__ {struct rfcomm_dlc* dlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*) ; 
 int /*<<< orphan*/  BT_OPEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 int /*<<< orphan*/  RFCOMM_CONN_TIMEOUT ; 
 int RFCOMM_DEFAULT_MTU ; 
 int RFCOMM_MAX_CREDITS ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  bt_sock_link (int /*<<< orphan*/ *,struct sock*) ; 
 struct rfcomm_dlc* rfcomm_dlc_alloc (int /*<<< orphan*/ ) ; 
 TYPE_1__* rfcomm_pi (struct sock*) ; 
 int /*<<< orphan*/  rfcomm_proto ; 
 int /*<<< orphan*/  rfcomm_sk_data_ready ; 
 int /*<<< orphan*/  rfcomm_sk_list ; 
 int /*<<< orphan*/  rfcomm_sk_state_change ; 
 int /*<<< orphan*/  rfcomm_sock_destruct ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_free (struct sock*) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sock *rfcomm_sock_alloc(struct net *net, struct socket *sock, int proto, gfp_t prio)
{
	struct rfcomm_dlc *d;
	struct sock *sk;

	sk = sk_alloc(net, PF_BLUETOOTH, prio, &rfcomm_proto);
	if (!sk)
		return NULL;

	sock_init_data(sock, sk);
	INIT_LIST_HEAD(&bt_sk(sk)->accept_q);

	d = rfcomm_dlc_alloc(prio);
	if (!d) {
		sk_free(sk);
		return NULL;
	}

	d->data_ready   = rfcomm_sk_data_ready;
	d->state_change = rfcomm_sk_state_change;

	rfcomm_pi(sk)->dlc = d;
	d->owner = sk;

	sk->sk_destruct = rfcomm_sock_destruct;
	sk->sk_sndtimeo = RFCOMM_CONN_TIMEOUT;

	sk->sk_sndbuf = RFCOMM_MAX_CREDITS * RFCOMM_DEFAULT_MTU * 10;
	sk->sk_rcvbuf = RFCOMM_MAX_CREDITS * RFCOMM_DEFAULT_MTU * 10;

	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = proto;
	sk->sk_state    = BT_OPEN;

	bt_sock_link(&rfcomm_sk_list, sk);

	BT_DBG("sk %p", sk);
	return sk;
}