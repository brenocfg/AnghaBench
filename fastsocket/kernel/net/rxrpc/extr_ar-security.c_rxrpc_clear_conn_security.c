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
struct rxrpc_connection {int /*<<< orphan*/  server_key; int /*<<< orphan*/  key; TYPE_1__* security; int /*<<< orphan*/  debug_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clear ) (struct rxrpc_connection*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_security_put (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct rxrpc_connection*) ; 

void rxrpc_clear_conn_security(struct rxrpc_connection *conn)
{
	_enter("{%d}", conn->debug_id);

	if (conn->security) {
		conn->security->clear(conn);
		rxrpc_security_put(conn->security);
		conn->security = NULL;
	}

	key_put(conn->key);
	key_put(conn->server_key);
}