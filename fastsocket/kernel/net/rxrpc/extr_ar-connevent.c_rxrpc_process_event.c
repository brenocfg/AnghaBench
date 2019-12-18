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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tmp ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int type; int /*<<< orphan*/  serial; } ;
struct rxrpc_skb_priv {TYPE_2__ hdr; } ;
struct rxrpc_connection {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  state_lock; int /*<<< orphan*/ * channels; TYPE_1__* security; int /*<<< orphan*/  debug_id; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int (* respond_to_challenge ) (struct rxrpc_connection*,struct sk_buff*,int /*<<< orphan*/ *) ;int (* verify_response ) (struct rxrpc_connection*,struct sk_buff*,int /*<<< orphan*/ *) ;int (* init_connection_security ) (struct rxrpc_connection*) ;int /*<<< orphan*/  (* prime_packet_security ) (struct rxrpc_connection*) ;} ;

/* Variables and functions */
 int ECONNABORTED ; 
 int EPROTO ; 
 int /*<<< orphan*/  RXRPC_CALL_REMOTELY_ABORTED ; 
 scalar_t__ RXRPC_CONN_REMOTELY_ABORTED ; 
 scalar_t__ RXRPC_CONN_SERVER ; 
 scalar_t__ RXRPC_CONN_SERVER_CHALLENGING ; 
 int RXRPC_MAXCALLS ; 
#define  RXRPC_PACKET_TYPE_ABORT 130 
#define  RXRPC_PACKET_TYPE_CHALLENGE 129 
#define  RXRPC_PACKET_TYPE_RESPONSE 128 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  _proto (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kleave (char*,scalar_t__) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_abort_calls (struct rxrpc_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_call_is_secure (int /*<<< orphan*/ ) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct rxrpc_connection*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int stub2 (struct rxrpc_connection*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int stub3 (struct rxrpc_connection*) ; 
 int /*<<< orphan*/  stub4 (struct rxrpc_connection*) ; 

__attribute__((used)) static int rxrpc_process_event(struct rxrpc_connection *conn,
			       struct sk_buff *skb,
			       u32 *_abort_code)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);
	__be32 tmp;
	u32 serial;
	int loop, ret;

	if (conn->state >= RXRPC_CONN_REMOTELY_ABORTED) {
		kleave(" = -ECONNABORTED [%u]", conn->state);
		return -ECONNABORTED;
	}

	serial = ntohl(sp->hdr.serial);

	_enter("{%d},{%u,%%%u},", conn->debug_id, sp->hdr.type, serial);

	switch (sp->hdr.type) {
	case RXRPC_PACKET_TYPE_ABORT:
		if (skb_copy_bits(skb, 0, &tmp, sizeof(tmp)) < 0)
			return -EPROTO;
		_proto("Rx ABORT %%%u { ac=%d }", serial, ntohl(tmp));

		conn->state = RXRPC_CONN_REMOTELY_ABORTED;
		rxrpc_abort_calls(conn, RXRPC_CALL_REMOTELY_ABORTED,
				  ntohl(tmp));
		return -ECONNABORTED;

	case RXRPC_PACKET_TYPE_CHALLENGE:
		if (conn->security)
			return conn->security->respond_to_challenge(
				conn, skb, _abort_code);
		return -EPROTO;

	case RXRPC_PACKET_TYPE_RESPONSE:
		if (!conn->security)
			return -EPROTO;

		ret = conn->security->verify_response(conn, skb, _abort_code);
		if (ret < 0)
			return ret;

		ret = conn->security->init_connection_security(conn);
		if (ret < 0)
			return ret;

		conn->security->prime_packet_security(conn);
		read_lock_bh(&conn->lock);
		spin_lock(&conn->state_lock);

		if (conn->state == RXRPC_CONN_SERVER_CHALLENGING) {
			conn->state = RXRPC_CONN_SERVER;
			for (loop = 0; loop < RXRPC_MAXCALLS; loop++)
				rxrpc_call_is_secure(conn->channels[loop]);
		}

		spin_unlock(&conn->state_lock);
		read_unlock_bh(&conn->lock);
		return 0;

	default:
		_leave(" = -EPROTO [%u]", sp->hdr.type);
		return -EPROTO;
	}
}