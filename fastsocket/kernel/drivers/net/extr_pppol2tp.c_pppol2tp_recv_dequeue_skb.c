#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_state; } ;
struct sk_buff {int dummy; } ;
struct pppox_sock {int /*<<< orphan*/  chan; } ;
struct TYPE_4__ {int rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct pppol2tp_tunnel {TYPE_1__ stats; } ;
struct TYPE_5__ {int rx_bytes; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; } ;
struct pppol2tp_session {struct sock* sock; TYPE_2__ stats; int /*<<< orphan*/  name; int /*<<< orphan*/  debug; int /*<<< orphan*/  nr; struct pppol2tp_tunnel* tunnel; } ;
struct TYPE_6__ {int length; scalar_t__ has_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PPPOL2TP_MSG_DATA ; 
 int /*<<< orphan*/  PPPOL2TP_MSG_SEQ ; 
 TYPE_3__* PPPOL2TP_SKB_CB (struct sk_buff*) ; 
 int PPPOX_BOUND ; 
 int /*<<< orphan*/  PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  ppp_input (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct pppox_sock* pppox_sk (struct sock*) ; 
 int /*<<< orphan*/  secpath_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void pppol2tp_recv_dequeue_skb(struct pppol2tp_session *session, struct sk_buff *skb)
{
	struct pppol2tp_tunnel *tunnel = session->tunnel;
	int length = PPPOL2TP_SKB_CB(skb)->length;
	struct sock *session_sock = NULL;

	/* We're about to requeue the skb, so return resources
	 * to its current owner (a socket receive buffer).
	 */
	skb_orphan(skb);

	tunnel->stats.rx_packets++;
	tunnel->stats.rx_bytes += length;
	session->stats.rx_packets++;
	session->stats.rx_bytes += length;

	if (PPPOL2TP_SKB_CB(skb)->has_seq) {
		/* Bump our Nr */
		session->nr++;
		PRINTK(session->debug, PPPOL2TP_MSG_SEQ, KERN_DEBUG,
		       "%s: updated nr to %hu\n", session->name, session->nr);
	}

	/* If the socket is bound, send it in to PPP's input queue. Otherwise
	 * queue it on the session socket.
	 */
	session_sock = session->sock;
	if (session_sock->sk_state & PPPOX_BOUND) {
		struct pppox_sock *po;
		PRINTK(session->debug, PPPOL2TP_MSG_DATA, KERN_DEBUG,
		       "%s: recv %d byte data frame, passing to ppp\n",
		       session->name, length);

		/* We need to forget all info related to the L2TP packet
		 * gathered in the skb as we are going to reuse the same
		 * skb for the inner packet.
		 * Namely we need to:
		 * - reset xfrm (IPSec) information as it applies to
		 *   the outer L2TP packet and not to the inner one
		 * - release the dst to force a route lookup on the inner
		 *   IP packet since skb->dst currently points to the dst
		 *   of the UDP tunnel
		 * - reset netfilter information as it doesn't apply
		 *   to the inner packet either
		 */
		secpath_reset(skb);
		skb_dst_drop(skb);
		nf_reset(skb);

		po = pppox_sk(session_sock);
		ppp_input(&po->chan, skb);
	} else {
		PRINTK(session->debug, PPPOL2TP_MSG_DATA, KERN_INFO,
		       "%s: socket not bound\n", session->name);

		/* Not bound. Nothing we can do, so discard. */
		session->stats.rx_errors++;
		kfree_skb(skb);
	}

	sock_put(session->sock);
}