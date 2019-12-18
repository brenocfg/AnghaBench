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
struct sock {int /*<<< orphan*/  sk_state; } ;
struct TYPE_4__ {TYPE_1__* parent; int /*<<< orphan*/  accept_q; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_ack_backlog; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

void bt_accept_unlink(struct sock *sk)
{
	BT_DBG("sk %p state %d", sk, sk->sk_state);

	list_del_init(&bt_sk(sk)->accept_q);
	bt_sk(sk)->parent->sk_ack_backlog--;
	bt_sk(sk)->parent = NULL;
	sock_put(sk);
}