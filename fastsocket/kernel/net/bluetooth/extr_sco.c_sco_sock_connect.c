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
struct sockaddr_sco {int /*<<< orphan*/  sco_bdaddr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct sock {scalar_t__ sk_state; scalar_t__ sk_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 scalar_t__ AF_BLUETOOTH ; 
 scalar_t__ BT_BOUND ; 
 int /*<<< orphan*/  BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct sock*) ; 
 scalar_t__ BT_OPEN ; 
 int EBADFD ; 
 int EINVAL ; 
 int O_NONBLOCK ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* bt_sk (struct sock*) ; 
 int bt_sock_wait_state (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int sco_connect (struct sock*) ; 
 int /*<<< orphan*/  sock_sndtimeo (struct sock*,int) ; 

__attribute__((used)) static int sco_sock_connect(struct socket *sock, struct sockaddr *addr, int alen, int flags)
{
	struct sockaddr_sco *sa = (struct sockaddr_sco *) addr;
	struct sock *sk = sock->sk;
	int err = 0;


	BT_DBG("sk %p", sk);

	if (addr->sa_family != AF_BLUETOOTH || alen < sizeof(struct sockaddr_sco))
		return -EINVAL;

	if (sk->sk_state != BT_OPEN && sk->sk_state != BT_BOUND)
		return -EBADFD;

	if (sk->sk_type != SOCK_SEQPACKET)
		return -EINVAL;

	lock_sock(sk);

	/* Set destination address and psm */
	bacpy(&bt_sk(sk)->dst, &sa->sco_bdaddr);

	if ((err = sco_connect(sk)))
		goto done;

	err = bt_sock_wait_state(sk, BT_CONNECTED,
			sock_sndtimeo(sk, flags & O_NONBLOCK));

done:
	release_sock(sk);
	return err;
}