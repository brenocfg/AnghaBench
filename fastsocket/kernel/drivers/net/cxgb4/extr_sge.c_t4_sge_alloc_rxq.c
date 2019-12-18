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
struct tx_desc {int dummy; } ;
struct sge_rspq {int size; int iqe_len; int gen; size_t cntxt_id; int offset; int /*<<< orphan*/ * desc; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  handler; struct net_device* netdev; struct adapter* adap; void* abs_id; int /*<<< orphan*/  intr_params; int /*<<< orphan*/  next_intr_params; scalar_t__ cidx; int /*<<< orphan*/ * cur_desc; int /*<<< orphan*/  napi; int /*<<< orphan*/  pktcnt_idx; } ;
struct sge_fl {int size; size_t cntxt_id; int /*<<< orphan*/ * desc; int /*<<< orphan*/  addr; int /*<<< orphan*/ * sdesc; scalar_t__ starving; scalar_t__ large_alloc_failed; scalar_t__ alloc_failed; scalar_t__ cidx; scalar_t__ pidx; scalar_t__ pend_cred; scalar_t__ avail; } ;
struct rx_sw_desc {int dummy; } ;
struct port_info {int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  viid; } ;
struct net_device {int dummy; } ;
struct fw_iq_cmd {int /*<<< orphan*/  fl0id; int /*<<< orphan*/  physiqid; int /*<<< orphan*/  iqid; void* fl0addr; void* fl0size; void* fl0dcaen_to_fl0cidxfthresh; void* iqns_to_fl0congen; void* iqaddr; void* iqsize; void* iqdroprss_to_iqesize; void* type_to_iqandstindex; void* alloc_to_len16; void* op_to_vfn; } ;
struct TYPE_2__ {size_t ingr_start; size_t egr_start; struct sge_fl** egr_map; struct sge_rspq** ingr_map; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; TYPE_1__ sge; int /*<<< orphan*/  fn; } ;
typedef  int /*<<< orphan*/  rspq_handler_t ;
typedef  int /*<<< orphan*/  c ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int ENOMEM ; 
 int FW_CMD_EXEC ; 
 int FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST ; 
 int FW_CMD_WRITE ; 
 int /*<<< orphan*/  FW_IQ_CMD ; 
 int FW_IQ_CMD_ALLOC ; 
 int FW_IQ_CMD_FL0DATARO (int) ; 
 int FW_IQ_CMD_FL0FBMAX (int) ; 
 int FW_IQ_CMD_FL0FBMIN (int) ; 
 int FW_IQ_CMD_FL0FETCHRO (int) ; 
 int FW_IQ_CMD_FL0PACKEN ; 
 int FW_IQ_CMD_FL0PADEN ; 
 int FW_IQ_CMD_IQANDST (int) ; 
 int FW_IQ_CMD_IQANDSTINDEX (int) ; 
 int FW_IQ_CMD_IQANUD (int) ; 
 int FW_IQ_CMD_IQASYNCH (int) ; 
 int FW_IQ_CMD_IQESIZE (scalar_t__) ; 
 int FW_IQ_CMD_IQGTSMODE ; 
 int FW_IQ_CMD_IQINTCNTTHRESH (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQPCIECH (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQSTART (int) ; 
 int FW_IQ_CMD_PFN (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_TYPE (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_VFN (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_VIID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_IQ_TYPE_FL_INT_CAP ; 
 int FW_LEN16 (struct fw_iq_cmd) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int STAT_LEN ; 
 void* alloc_ring (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fl_cap (struct sge_fl*) ; 
 void* htonl (int) ; 
 void* htons (int) ; 
 scalar_t__ ilog2 (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fw_iq_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_rx_handler ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refill_fl (struct adapter*,struct sge_fl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* roundup (int,int) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_iq_cmd*,int,struct fw_iq_cmd*) ; 

int t4_sge_alloc_rxq(struct adapter *adap, struct sge_rspq *iq, bool fwevtq,
		     struct net_device *dev, int intr_idx,
		     struct sge_fl *fl, rspq_handler_t hnd)
{
	int ret, flsz = 0;
	struct fw_iq_cmd c;
	struct port_info *pi = netdev_priv(dev);

	/* Size needs to be multiple of 16, including status entry. */
	iq->size = roundup(iq->size, 16);

	iq->desc = alloc_ring(adap->pdev_dev, iq->size, iq->iqe_len, 0,
			      &iq->phys_addr, NULL, 0);
	if (!iq->desc)
		return -ENOMEM;

	memset(&c, 0, sizeof(c));
	c.op_to_vfn = htonl(FW_CMD_OP(FW_IQ_CMD) | FW_CMD_REQUEST |
			    FW_CMD_WRITE | FW_CMD_EXEC |
			    FW_IQ_CMD_PFN(adap->fn) | FW_IQ_CMD_VFN(0));
	c.alloc_to_len16 = htonl(FW_IQ_CMD_ALLOC | FW_IQ_CMD_IQSTART(1) |
				 FW_LEN16(c));
	c.type_to_iqandstindex = htonl(FW_IQ_CMD_TYPE(FW_IQ_TYPE_FL_INT_CAP) |
		FW_IQ_CMD_IQASYNCH(fwevtq) | FW_IQ_CMD_VIID(pi->viid) |
		FW_IQ_CMD_IQANDST(intr_idx < 0) | FW_IQ_CMD_IQANUD(1) |
		FW_IQ_CMD_IQANDSTINDEX(intr_idx >= 0 ? intr_idx :
							-intr_idx - 1));
	c.iqdroprss_to_iqesize = htons(FW_IQ_CMD_IQPCIECH(pi->tx_chan) |
		FW_IQ_CMD_IQGTSMODE |
		FW_IQ_CMD_IQINTCNTTHRESH(iq->pktcnt_idx) |
		FW_IQ_CMD_IQESIZE(ilog2(iq->iqe_len) - 4));
	c.iqsize = htons(iq->size);
	c.iqaddr = cpu_to_be64(iq->phys_addr);

	if (fl) {
		fl->size = roundup(fl->size, 8);
		fl->desc = alloc_ring(adap->pdev_dev, fl->size, sizeof(__be64),
				      sizeof(struct rx_sw_desc), &fl->addr,
				      &fl->sdesc, STAT_LEN);
		if (!fl->desc)
			goto fl_nomem;

		flsz = fl->size / 8 + STAT_LEN / sizeof(struct tx_desc);
		c.iqns_to_fl0congen = htonl(FW_IQ_CMD_FL0PACKEN |
					    FW_IQ_CMD_FL0FETCHRO(1) |
					    FW_IQ_CMD_FL0DATARO(1) |
					    FW_IQ_CMD_FL0PADEN);
		c.fl0dcaen_to_fl0cidxfthresh = htons(FW_IQ_CMD_FL0FBMIN(2) |
				FW_IQ_CMD_FL0FBMAX(3));
		c.fl0size = htons(flsz);
		c.fl0addr = cpu_to_be64(fl->addr);
	}

	ret = t4_wr_mbox(adap, adap->fn, &c, sizeof(c), &c);
	if (ret)
		goto err;

	netif_napi_add(dev, &iq->napi, napi_rx_handler, 64);
	iq->cur_desc = iq->desc;
	iq->cidx = 0;
	iq->gen = 1;
	iq->next_intr_params = iq->intr_params;
	iq->cntxt_id = ntohs(c.iqid);
	iq->abs_id = ntohs(c.physiqid);
	iq->size--;                           /* subtract status entry */
	iq->adap = adap;
	iq->netdev = dev;
	iq->handler = hnd;

	/* set offset to -1 to distinguish ingress queues without FL */
	iq->offset = fl ? 0 : -1;

	adap->sge.ingr_map[iq->cntxt_id - adap->sge.ingr_start] = iq;

	if (fl) {
		fl->cntxt_id = ntohs(c.fl0id);
		fl->avail = fl->pend_cred = 0;
		fl->pidx = fl->cidx = 0;
		fl->alloc_failed = fl->large_alloc_failed = fl->starving = 0;
		adap->sge.egr_map[fl->cntxt_id - adap->sge.egr_start] = fl;
		refill_fl(adap, fl, fl_cap(fl), GFP_KERNEL);
	}
	return 0;

fl_nomem:
	ret = -ENOMEM;
err:
	if (iq->desc) {
		dma_free_coherent(adap->pdev_dev, iq->size * iq->iqe_len,
				  iq->desc, iq->phys_addr);
		iq->desc = NULL;
	}
	if (fl && fl->desc) {
		kfree(fl->sdesc);
		fl->sdesc = NULL;
		dma_free_coherent(adap->pdev_dev, flsz * sizeof(struct tx_desc),
				  fl->desc, fl->addr);
		fl->desc = NULL;
	}
	return ret;
}