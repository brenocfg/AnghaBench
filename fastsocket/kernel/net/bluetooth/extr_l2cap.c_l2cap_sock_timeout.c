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
struct sock {scalar_t__ sk_state; } ;
struct TYPE_2__ {scalar_t__ sec_level; } ;

/* Variables and functions */
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECT ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,scalar_t__) ; 
 scalar_t__ BT_SECURITY_SDP ; 
 int ECONNREFUSED ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  __l2cap_sock_close (struct sock*,int) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_kill (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void l2cap_sock_timeout(unsigned long arg)
{
	struct sock *sk = (struct sock *) arg;
	int reason;

	BT_DBG("sock %p state %d", sk, sk->sk_state);

	bh_lock_sock(sk);

	if (sk->sk_state == BT_CONNECTED || sk->sk_state == BT_CONFIG)
		reason = ECONNREFUSED;
	else if (sk->sk_state == BT_CONNECT &&
				l2cap_pi(sk)->sec_level != BT_SECURITY_SDP)
		reason = ECONNREFUSED;
	else
		reason = ETIMEDOUT;

	__l2cap_sock_close(sk, reason);

	bh_unlock_sock(sk);

	l2cap_sock_kill(sk);
	sock_put(sk);
}