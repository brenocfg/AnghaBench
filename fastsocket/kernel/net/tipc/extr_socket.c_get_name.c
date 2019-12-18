#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;
struct tipc_sock {TYPE_2__* p; TYPE_1__ peer_name; } ;
struct socket {scalar_t__ state; int /*<<< orphan*/  sk; } ;
struct TYPE_8__ {scalar_t__ domain; } ;
struct TYPE_10__ {int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;
struct TYPE_9__ {TYPE_3__ name; TYPE_5__ id; } ;
struct sockaddr_tipc {TYPE_4__ addr; scalar_t__ scope; int /*<<< orphan*/  family; int /*<<< orphan*/  addrtype; } ;
struct sockaddr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_TIPC ; 
 int ENOTCONN ; 
 scalar_t__ SS_CONNECTED ; 
 scalar_t__ SS_DISCONNECTING ; 
 int /*<<< orphan*/  TIPC_ADDR_ID ; 
 int /*<<< orphan*/  tipc_ownidentity (int /*<<< orphan*/ ,TYPE_5__*) ; 
 struct tipc_sock* tipc_sk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_name(struct socket *sock, struct sockaddr *uaddr,
		    int *uaddr_len, int peer)
{
	struct sockaddr_tipc *addr = (struct sockaddr_tipc *)uaddr;
	struct tipc_sock *tsock = tipc_sk(sock->sk);

	if (peer) {
		if ((sock->state != SS_CONNECTED) &&
			((peer != 2) || (sock->state != SS_DISCONNECTING)))
			return -ENOTCONN;
		addr->addr.id.ref = tsock->peer_name.ref;
		addr->addr.id.node = tsock->peer_name.node;
	} else {
		tipc_ownidentity(tsock->p->ref, &addr->addr.id);
	}

	*uaddr_len = sizeof(*addr);
	addr->addrtype = TIPC_ADDR_ID;
	addr->family = AF_TIPC;
	addr->scope = 0;
	addr->addr.name.domain = 0;

	return 0;
}