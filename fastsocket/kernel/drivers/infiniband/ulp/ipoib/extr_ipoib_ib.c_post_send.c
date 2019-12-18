#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct ipoib_tx_buf {void** mapping; struct sk_buff* skb; } ;
struct TYPE_8__ {int hlen; void* header; int /*<<< orphan*/  mss; struct ib_ah* ah; int /*<<< orphan*/  remote_qpn; } ;
struct TYPE_9__ {TYPE_2__ ud; } ;
struct TYPE_12__ {int num_sge; unsigned int wr_id; int /*<<< orphan*/  opcode; TYPE_3__ wr; } ;
struct ipoib_dev_priv {TYPE_6__ tx_wr; int /*<<< orphan*/  qp; TYPE_1__* tx_sge; } ;
struct ib_send_wr {int dummy; } ;
struct ib_ah {int dummy; } ;
struct TYPE_10__ {scalar_t__ size; } ;
typedef  TYPE_4__ skb_frag_t ;
struct TYPE_11__ {int nr_frags; int /*<<< orphan*/  gso_size; TYPE_4__* frags; } ;
struct TYPE_7__ {scalar_t__ length; void* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WR_LSO ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int ib_post_send (int /*<<< orphan*/ ,TYPE_6__*,struct ib_send_wr**) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 TYPE_5__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline int post_send(struct ipoib_dev_priv *priv,
			    unsigned int wr_id,
			    struct ib_ah *address, u32 qpn,
			    struct ipoib_tx_buf *tx_req,
			    void *head, int hlen)
{
	struct ib_send_wr *bad_wr;
	int i, off;
	struct sk_buff *skb = tx_req->skb;
	skb_frag_t *frags = skb_shinfo(skb)->frags;
	int nr_frags = skb_shinfo(skb)->nr_frags;
	u64 *mapping = tx_req->mapping;

	if (skb_headlen(skb)) {
		priv->tx_sge[0].addr         = mapping[0];
		priv->tx_sge[0].length       = skb_headlen(skb);
		off = 1;
	} else
		off = 0;

	for (i = 0; i < nr_frags; ++i) {
		priv->tx_sge[i + off].addr = mapping[i + off];
		priv->tx_sge[i + off].length = frags[i].size;
	}
	priv->tx_wr.num_sge	     = nr_frags + off;
	priv->tx_wr.wr_id 	     = wr_id;
	priv->tx_wr.wr.ud.remote_qpn = qpn;
	priv->tx_wr.wr.ud.ah 	     = address;

	if (head) {
		priv->tx_wr.wr.ud.mss	 = skb_shinfo(skb)->gso_size;
		priv->tx_wr.wr.ud.header = head;
		priv->tx_wr.wr.ud.hlen	 = hlen;
		priv->tx_wr.opcode	 = IB_WR_LSO;
	} else
		priv->tx_wr.opcode	 = IB_WR_SEND;

	return ib_post_send(priv->qp, &priv->tx_wr, &bad_wr);
}