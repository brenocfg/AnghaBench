#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct ulptx_sgl {int dummy; } ;
struct skb_shared_info {int gso_size; int gso_type; scalar_t__ gso_segs; } ;
struct sk_buff {int len; scalar_t__ ip_summed; } ;
struct TYPE_14__ {size_t pidx; int size; TYPE_1__* sdesc; int /*<<< orphan*/ * desc; } ;
struct sge_eth_txq {TYPE_4__ q; int /*<<< orphan*/  vlan_ins; scalar_t__ tx_cso; int /*<<< orphan*/  tso; int /*<<< orphan*/  mapping_err; } ;
struct port_info {int first_qset; int /*<<< orphan*/  tx_chan; struct adapter* adapter; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct fw_eth_tx_pkt_wr {void* op_immdlen; void* r3; void* equiq_to_len16; } ;
struct TYPE_13__ {void* len; void* seqno_offset; void* mss; void* ipid_ofst; void* lso_ctrl; } ;
struct cpl_tx_pkt_lso {TYPE_3__ c; } ;
struct cpl_tx_pkt_core {void* ctrl1; void* len; void* pack; void* ctrl0; } ;
struct TYPE_12__ {struct sge_eth_txq* ethtxq; } ;
struct adapter {int /*<<< orphan*/  fn; int /*<<< orphan*/  pdev_dev; TYPE_2__ sge; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_15__ {int /*<<< orphan*/  doff; } ;
struct TYPE_11__ {struct ulptx_sgl* sgl; struct sk_buff* skb; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  CPL_TX_PKT_LSO ; 
 int /*<<< orphan*/  CPL_TX_PKT_XT ; 
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned int,int) ; 
 int ETHTXQ_STOP_THRES ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  FW_ETH_TX_PKT_WR ; 
 int FW_WR_EQUEQ ; 
 int FW_WR_EQUIQ ; 
 int FW_WR_IMMDLEN (int) ; 
 int FW_WR_LEN16 (int /*<<< orphan*/ ) ; 
 int FW_WR_OP (int /*<<< orphan*/ ) ; 
 int LSO_ETHHDR_LEN (int) ; 
 int LSO_FIRST_SLICE ; 
 int LSO_IPHDR_LEN (int) ; 
 int LSO_IPV6 (int) ; 
 int LSO_LAST_SLICE ; 
 int LSO_OPCODE (int /*<<< orphan*/ ) ; 
 int LSO_TCPHDR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int SKB_GSO_TCPV6 ; 
 int TXPKT_CSUM_TYPE (int /*<<< orphan*/ ) ; 
 int TXPKT_ETHHDR_LEN (int) ; 
 int TXPKT_INTF (int /*<<< orphan*/ ) ; 
 int TXPKT_IPCSUM_DIS ; 
 int TXPKT_IPHDR_LEN (int) ; 
 int TXPKT_L4CSUM_DIS ; 
 int TXPKT_OPCODE (int /*<<< orphan*/ ) ; 
 int TXPKT_PF (int /*<<< orphan*/ ) ; 
 int TXPKT_VLAN (int /*<<< orphan*/ ) ; 
 int TXPKT_VLAN_VLD ; 
 int /*<<< orphan*/  TX_CSUM_TCPIP ; 
 int /*<<< orphan*/  TX_CSUM_TCPIP6 ; 
 unsigned int calc_tx_flits (struct sk_buff*) ; 
 void* cpu_to_be64 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_txq_stop (struct sge_eth_txq*) ; 
 unsigned int flits_to_desc (unsigned int) ; 
 void* htonl (int) ; 
 void* htons (int) ; 
 int hwcsum (struct sk_buff*) ; 
 int /*<<< orphan*/  inline_tx_skb (struct sk_buff*,TYPE_4__*,struct cpl_tx_pkt_core*) ; 
 scalar_t__ is_eth_imm (struct sk_buff*) ; 
 scalar_t__ map_skb (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  reclaim_completed_tx (struct adapter*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  ring_tx_db (struct adapter*,TYPE_4__*,unsigned int) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int skb_network_header_len (struct sk_buff*) ; 
 int skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff*) ; 
 TYPE_7__* tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  txq_advance (TYPE_4__*,unsigned int) ; 
 unsigned int txq_avail (TYPE_4__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlan_tx_tag_get (struct sk_buff*) ; 
 scalar_t__ vlan_tx_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  write_sgl (struct sk_buff*,TYPE_4__*,struct ulptx_sgl*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

netdev_tx_t t4_eth_xmit(struct sk_buff *skb, struct net_device *dev)
{
	u32 wr_mid;
	u64 cntrl, *end;
	int qidx, credits;
	unsigned int flits, ndesc;
	struct adapter *adap;
	struct sge_eth_txq *q;
	const struct port_info *pi;
	struct fw_eth_tx_pkt_wr *wr;
	struct cpl_tx_pkt_core *cpl;
	const struct skb_shared_info *ssi;
	dma_addr_t addr[MAX_SKB_FRAGS + 1];

	/*
	 * The chip min packet length is 10 octets but play safe and reject
	 * anything shorter than an Ethernet header.
	 */
	if (unlikely(skb->len < ETH_HLEN)) {
out_free:	dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	pi = netdev_priv(dev);
	adap = pi->adapter;
	qidx = skb_get_queue_mapping(skb);
	q = &adap->sge.ethtxq[qidx + pi->first_qset];

	reclaim_completed_tx(adap, &q->q, true);

	flits = calc_tx_flits(skb);
	ndesc = flits_to_desc(flits);
	credits = txq_avail(&q->q) - ndesc;

	if (unlikely(credits < 0)) {
		eth_txq_stop(q);
		dev_err(adap->pdev_dev,
			"%s: Tx ring %u full while queue awake!\n",
			dev->name, qidx);
		return NETDEV_TX_BUSY;
	}

	if (!is_eth_imm(skb) &&
	    unlikely(map_skb(adap->pdev_dev, skb, addr) < 0)) {
		q->mapping_err++;
		goto out_free;
	}

	wr_mid = FW_WR_LEN16(DIV_ROUND_UP(flits, 2));
	if (unlikely(credits < ETHTXQ_STOP_THRES)) {
		eth_txq_stop(q);
		wr_mid |= FW_WR_EQUEQ | FW_WR_EQUIQ;
	}

	wr = (void *)&q->q.desc[q->q.pidx];
	wr->equiq_to_len16 = htonl(wr_mid);
	wr->r3 = cpu_to_be64(0);
	end = (u64 *)wr + flits;

	ssi = skb_shinfo(skb);
	if (ssi->gso_size) {
		struct cpl_tx_pkt_lso *lso = (void *)wr;
		bool v6 = (ssi->gso_type & SKB_GSO_TCPV6) != 0;
		int l3hdr_len = skb_network_header_len(skb);
		int eth_xtra_len = skb_network_offset(skb) - ETH_HLEN;

		wr->op_immdlen = htonl(FW_WR_OP(FW_ETH_TX_PKT_WR) |
				       FW_WR_IMMDLEN(sizeof(*lso)));
		lso->c.lso_ctrl = htonl(LSO_OPCODE(CPL_TX_PKT_LSO) |
					LSO_FIRST_SLICE | LSO_LAST_SLICE |
					LSO_IPV6(v6) |
					LSO_ETHHDR_LEN(eth_xtra_len / 4) |
					LSO_IPHDR_LEN(l3hdr_len / 4) |
					LSO_TCPHDR_LEN(tcp_hdr(skb)->doff));
		lso->c.ipid_ofst = htons(0);
		lso->c.mss = htons(ssi->gso_size);
		lso->c.seqno_offset = htonl(0);
		lso->c.len = htonl(skb->len);
		cpl = (void *)(lso + 1);
		cntrl = TXPKT_CSUM_TYPE(v6 ? TX_CSUM_TCPIP6 : TX_CSUM_TCPIP) |
			TXPKT_IPHDR_LEN(l3hdr_len) |
			TXPKT_ETHHDR_LEN(eth_xtra_len);
		q->tso++;
		q->tx_cso += ssi->gso_segs;
	} else {
		int len;

		len = is_eth_imm(skb) ? skb->len + sizeof(*cpl) : sizeof(*cpl);
		wr->op_immdlen = htonl(FW_WR_OP(FW_ETH_TX_PKT_WR) |
				       FW_WR_IMMDLEN(len));
		cpl = (void *)(wr + 1);
		if (skb->ip_summed == CHECKSUM_PARTIAL) {
			cntrl = hwcsum(skb) | TXPKT_IPCSUM_DIS;
			q->tx_cso++;
		} else
			cntrl = TXPKT_L4CSUM_DIS | TXPKT_IPCSUM_DIS;
	}

	if (vlan_tx_tag_present(skb)) {
		q->vlan_ins++;
		cntrl |= TXPKT_VLAN_VLD | TXPKT_VLAN(vlan_tx_tag_get(skb));
	}

	cpl->ctrl0 = htonl(TXPKT_OPCODE(CPL_TX_PKT_XT) |
			   TXPKT_INTF(pi->tx_chan) | TXPKT_PF(adap->fn));
	cpl->pack = htons(0);
	cpl->len = htons(skb->len);
	cpl->ctrl1 = cpu_to_be64(cntrl);

	if (is_eth_imm(skb)) {
		inline_tx_skb(skb, &q->q, cpl + 1);
		dev_kfree_skb(skb);
	} else {
		int last_desc;

		write_sgl(skb, &q->q, (struct ulptx_sgl *)(cpl + 1), end, 0,
			  addr);
		skb_orphan(skb);

		last_desc = q->q.pidx + ndesc - 1;
		if (last_desc >= q->q.size)
			last_desc -= q->q.size;
		q->q.sdesc[last_desc].skb = skb;
		q->q.sdesc[last_desc].sgl = (struct ulptx_sgl *)(cpl + 1);
	}

	txq_advance(&q->q, ndesc);

	ring_tx_db(adap, &q->q, ndesc);
	return NETDEV_TX_OK;
}