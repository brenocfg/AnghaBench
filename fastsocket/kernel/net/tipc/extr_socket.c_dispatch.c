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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_port {scalar_t__ usr_handle; } ;
struct sock {int /*<<< orphan*/  sk_rcvbuf; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_ERR_OVERLOAD ; 
 int /*<<< orphan*/  TIPC_OK ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  filter_rcv (struct sock*,struct sk_buff*) ; 
 scalar_t__ sk_add_backlog (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 

__attribute__((used)) static u32 dispatch(struct tipc_port *tport, struct sk_buff *buf)
{
	struct sock *sk = (struct sock *)tport->usr_handle;
	u32 res;

	/*
	 * Process message if socket is unlocked; otherwise add to backlog queue
	 *
	 * This code is based on sk_receive_skb(), but must be distinct from it
	 * since a TIPC-specific filter/reject mechanism is utilized
	 */

	bh_lock_sock(sk);
	if (!sock_owned_by_user(sk)) {
		res = filter_rcv(sk, buf);
	} else {
		if (sk_add_backlog(sk, buf, sk->sk_rcvbuf))
			res = TIPC_ERR_OVERLOAD;
		else
			res = TIPC_OK;
	}
	bh_unlock_sock(sk);

	return res;
}