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
struct TYPE_4__ {int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;
struct tipc_sock {TYPE_1__* p; TYPE_2__ peer_name; } ;
struct tipc_msg {int dummy; } ;
struct socket {int /*<<< orphan*/  state; int /*<<< orphan*/  sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int /*<<< orphan*/  SS_CONNECTED ; 
 int /*<<< orphan*/  SS_DISCONNECTING ; 
 scalar_t__ msg_errcode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_importance (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_orignode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_origport (struct tipc_msg*) ; 
 int /*<<< orphan*/  tipc_connect2port (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  tipc_set_portimportance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tipc_sock* tipc_sk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int auto_connect(struct socket *sock, struct tipc_msg *msg)
{
	struct tipc_sock *tsock = tipc_sk(sock->sk);

	if (msg_errcode(msg)) {
		sock->state = SS_DISCONNECTING;
		return -ECONNREFUSED;
	}

	tsock->peer_name.ref = msg_origport(msg);
	tsock->peer_name.node = msg_orignode(msg);
	tipc_connect2port(tsock->p->ref, &tsock->peer_name);
	tipc_set_portimportance(tsock->p->ref, msg_importance(msg));
	sock->state = SS_CONNECTED;
	return 0;
}