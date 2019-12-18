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
struct rxrpc_security {int (* init_connection_security ) (struct rxrpc_connection*) ;} ;
struct rxrpc_key_token {int /*<<< orphan*/  security_index; } ;
struct rxrpc_connection {struct rxrpc_security* security; int /*<<< orphan*/  debug_id; struct key* key; } ;
struct TYPE_2__ {struct rxrpc_key_token* data; } ;
struct key {TYPE_1__ payload; } ;

/* Variables and functions */
 int EKEYREJECTED ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int key_validate (struct key*) ; 
 struct rxrpc_security* rxrpc_security_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_security_put (struct rxrpc_security*) ; 
 int stub1 (struct rxrpc_connection*) ; 

int rxrpc_init_client_conn_security(struct rxrpc_connection *conn)
{
	struct rxrpc_key_token *token;
	struct rxrpc_security *sec;
	struct key *key = conn->key;
	int ret;

	_enter("{%d},{%x}", conn->debug_id, key_serial(key));

	if (!key)
		return 0;

	ret = key_validate(key);
	if (ret < 0)
		return ret;

	if (!key->payload.data)
		return -EKEYREJECTED;
	token = key->payload.data;

	sec = rxrpc_security_lookup(token->security_index);
	if (!sec)
		return -EKEYREJECTED;
	conn->security = sec;

	ret = conn->security->init_connection_security(conn);
	if (ret < 0) {
		rxrpc_security_put(conn->security);
		conn->security = NULL;
		return ret;
	}

	_leave(" = 0");
	return 0;
}