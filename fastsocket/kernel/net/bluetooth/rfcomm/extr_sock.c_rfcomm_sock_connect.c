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
struct socket {struct sock* sk; } ;
struct sockaddr_rc {int /*<<< orphan*/  rc_channel; int /*<<< orphan*/  rc_bdaddr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct sock {scalar_t__ sk_state; scalar_t__ sk_type; } ;
struct rfcomm_dlc {int /*<<< orphan*/  role_switch; int /*<<< orphan*/  sec_level; } ;
struct TYPE_4__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_3__ {int /*<<< orphan*/  role_switch; int /*<<< orphan*/  sec_level; int /*<<< orphan*/  channel; struct rfcomm_dlc* dlc; } ;

/* Variables and functions */
 scalar_t__ AF_BLUETOOTH ; 
 scalar_t__ BT_BOUND ; 
 scalar_t__ BT_CONNECT ; 
 int /*<<< orphan*/  BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct sock*) ; 
 scalar_t__ BT_OPEN ; 
 int EBADFD ; 
 int EINVAL ; 
 int O_NONBLOCK ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 int bt_sock_wait_state (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int rfcomm_dlc_open (struct rfcomm_dlc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* rfcomm_pi (struct sock*) ; 
 int /*<<< orphan*/  sock_sndtimeo (struct sock*,int) ; 

__attribute__((used)) static int rfcomm_sock_connect(struct socket *sock, struct sockaddr *addr, int alen, int flags)
{
	struct sockaddr_rc *sa = (struct sockaddr_rc *) addr;
	struct sock *sk = sock->sk;
	struct rfcomm_dlc *d = rfcomm_pi(sk)->dlc;
	int err = 0;

	BT_DBG("sk %p", sk);

	if (addr->sa_family != AF_BLUETOOTH || alen < sizeof(struct sockaddr_rc))
		return -EINVAL;

	lock_sock(sk);

	if (sk->sk_state != BT_OPEN && sk->sk_state != BT_BOUND) {
		err = -EBADFD;
		goto done;
	}

	if (sk->sk_type != SOCK_STREAM) {
		err = -EINVAL;
		goto done;
	}

	sk->sk_state = BT_CONNECT;
	bacpy(&bt_sk(sk)->dst, &sa->rc_bdaddr);
	rfcomm_pi(sk)->channel = sa->rc_channel;

	d->sec_level = rfcomm_pi(sk)->sec_level;
	d->role_switch = rfcomm_pi(sk)->role_switch;

	err = rfcomm_dlc_open(d, &bt_sk(sk)->src, &sa->rc_bdaddr, sa->rc_channel);
	if (!err)
		err = bt_sock_wait_state(sk, BT_CONNECTED,
				sock_sndtimeo(sk, flags & O_NONBLOCK));

done:
	release_sock(sk);
	return err;
}