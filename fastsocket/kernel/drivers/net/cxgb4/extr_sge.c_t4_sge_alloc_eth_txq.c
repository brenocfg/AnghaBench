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
struct tx_sw_desc {int dummy; } ;
struct tx_desc {int dummy; } ;
struct TYPE_2__ {int size; int /*<<< orphan*/ * desc; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/ * sdesc; } ;
struct sge_eth_txq {scalar_t__ mapping_err; scalar_t__ vlan_ins; scalar_t__ tx_cso; scalar_t__ tso; struct netdev_queue* txq; TYPE_1__ q; } ;
struct port_info {int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  viid; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct fw_eq_eth_cmd {int /*<<< orphan*/  eqid_pkd; int /*<<< orphan*/  eqaddr; void* dcaen_to_eqsize; void* fetchszm_to_iqid; void* viid_pkd; void* alloc_to_len16; void* op_to_vfn; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; int /*<<< orphan*/  fn; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int ENOMEM ; 
 int FW_CMD_EXEC ; 
 int FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST ; 
 int FW_CMD_WRITE ; 
 int /*<<< orphan*/  FW_EQ_ETH_CMD ; 
 int FW_EQ_ETH_CMD_ALLOC ; 
 int FW_EQ_ETH_CMD_CIDXFTHRESH (int) ; 
 int /*<<< orphan*/  FW_EQ_ETH_CMD_EQID_GET (int /*<<< orphan*/ ) ; 
 int FW_EQ_ETH_CMD_EQSIZE (int) ; 
 int FW_EQ_ETH_CMD_EQSTART ; 
 int FW_EQ_ETH_CMD_FBMAX (int) ; 
 int FW_EQ_ETH_CMD_FBMIN (int) ; 
 int FW_EQ_ETH_CMD_FETCHRO (int) ; 
 int FW_EQ_ETH_CMD_HOSTFCMODE (int) ; 
 int FW_EQ_ETH_CMD_IQID (unsigned int) ; 
 int FW_EQ_ETH_CMD_PCIECHN (int /*<<< orphan*/ ) ; 
 int FW_EQ_ETH_CMD_PFN (int /*<<< orphan*/ ) ; 
 int FW_EQ_ETH_CMD_VFN (int /*<<< orphan*/ ) ; 
 int FW_EQ_ETH_CMD_VIID (int /*<<< orphan*/ ) ; 
 int FW_LEN16 (struct fw_eq_eth_cmd) ; 
 int STAT_LEN ; 
 int /*<<< orphan*/ * alloc_ring (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  init_txq (struct adapter*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fw_eq_eth_cmd*,int /*<<< orphan*/ ,int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_eq_eth_cmd*,int,struct fw_eq_eth_cmd*) ; 

int t4_sge_alloc_eth_txq(struct adapter *adap, struct sge_eth_txq *txq,
			 struct net_device *dev, struct netdev_queue *netdevq,
			 unsigned int iqid)
{
	int ret, nentries;
	struct fw_eq_eth_cmd c;
	struct port_info *pi = netdev_priv(dev);

	/* Add status entries */
	nentries = txq->q.size + STAT_LEN / sizeof(struct tx_desc);

	txq->q.desc = alloc_ring(adap->pdev_dev, txq->q.size,
			sizeof(struct tx_desc), sizeof(struct tx_sw_desc),
			&txq->q.phys_addr, &txq->q.sdesc, STAT_LEN);
	if (!txq->q.desc)
		return -ENOMEM;

	memset(&c, 0, sizeof(c));
	c.op_to_vfn = htonl(FW_CMD_OP(FW_EQ_ETH_CMD) | FW_CMD_REQUEST |
			    FW_CMD_WRITE | FW_CMD_EXEC |
			    FW_EQ_ETH_CMD_PFN(adap->fn) | FW_EQ_ETH_CMD_VFN(0));
	c.alloc_to_len16 = htonl(FW_EQ_ETH_CMD_ALLOC |
				 FW_EQ_ETH_CMD_EQSTART | FW_LEN16(c));
	c.viid_pkd = htonl(FW_EQ_ETH_CMD_VIID(pi->viid));
	c.fetchszm_to_iqid = htonl(FW_EQ_ETH_CMD_HOSTFCMODE(2) |
				   FW_EQ_ETH_CMD_PCIECHN(pi->tx_chan) |
				   FW_EQ_ETH_CMD_FETCHRO(1) |
				   FW_EQ_ETH_CMD_IQID(iqid));
	c.dcaen_to_eqsize = htonl(FW_EQ_ETH_CMD_FBMIN(2) |
				  FW_EQ_ETH_CMD_FBMAX(3) |
				  FW_EQ_ETH_CMD_CIDXFTHRESH(5) |
				  FW_EQ_ETH_CMD_EQSIZE(nentries));
	c.eqaddr = cpu_to_be64(txq->q.phys_addr);

	ret = t4_wr_mbox(adap, adap->fn, &c, sizeof(c), &c);
	if (ret) {
		kfree(txq->q.sdesc);
		txq->q.sdesc = NULL;
		dma_free_coherent(adap->pdev_dev,
				  nentries * sizeof(struct tx_desc),
				  txq->q.desc, txq->q.phys_addr);
		txq->q.desc = NULL;
		return ret;
	}

	init_txq(adap, &txq->q, FW_EQ_ETH_CMD_EQID_GET(ntohl(c.eqid_pkd)));
	txq->txq = netdevq;
	txq->tso = txq->tx_cso = txq->vlan_ins = 0;
	txq->mapping_err = 0;
	return 0;
}