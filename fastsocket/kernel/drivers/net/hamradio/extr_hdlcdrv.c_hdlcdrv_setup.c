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
struct net_device {int tx_queue_len; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  mtu; scalar_t__ hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_12__ {int shreg; scalar_t__ wr; scalar_t__ rd; } ;
struct TYPE_11__ {int shreg; scalar_t__ wr; scalar_t__ rd; } ;
struct TYPE_9__ {scalar_t__ wr; scalar_t__ rd; int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {int tx_state; scalar_t__ calibrate; int /*<<< orphan*/  slotcnt; scalar_t__ ptt; scalar_t__ numbits; scalar_t__ bitbuf; scalar_t__ bitstream; scalar_t__ numflags; scalar_t__ in_hdlc_tx; TYPE_3__ hbuf; } ;
struct hdlcdrv_channel_params {int member_0; int member_1; int member_2; int member_3; int /*<<< orphan*/  slottime; int /*<<< orphan*/  member_4; } ;
struct TYPE_7__ {scalar_t__ wr; scalar_t__ rd; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {scalar_t__ rx_state; scalar_t__ in_hdlc_rx; TYPE_1__ hbuf; } ;
struct hdlcdrv_state {int /*<<< orphan*/ * skb; TYPE_6__ bitbuf_hdlc; TYPE_5__ bitbuf_channel; TYPE_4__ hdlctx; struct hdlcdrv_channel_params ch_params; TYPE_2__ hdlcrx; scalar_t__ ptt_keyed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_AX25 ; 
 int /*<<< orphan*/  AX25_ADDR_LEN ; 
 scalar_t__ AX25_BPQ_HEADER_LEN ; 
 int /*<<< orphan*/  AX25_DEF_PACLEN ; 
 scalar_t__ AX25_MAX_HEADER_LEN ; 
 int /*<<< orphan*/  ax25_bcast ; 
 int /*<<< orphan*/  ax25_defaddr ; 
 int /*<<< orphan*/  ax25_header_ops ; 
 int /*<<< orphan*/  hdlcdrv_netdev ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hdlcdrv_state* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdlcdrv_setup(struct net_device *dev)
{
	static const struct hdlcdrv_channel_params dflt_ch_params = { 
		20, 2, 10, 40, 0 
	};
	struct hdlcdrv_state *s = netdev_priv(dev);

	/*
	 * initialize the hdlcdrv_state struct
	 */
	s->ch_params = dflt_ch_params;
	s->ptt_keyed = 0;

	spin_lock_init(&s->hdlcrx.hbuf.lock);
	s->hdlcrx.hbuf.rd = s->hdlcrx.hbuf.wr = 0;
	s->hdlcrx.in_hdlc_rx = 0;
	s->hdlcrx.rx_state = 0;
	
	spin_lock_init(&s->hdlctx.hbuf.lock);
	s->hdlctx.hbuf.rd = s->hdlctx.hbuf.wr = 0;
	s->hdlctx.in_hdlc_tx = 0;
	s->hdlctx.tx_state = 1;
	s->hdlctx.numflags = 0;
	s->hdlctx.bitstream = s->hdlctx.bitbuf = s->hdlctx.numbits = 0;
	s->hdlctx.ptt = 0;
	s->hdlctx.slotcnt = s->ch_params.slottime;
	s->hdlctx.calibrate = 0;

#ifdef HDLCDRV_DEBUG
	s->bitbuf_channel.rd = s->bitbuf_channel.wr = 0;
	s->bitbuf_channel.shreg = 0x80;

	s->bitbuf_hdlc.rd = s->bitbuf_hdlc.wr = 0;
	s->bitbuf_hdlc.shreg = 0x80;
#endif /* HDLCDRV_DEBUG */


	/* Fill in the fields of the device structure */

	s->skb = NULL;
	
	dev->netdev_ops = &hdlcdrv_netdev;
	dev->header_ops = &ax25_header_ops;
	
	dev->type = ARPHRD_AX25;           /* AF_AX25 device */
	dev->hard_header_len = AX25_MAX_HEADER_LEN + AX25_BPQ_HEADER_LEN;
	dev->mtu = AX25_DEF_PACLEN;        /* eth_mtu is the default */
	dev->addr_len = AX25_ADDR_LEN;     /* sizeof an ax.25 address */
	memcpy(dev->broadcast, &ax25_bcast, AX25_ADDR_LEN);
	memcpy(dev->dev_addr, &ax25_defaddr, AX25_ADDR_LEN);
	dev->tx_queue_len = 16;
}