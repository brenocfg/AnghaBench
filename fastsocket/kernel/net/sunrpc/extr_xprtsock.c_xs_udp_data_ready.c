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
typedef  int /*<<< orphan*/  u32 ;
struct udphdr {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_callback_lock; } ;
struct sk_buff {int len; } ;
struct rpc_xprt {int /*<<< orphan*/  transport_lock; } ;
struct rpc_task {int dummy; } ;
struct TYPE_2__ {int buflen; } ;
struct rpc_rqst {TYPE_1__ rq_private_buf; struct rpc_task* rq_task; } ;
typedef  int /*<<< orphan*/  _xid ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  UDPX_INC_STATS_BH (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDP_MIB_INDATAGRAMS ; 
 int /*<<< orphan*/  UDP_MIB_INERRORS ; 
 scalar_t__ csum_partial_copy_to_xdr (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  dst_confirm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_header_pointer (struct sk_buff*,int,int,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_adjust_cwnd (struct rpc_task*,int) ; 
 int /*<<< orphan*/  xprt_complete_rqst (struct rpc_task*,int) ; 
 struct rpc_xprt* xprt_from_sock (struct sock*) ; 
 struct rpc_rqst* xprt_lookup_rqst (struct rpc_xprt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xs_udp_data_ready(struct sock *sk, int len)
{
	struct rpc_task *task;
	struct rpc_xprt *xprt;
	struct rpc_rqst *rovr;
	struct sk_buff *skb;
	int err, repsize, copied;
	u32 _xid;
	__be32 *xp;

	read_lock_bh(&sk->sk_callback_lock);
	dprintk("RPC:       xs_udp_data_ready...\n");
	if (!(xprt = xprt_from_sock(sk)))
		goto out;

	if ((skb = skb_recv_datagram(sk, 0, 1, &err)) == NULL)
		goto out;

	repsize = skb->len - sizeof(struct udphdr);
	if (repsize < 4) {
		dprintk("RPC:       impossible RPC reply size %d!\n", repsize);
		goto dropit;
	}

	/* Copy the XID from the skb... */
	xp = skb_header_pointer(skb, sizeof(struct udphdr),
				sizeof(_xid), &_xid);
	if (xp == NULL)
		goto dropit;

	/* Look up and lock the request corresponding to the given XID */
	spin_lock(&xprt->transport_lock);
	rovr = xprt_lookup_rqst(xprt, *xp);
	if (!rovr)
		goto out_unlock;
	task = rovr->rq_task;

	if ((copied = rovr->rq_private_buf.buflen) > repsize)
		copied = repsize;

	/* Suck it into the iovec, verify checksum if not done by hw. */
	if (csum_partial_copy_to_xdr(&rovr->rq_private_buf, skb)) {
		UDPX_INC_STATS_BH(sk, UDP_MIB_INERRORS);
		goto out_unlock;
	}

	UDPX_INC_STATS_BH(sk, UDP_MIB_INDATAGRAMS);

	/* Something worked... */
	dst_confirm(skb_dst(skb));

	xprt_adjust_cwnd(task, copied);
	xprt_complete_rqst(task, copied);

 out_unlock:
	spin_unlock(&xprt->transport_lock);
 dropit:
	skb_free_datagram(sk, skb);
 out:
	read_unlock_bh(&sk->sk_callback_lock);
}