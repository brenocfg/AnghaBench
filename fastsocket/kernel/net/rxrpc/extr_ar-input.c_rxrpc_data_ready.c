#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct udphdr {int dummy; } ;
struct sock {struct rxrpc_local* sk_user_data; } ;
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct rxrpc_transport {int dummy; } ;
struct TYPE_6__ {int flags; scalar_t__ epoch; scalar_t__ cid; scalar_t__ callNumber; scalar_t__ type; scalar_t__ seq; } ;
struct rxrpc_skb_priv {TYPE_2__ hdr; } ;
struct rxrpc_peer {int dummy; } ;
struct rxrpc_local {int /*<<< orphan*/  acceptor; int /*<<< orphan*/  accept_queue; int /*<<< orphan*/  usage; } ;
struct rxrpc_connection {int /*<<< orphan*/  debug_id; } ;
struct TYPE_7__ {scalar_t__ saddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BUG () ; 
 int EAGAIN ; 
 scalar_t__ IS_ERR (struct rxrpc_peer*) ; 
 int RXRPC_CLIENT_INITIATED ; 
 scalar_t__ RXRPC_N_PACKET_TYPES ; 
 scalar_t__ RXRPC_PACKET_TYPE_DATA ; 
 int /*<<< orphan*/  RX_CALL_DEAD ; 
 int /*<<< orphan*/  RX_INVALID_OPERATION ; 
 int /*<<< orphan*/  RX_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  UDP_INC_STATS_BH (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDP_MIB_INDATAGRAMS ; 
 int /*<<< orphan*/  UDP_MIB_INERRORS ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _enter (char*,struct sock*,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  _net (char*,...) ; 
 int /*<<< orphan*/  _proto (char*,scalar_t__) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int /*<<< orphan*/  init_net ; 
 TYPE_4__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  memset (struct rxrpc_skb_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (scalar_t__) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct rxrpc_connection* rxrpc_find_connection (struct rxrpc_transport*,TYPE_2__*) ; 
 struct rxrpc_peer* rxrpc_find_peer (struct rxrpc_local*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct rxrpc_transport* rxrpc_find_transport (struct rxrpc_local*,struct rxrpc_peer*) ; 
 int /*<<< orphan*/  rxrpc_free_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_get_local (struct rxrpc_local*) ; 
 int /*<<< orphan*/  rxrpc_local_lock ; 
 int /*<<< orphan*/  rxrpc_new_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_post_packet_to_call (struct rxrpc_connection*,struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_post_packet_to_conn (struct rxrpc_connection*,struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_put_connection (struct rxrpc_connection*) ; 
 int /*<<< orphan*/  rxrpc_put_local (struct rxrpc_local*) ; 
 int /*<<< orphan*/  rxrpc_put_peer (struct rxrpc_peer*) ; 
 int /*<<< orphan*/  rxrpc_put_transport (struct rxrpc_transport*) ; 
 int /*<<< orphan*/  rxrpc_queue_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_reject_packet (struct rxrpc_local*,struct sk_buff*) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 scalar_t__ skb_checksum_complete (struct sk_buff*) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int /*<<< orphan*/ ,int,int*) ; 
 TYPE_1__* udp_hdr (struct sk_buff*) ; 

void rxrpc_data_ready(struct sock *sk, int count)
{
	struct rxrpc_connection *conn;
	struct rxrpc_transport *trans;
	struct rxrpc_skb_priv *sp;
	struct rxrpc_local *local;
	struct rxrpc_peer *peer;
	struct sk_buff *skb;
	int ret;

	_enter("%p, %d", sk, count);

	ASSERT(!irqs_disabled());

	read_lock_bh(&rxrpc_local_lock);
	local = sk->sk_user_data;
	if (local && atomic_read(&local->usage) > 0)
		rxrpc_get_local(local);
	else
		local = NULL;
	read_unlock_bh(&rxrpc_local_lock);
	if (!local) {
		_leave(" [local dead]");
		return;
	}

	skb = skb_recv_datagram(sk, 0, 1, &ret);
	if (!skb) {
		rxrpc_put_local(local);
		if (ret == -EAGAIN)
			return;
		_debug("UDP socket error %d", ret);
		return;
	}

	rxrpc_new_skb(skb);

	_net("recv skb %p", skb);

	/* we'll probably need to checksum it (didn't call sock_recvmsg) */
	if (skb_checksum_complete(skb)) {
		rxrpc_free_skb(skb);
		rxrpc_put_local(local);
		UDP_INC_STATS_BH(&init_net, UDP_MIB_INERRORS, 0);
		_leave(" [CSUM failed]");
		return;
	}

	UDP_INC_STATS_BH(&init_net, UDP_MIB_INDATAGRAMS, 0);

	/* the socket buffer we have is owned by UDP, with UDP's data all over
	 * it, but we really want our own */
	skb_orphan(skb);
	sp = rxrpc_skb(skb);
	memset(sp, 0, sizeof(*sp));

	_net("Rx UDP packet from %08x:%04hu",
	     ntohl(ip_hdr(skb)->saddr), ntohs(udp_hdr(skb)->source));

	/* dig out the RxRPC connection details */
	if (skb_copy_bits(skb, sizeof(struct udphdr), &sp->hdr,
			  sizeof(sp->hdr)) < 0)
		goto bad_message;
	if (!pskb_pull(skb, sizeof(struct udphdr) + sizeof(sp->hdr)))
		BUG();

	_net("Rx RxRPC %s ep=%x call=%x:%x",
	     sp->hdr.flags & RXRPC_CLIENT_INITIATED ? "ToServer" : "ToClient",
	     ntohl(sp->hdr.epoch),
	     ntohl(sp->hdr.cid),
	     ntohl(sp->hdr.callNumber));

	if (sp->hdr.type == 0 || sp->hdr.type >= RXRPC_N_PACKET_TYPES) {
		_proto("Rx Bad Packet Type %u", sp->hdr.type);
		goto bad_message;
	}

	if (sp->hdr.type == RXRPC_PACKET_TYPE_DATA &&
	    (sp->hdr.callNumber == 0 || sp->hdr.seq == 0))
		goto bad_message;

	peer = rxrpc_find_peer(local, ip_hdr(skb)->saddr, udp_hdr(skb)->source);
	if (IS_ERR(peer))
		goto cant_route_call;

	trans = rxrpc_find_transport(local, peer);
	rxrpc_put_peer(peer);
	if (!trans)
		goto cant_route_call;

	conn = rxrpc_find_connection(trans, &sp->hdr);
	rxrpc_put_transport(trans);
	if (!conn)
		goto cant_route_call;

	_debug("CONN %p {%d}", conn, conn->debug_id);

	if (sp->hdr.callNumber == 0)
		rxrpc_post_packet_to_conn(conn, skb);
	else
		rxrpc_post_packet_to_call(conn, skb);
	rxrpc_put_connection(conn);
	rxrpc_put_local(local);
	return;

cant_route_call:
	_debug("can't route call");
	if (sp->hdr.flags & RXRPC_CLIENT_INITIATED &&
	    sp->hdr.type == RXRPC_PACKET_TYPE_DATA) {
		if (sp->hdr.seq == cpu_to_be32(1)) {
			_debug("first packet");
			skb_queue_tail(&local->accept_queue, skb);
			rxrpc_queue_work(&local->acceptor);
			rxrpc_put_local(local);
			_leave(" [incoming]");
			return;
		}
		skb->priority = RX_INVALID_OPERATION;
	} else {
		skb->priority = RX_CALL_DEAD;
	}

	_debug("reject");
	rxrpc_reject_packet(local, skb);
	rxrpc_put_local(local);
	_leave(" [no call]");
	return;

bad_message:
	skb->priority = RX_PROTOCOL_ERROR;
	rxrpc_reject_packet(local, skb);
	rxrpc_put_local(local);
	_leave(" [badmsg]");
}