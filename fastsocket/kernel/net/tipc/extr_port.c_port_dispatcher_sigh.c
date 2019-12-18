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
typedef  int u32 ;
typedef  int /*<<< orphan*/  (* tipc_named_msg_event ) (void*,int,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tipc_portid*,struct tipc_name_seq*) ;
typedef  int /*<<< orphan*/  (* tipc_named_msg_err_event ) (void*,int,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct tipc_name_seq*) ;
typedef  int /*<<< orphan*/  (* tipc_msg_event ) (void*,int,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tipc_portid*) ;
typedef  int /*<<< orphan*/  (* tipc_msg_err_event ) (void*,int,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct tipc_portid*) ;
typedef  int /*<<< orphan*/  (* tipc_conn_shutdown_event ) (void*,int,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;
typedef  int /*<<< orphan*/  (* tipc_conn_msg_event ) (void*,int,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct user_port {int /*<<< orphan*/  (* named_err_cb ) (void*,int,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct tipc_name_seq*) ;int /*<<< orphan*/  (* err_cb ) (void*,int,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct tipc_portid*) ;int /*<<< orphan*/  (* conn_err_cb ) (void*,int,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* named_msg_cb ) (void*,int,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tipc_portid*,struct tipc_name_seq*) ;int /*<<< orphan*/  (* msg_cb ) (void*,int,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tipc_portid*) ;int /*<<< orphan*/  (* conn_msg_cb ) (void*,int,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;void* usr_handle; } ;
struct tipc_portid {int ref; int node; } ;
struct tipc_name_seq {void* lower; void* upper; void* type; } ;
struct tipc_msg {int dummy; } ;
struct sk_buff {struct sk_buff* next; } ;
struct TYPE_2__ {int connected; int published; int /*<<< orphan*/  conn_unacked; } ;
struct port {TYPE_1__ publ; struct user_port* user_port; } ;

/* Variables and functions */
#define  TIPC_CONN_MSG 131 
#define  TIPC_DIRECT_MSG 130 
 int /*<<< orphan*/  TIPC_ERR_NO_PORT ; 
 int /*<<< orphan*/  TIPC_FLOW_CONTROL_WIN ; 
#define  TIPC_MCAST_MSG 129 
#define  TIPC_NAMED_MSG 128 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_data (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_data_sz (struct tipc_msg*) ; 
 int msg_destport (struct tipc_msg*) ; 
 int msg_errcode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_hdr_sz (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_importance (struct tipc_msg*) ; 
 void* msg_nameinst (struct tipc_msg*) ; 
 void* msg_nametype (struct tipc_msg*) ; 
 void* msg_nameupper (struct tipc_msg*) ; 
 int msg_orignode (struct tipc_msg*) ; 
 int msg_origport (struct tipc_msg*) ; 
 struct sk_buff* msg_queue_head ; 
 int msg_type (struct tipc_msg*) ; 
 int port_peernode (struct port*) ; 
 int port_peerport (struct port*) ; 
 int /*<<< orphan*/  queue_lock ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_acknowledge (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_connect2port (int,struct tipc_portid*) ; 
 int /*<<< orphan*/  tipc_disconnect (int) ; 
 struct port* tipc_port_lock (int) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 
 int /*<<< orphan*/  tipc_reject_msg (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void port_dispatcher_sigh(void *dummy)
{
	struct sk_buff *buf;

	spin_lock_bh(&queue_lock);
	buf = msg_queue_head;
	msg_queue_head = NULL;
	spin_unlock_bh(&queue_lock);

	while (buf) {
		struct port *p_ptr;
		struct user_port *up_ptr;
		struct tipc_portid orig;
		struct tipc_name_seq dseq;
		void *usr_handle;
		int connected;
		int published;
		u32 message_type;

		struct sk_buff *next = buf->next;
		struct tipc_msg *msg = buf_msg(buf);
		u32 dref = msg_destport(msg);

		message_type = msg_type(msg);
		if (message_type > TIPC_DIRECT_MSG)
			goto reject;	/* Unsupported message type */

		p_ptr = tipc_port_lock(dref);
		if (!p_ptr)
			goto reject;	/* Port deleted while msg in queue */

		orig.ref = msg_origport(msg);
		orig.node = msg_orignode(msg);
		up_ptr = p_ptr->user_port;
		usr_handle = up_ptr->usr_handle;
		connected = p_ptr->publ.connected;
		published = p_ptr->publ.published;

		if (unlikely(msg_errcode(msg)))
			goto err;

		switch (message_type) {

		case TIPC_CONN_MSG:{
				tipc_conn_msg_event cb = up_ptr->conn_msg_cb;
				u32 peer_port = port_peerport(p_ptr);
				u32 peer_node = port_peernode(p_ptr);

				tipc_port_unlock(p_ptr);
				if (unlikely(!cb))
					goto reject;
				if (unlikely(!connected)) {
					if (tipc_connect2port(dref, &orig))
						goto reject;
				} else if ((msg_origport(msg) != peer_port) ||
					   (msg_orignode(msg) != peer_node))
					goto reject;
				if (unlikely(++p_ptr->publ.conn_unacked >=
					     TIPC_FLOW_CONTROL_WIN))
					tipc_acknowledge(dref,
							 p_ptr->publ.conn_unacked);
				skb_pull(buf, msg_hdr_sz(msg));
				cb(usr_handle, dref, &buf, msg_data(msg),
				   msg_data_sz(msg));
				break;
			}
		case TIPC_DIRECT_MSG:{
				tipc_msg_event cb = up_ptr->msg_cb;

				tipc_port_unlock(p_ptr);
				if (unlikely(!cb || connected))
					goto reject;
				skb_pull(buf, msg_hdr_sz(msg));
				cb(usr_handle, dref, &buf, msg_data(msg),
				   msg_data_sz(msg), msg_importance(msg),
				   &orig);
				break;
			}
		case TIPC_MCAST_MSG:
		case TIPC_NAMED_MSG:{
				tipc_named_msg_event cb = up_ptr->named_msg_cb;

				tipc_port_unlock(p_ptr);
				if (unlikely(!cb || connected || !published))
					goto reject;
				dseq.type =  msg_nametype(msg);
				dseq.lower = msg_nameinst(msg);
				dseq.upper = (message_type == TIPC_NAMED_MSG)
					? dseq.lower : msg_nameupper(msg);
				skb_pull(buf, msg_hdr_sz(msg));
				cb(usr_handle, dref, &buf, msg_data(msg),
				   msg_data_sz(msg), msg_importance(msg),
				   &orig, &dseq);
				break;
			}
		}
		if (buf)
			buf_discard(buf);
		buf = next;
		continue;
err:
		switch (message_type) {

		case TIPC_CONN_MSG:{
				tipc_conn_shutdown_event cb =
					up_ptr->conn_err_cb;
				u32 peer_port = port_peerport(p_ptr);
				u32 peer_node = port_peernode(p_ptr);

				tipc_port_unlock(p_ptr);
				if (!cb || !connected)
					break;
				if ((msg_origport(msg) != peer_port) ||
				    (msg_orignode(msg) != peer_node))
					break;
				tipc_disconnect(dref);
				skb_pull(buf, msg_hdr_sz(msg));
				cb(usr_handle, dref, &buf, msg_data(msg),
				   msg_data_sz(msg), msg_errcode(msg));
				break;
			}
		case TIPC_DIRECT_MSG:{
				tipc_msg_err_event cb = up_ptr->err_cb;

				tipc_port_unlock(p_ptr);
				if (!cb || connected)
					break;
				skb_pull(buf, msg_hdr_sz(msg));
				cb(usr_handle, dref, &buf, msg_data(msg),
				   msg_data_sz(msg), msg_errcode(msg), &orig);
				break;
			}
		case TIPC_MCAST_MSG:
		case TIPC_NAMED_MSG:{
				tipc_named_msg_err_event cb =
					up_ptr->named_err_cb;

				tipc_port_unlock(p_ptr);
				if (!cb || connected)
					break;
				dseq.type =  msg_nametype(msg);
				dseq.lower = msg_nameinst(msg);
				dseq.upper = (message_type == TIPC_NAMED_MSG)
					? dseq.lower : msg_nameupper(msg);
				skb_pull(buf, msg_hdr_sz(msg));
				cb(usr_handle, dref, &buf, msg_data(msg),
				   msg_data_sz(msg), msg_errcode(msg), &dseq);
				break;
			}
		}
		if (buf)
			buf_discard(buf);
		buf = next;
		continue;
reject:
		tipc_reject_msg(buf, TIPC_ERR_NO_PORT);
		buf = next;
	}
}