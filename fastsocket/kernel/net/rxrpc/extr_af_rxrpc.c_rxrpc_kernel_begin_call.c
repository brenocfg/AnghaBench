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
struct socket {int /*<<< orphan*/  sk; } ;
struct sockaddr_rxrpc {int /*<<< orphan*/  srx_service; } ;
struct sockaddr {int dummy; } ;
struct rxrpc_transport {int /*<<< orphan*/  usage; } ;
struct rxrpc_sock {int /*<<< orphan*/  sk; struct key* key; int /*<<< orphan*/  service_id; struct rxrpc_transport* trans; } ;
struct rxrpc_conn_bundle {int /*<<< orphan*/  usage; } ;
struct rxrpc_call {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct key {TYPE_1__ payload; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTCONN ; 
 struct rxrpc_call* ERR_CAST (struct rxrpc_transport*) ; 
 struct rxrpc_call* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct rxrpc_transport*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_call*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  lock_sock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (int /*<<< orphan*/ *) ; 
 struct rxrpc_transport* rxrpc_get_bundle (struct rxrpc_sock*,struct rxrpc_transport*,struct key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rxrpc_call* rxrpc_get_client_call (struct rxrpc_sock*,struct rxrpc_transport*,struct rxrpc_transport*,unsigned long,int,int /*<<< orphan*/ ) ; 
 struct rxrpc_transport* rxrpc_name_to_transport (struct socket*,struct sockaddr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_put_bundle (struct rxrpc_transport*,struct rxrpc_transport*) ; 
 int /*<<< orphan*/  rxrpc_put_transport (struct rxrpc_transport*) ; 
 struct rxrpc_sock* rxrpc_sk (int /*<<< orphan*/ ) ; 

struct rxrpc_call *rxrpc_kernel_begin_call(struct socket *sock,
					   struct sockaddr_rxrpc *srx,
					   struct key *key,
					   unsigned long user_call_ID,
					   gfp_t gfp)
{
	struct rxrpc_conn_bundle *bundle;
	struct rxrpc_transport *trans;
	struct rxrpc_call *call;
	struct rxrpc_sock *rx = rxrpc_sk(sock->sk);
	__be16 service_id;

	_enter(",,%x,%lx", key_serial(key), user_call_ID);

	lock_sock(&rx->sk);

	if (srx) {
		trans = rxrpc_name_to_transport(sock, (struct sockaddr *) srx,
						sizeof(*srx), 0, gfp);
		if (IS_ERR(trans)) {
			call = ERR_CAST(trans);
			trans = NULL;
			goto out_notrans;
		}
	} else {
		trans = rx->trans;
		if (!trans) {
			call = ERR_PTR(-ENOTCONN);
			goto out_notrans;
		}
		atomic_inc(&trans->usage);
	}

	service_id = rx->service_id;
	if (srx)
		service_id = htons(srx->srx_service);

	if (!key)
		key = rx->key;
	if (key && !key->payload.data)
		key = NULL; /* a no-security key */

	bundle = rxrpc_get_bundle(rx, trans, key, service_id, gfp);
	if (IS_ERR(bundle)) {
		call = ERR_CAST(bundle);
		goto out;
	}

	call = rxrpc_get_client_call(rx, trans, bundle, user_call_ID, true,
				     gfp);
	rxrpc_put_bundle(trans, bundle);
out:
	rxrpc_put_transport(trans);
out_notrans:
	release_sock(&rx->sk);
	_leave(" = %p", call);
	return call;
}