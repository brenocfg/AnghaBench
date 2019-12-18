#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bnad {int dummy; } ;
struct bna_rxq {struct bna_rcb* rcb; scalar_t__ rxbuf_alloc_failed; scalar_t__ rx_packets_with_error; scalar_t__ rx_bytes; scalar_t__ rx_packets; int /*<<< orphan*/  buffer_size; struct bna_rxp* rxp; struct bna_rx* rx; } ;
struct TYPE_11__ {int /*<<< orphan*/  msb; int /*<<< orphan*/  lsb; } ;
struct TYPE_15__ {scalar_t__ intr_type; int intr_vector; int /*<<< orphan*/  coalescing_timeo; int /*<<< orphan*/  door_bell; scalar_t__ ib_seg_host_addr_kva; int /*<<< orphan*/  interpkt_timeo; int /*<<< orphan*/  interpkt_count; TYPE_2__ ib_seg_host_addr; } ;
struct TYPE_17__ {struct bna_ccb* ccb; TYPE_6__ ib; struct bna_rx* rx; } ;
struct bna_rxp {scalar_t__ type; int vector; TYPE_8__ cq; struct bna_rx* rx; int /*<<< orphan*/  qe; } ;
struct bna_rx_mod {int flags; int rid_mask; } ;
struct bna_rx_event_cbfn {int /*<<< orphan*/  rx_post_cbfn; int /*<<< orphan*/  rx_cleanup_cbfn; int /*<<< orphan*/  rx_stall_cbfn; int /*<<< orphan*/  ccb_destroy_cbfn; int /*<<< orphan*/  (* ccb_setup_cbfn ) (struct bnad*,struct bna_ccb*) ;int /*<<< orphan*/  rcb_destroy_cbfn; int /*<<< orphan*/  (* rcb_setup_cbfn ) (struct bnad*,struct bna_rcb*) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  forced_offset; } ;
struct bna_rx_config {int num_paths; scalar_t__ rxp_type; TYPE_9__ hds_config; scalar_t__ q_depth; int /*<<< orphan*/  small_buff_size; int /*<<< orphan*/  coalescing_timeo; int /*<<< orphan*/  rx_type; } ;
struct bna_rx {int type; int num_paths; int rid; int /*<<< orphan*/  rxf; TYPE_9__ hds_cfg; int /*<<< orphan*/  (* ccb_setup_cbfn ) (struct bnad*,struct bna_ccb*) ;int /*<<< orphan*/  (* rcb_setup_cbfn ) (struct bnad*,struct bna_rcb*) ;int /*<<< orphan*/  rxp_q; scalar_t__ rx_flags; struct bna* bna; int /*<<< orphan*/  rx_post_cbfn; int /*<<< orphan*/  rx_cleanup_cbfn; int /*<<< orphan*/  rx_stall_cbfn; int /*<<< orphan*/  ccb_destroy_cbfn; int /*<<< orphan*/  rcb_destroy_cbfn; void* priv; int /*<<< orphan*/ * stop_cbarg; int /*<<< orphan*/ * stop_cbfn; } ;
struct TYPE_13__ {int len; struct bna_mem_descr* mdl; } ;
struct bna_intr_info {int num; scalar_t__ intr_type; TYPE_1__* idl; } ;
struct TYPE_14__ {TYPE_4__ mem_info; struct bna_intr_info intr_info; } ;
struct bna_res_info {TYPE_5__ res_u; } ;
struct bna_rcb {int id; struct bna_ccb* ccb; int /*<<< orphan*/  bnad; struct bna_rxq* rxq; scalar_t__ q_depth; void* unmap_q; } ;
struct TYPE_12__ {int /*<<< orphan*/  msb; int /*<<< orphan*/  lsb; } ;
struct bna_mem_descr {scalar_t__ kva; TYPE_3__ dma; } ;
struct TYPE_16__ {scalar_t__ large_pkt_cnt; scalar_t__ small_pkt_cnt; } ;
struct bna_ccb {int* hw_producer_index; scalar_t__ intr_type; int intr_vector; int id; int /*<<< orphan*/  bnad; TYPE_7__ pkt_rate; int /*<<< orphan*/  rx_coalescing_timeo; int /*<<< orphan*/ * i_dbell; struct bna_rcb** rcb; TYPE_8__* cq; scalar_t__ q_depth; } ;
struct bna {int /*<<< orphan*/  bnad; struct bna_rx_mod rx_mod; } ;
struct TYPE_10__ {int vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_RX_INTERPKT_COUNT ; 
 int /*<<< orphan*/  BFI_RX_INTERPKT_TIMEO ; 
 scalar_t__ BNA_INTR_T_MSIX ; 
 scalar_t__ BNA_RXP_HDS ; 
 scalar_t__ BNA_RXP_SINGLE ; 
 scalar_t__ BNA_RX_F_ENET_STARTED ; 
 int BNA_RX_MOD_F_ENET_LOOPBACK ; 
 int BNA_RX_MOD_F_ENET_STARTED ; 
 size_t BNA_RX_RES_MEM_T_CCB ; 
 size_t BNA_RX_RES_MEM_T_CQPT ; 
 size_t BNA_RX_RES_MEM_T_CQPT_PAGE ; 
 size_t BNA_RX_RES_MEM_T_CSWQPT ; 
 size_t BNA_RX_RES_MEM_T_DPAGE ; 
 size_t BNA_RX_RES_MEM_T_DQPT ; 
 size_t BNA_RX_RES_MEM_T_DSWQPT ; 
 size_t BNA_RX_RES_MEM_T_HPAGE ; 
 size_t BNA_RX_RES_MEM_T_HQPT ; 
 size_t BNA_RX_RES_MEM_T_HSWQPT ; 
 size_t BNA_RX_RES_MEM_T_IBIDX ; 
 size_t BNA_RX_RES_MEM_T_RCB ; 
 size_t BNA_RX_RES_MEM_T_UNMAPQ ; 
 size_t BNA_RX_RES_T_INTR ; 
#define  BNA_RX_T_LOOPBACK 129 
#define  BNA_RX_T_REGULAR 128 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_rx*,int /*<<< orphan*/ ) ; 
 struct bna_rx* bna_rx_get (struct bna_rx_mod*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_rx_res_check (struct bna_rx_mod*,struct bna_rx_config*) ; 
 int /*<<< orphan*/  bna_rx_sm_stopped ; 
 int /*<<< orphan*/  bna_rxf_init (int /*<<< orphan*/ *,struct bna_rx*,struct bna_rx_config*,struct bna_res_info*) ; 
 int /*<<< orphan*/  bna_rxp_add_rxqs (struct bna_rxp*,struct bna_rxq*,struct bna_rxq*) ; 
 int /*<<< orphan*/  bna_rxp_cqpt_setup (struct bna_rxp*,int,int,struct bna_mem_descr*,struct bna_mem_descr*,struct bna_mem_descr*) ; 
 struct bna_rxp* bna_rxp_get (struct bna_rx_mod*) ; 
 struct bna_rxq* bna_rxq_get (struct bna_rx_mod*) ; 
 int /*<<< orphan*/  bna_rxq_qpt_setup (struct bna_rxq*,struct bna_rxp*,int,int,struct bna_mem_descr*,struct bna_mem_descr*,struct bna_mem_descr*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bnad*,struct bna_rcb*) ; 
 int /*<<< orphan*/  stub2 (struct bnad*,struct bna_rcb*) ; 
 int /*<<< orphan*/  stub3 (struct bnad*,struct bna_ccb*) ; 

struct bna_rx *
bna_rx_create(struct bna *bna, struct bnad *bnad,
		struct bna_rx_config *rx_cfg,
		const struct bna_rx_event_cbfn *rx_cbfn,
		struct bna_res_info *res_info,
		void *priv)
{
	struct bna_rx_mod *rx_mod = &bna->rx_mod;
	struct bna_rx *rx;
	struct bna_rxp *rxp;
	struct bna_rxq *q0;
	struct bna_rxq *q1;
	struct bna_intr_info *intr_info;
	u32 page_count;
	struct bna_mem_descr *ccb_mem;
	struct bna_mem_descr *rcb_mem;
	struct bna_mem_descr *unmapq_mem;
	struct bna_mem_descr *cqpt_mem;
	struct bna_mem_descr *cswqpt_mem;
	struct bna_mem_descr *cpage_mem;
	struct bna_mem_descr *hqpt_mem;
	struct bna_mem_descr *dqpt_mem;
	struct bna_mem_descr *hsqpt_mem;
	struct bna_mem_descr *dsqpt_mem;
	struct bna_mem_descr *hpage_mem;
	struct bna_mem_descr *dpage_mem;
	int i;
	int dpage_count, hpage_count, rcb_idx;

	if (!bna_rx_res_check(rx_mod, rx_cfg))
		return NULL;

	intr_info = &res_info[BNA_RX_RES_T_INTR].res_u.intr_info;
	ccb_mem = &res_info[BNA_RX_RES_MEM_T_CCB].res_u.mem_info.mdl[0];
	rcb_mem = &res_info[BNA_RX_RES_MEM_T_RCB].res_u.mem_info.mdl[0];
	unmapq_mem = &res_info[BNA_RX_RES_MEM_T_UNMAPQ].res_u.mem_info.mdl[0];
	cqpt_mem = &res_info[BNA_RX_RES_MEM_T_CQPT].res_u.mem_info.mdl[0];
	cswqpt_mem = &res_info[BNA_RX_RES_MEM_T_CSWQPT].res_u.mem_info.mdl[0];
	cpage_mem = &res_info[BNA_RX_RES_MEM_T_CQPT_PAGE].res_u.mem_info.mdl[0];
	hqpt_mem = &res_info[BNA_RX_RES_MEM_T_HQPT].res_u.mem_info.mdl[0];
	dqpt_mem = &res_info[BNA_RX_RES_MEM_T_DQPT].res_u.mem_info.mdl[0];
	hsqpt_mem = &res_info[BNA_RX_RES_MEM_T_HSWQPT].res_u.mem_info.mdl[0];
	dsqpt_mem = &res_info[BNA_RX_RES_MEM_T_DSWQPT].res_u.mem_info.mdl[0];
	hpage_mem = &res_info[BNA_RX_RES_MEM_T_HPAGE].res_u.mem_info.mdl[0];
	dpage_mem = &res_info[BNA_RX_RES_MEM_T_DPAGE].res_u.mem_info.mdl[0];

	page_count = res_info[BNA_RX_RES_MEM_T_CQPT_PAGE].res_u.mem_info.len /
			PAGE_SIZE;

	dpage_count = res_info[BNA_RX_RES_MEM_T_DPAGE].res_u.mem_info.len /
			PAGE_SIZE;

	hpage_count = res_info[BNA_RX_RES_MEM_T_HPAGE].res_u.mem_info.len /
			PAGE_SIZE;

	rx = bna_rx_get(rx_mod, rx_cfg->rx_type);
	rx->bna = bna;
	rx->rx_flags = 0;
	INIT_LIST_HEAD(&rx->rxp_q);
	rx->stop_cbfn = NULL;
	rx->stop_cbarg = NULL;
	rx->priv = priv;

	rx->rcb_setup_cbfn = rx_cbfn->rcb_setup_cbfn;
	rx->rcb_destroy_cbfn = rx_cbfn->rcb_destroy_cbfn;
	rx->ccb_setup_cbfn = rx_cbfn->ccb_setup_cbfn;
	rx->ccb_destroy_cbfn = rx_cbfn->ccb_destroy_cbfn;
	rx->rx_stall_cbfn = rx_cbfn->rx_stall_cbfn;
	/* Following callbacks are mandatory */
	rx->rx_cleanup_cbfn = rx_cbfn->rx_cleanup_cbfn;
	rx->rx_post_cbfn = rx_cbfn->rx_post_cbfn;

	if (rx->bna->rx_mod.flags & BNA_RX_MOD_F_ENET_STARTED) {
		switch (rx->type) {
		case BNA_RX_T_REGULAR:
			if (!(rx->bna->rx_mod.flags &
				BNA_RX_MOD_F_ENET_LOOPBACK))
				rx->rx_flags |= BNA_RX_F_ENET_STARTED;
			break;
		case BNA_RX_T_LOOPBACK:
			if (rx->bna->rx_mod.flags & BNA_RX_MOD_F_ENET_LOOPBACK)
				rx->rx_flags |= BNA_RX_F_ENET_STARTED;
			break;
		}
	}

	rx->num_paths = rx_cfg->num_paths;
	for (i = 0, rcb_idx = 0; i < rx->num_paths; i++) {
		rxp = bna_rxp_get(rx_mod);
		list_add_tail(&rxp->qe, &rx->rxp_q);
		rxp->type = rx_cfg->rxp_type;
		rxp->rx = rx;
		rxp->cq.rx = rx;

		q0 = bna_rxq_get(rx_mod);
		if (BNA_RXP_SINGLE == rx_cfg->rxp_type)
			q1 = NULL;
		else
			q1 = bna_rxq_get(rx_mod);

		if (1 == intr_info->num)
			rxp->vector = intr_info->idl[0].vector;
		else
			rxp->vector = intr_info->idl[i].vector;

		/* Setup IB */

		rxp->cq.ib.ib_seg_host_addr.lsb =
		res_info[BNA_RX_RES_MEM_T_IBIDX].res_u.mem_info.mdl[i].dma.lsb;
		rxp->cq.ib.ib_seg_host_addr.msb =
		res_info[BNA_RX_RES_MEM_T_IBIDX].res_u.mem_info.mdl[i].dma.msb;
		rxp->cq.ib.ib_seg_host_addr_kva =
		res_info[BNA_RX_RES_MEM_T_IBIDX].res_u.mem_info.mdl[i].kva;
		rxp->cq.ib.intr_type = intr_info->intr_type;
		if (intr_info->intr_type == BNA_INTR_T_MSIX)
			rxp->cq.ib.intr_vector = rxp->vector;
		else
			rxp->cq.ib.intr_vector = (1 << rxp->vector);
		rxp->cq.ib.coalescing_timeo = rx_cfg->coalescing_timeo;
		rxp->cq.ib.interpkt_count = BFI_RX_INTERPKT_COUNT;
		rxp->cq.ib.interpkt_timeo = BFI_RX_INTERPKT_TIMEO;

		bna_rxp_add_rxqs(rxp, q0, q1);

		/* Setup large Q */

		q0->rx = rx;
		q0->rxp = rxp;

		q0->rcb = (struct bna_rcb *) rcb_mem[rcb_idx].kva;
		q0->rcb->unmap_q = (void *)unmapq_mem[rcb_idx].kva;
		rcb_idx++;
		q0->rcb->q_depth = rx_cfg->q_depth;
		q0->rcb->rxq = q0;
		q0->rcb->bnad = bna->bnad;
		q0->rcb->id = 0;
		q0->rx_packets = q0->rx_bytes = 0;
		q0->rx_packets_with_error = q0->rxbuf_alloc_failed = 0;

		bna_rxq_qpt_setup(q0, rxp, dpage_count, PAGE_SIZE,
			&dqpt_mem[i], &dsqpt_mem[i], &dpage_mem[i]);

		if (rx->rcb_setup_cbfn)
			rx->rcb_setup_cbfn(bnad, q0->rcb);

		/* Setup small Q */

		if (q1) {
			q1->rx = rx;
			q1->rxp = rxp;

			q1->rcb = (struct bna_rcb *) rcb_mem[rcb_idx].kva;
			q1->rcb->unmap_q = (void *)unmapq_mem[rcb_idx].kva;
			rcb_idx++;
			q1->rcb->q_depth = rx_cfg->q_depth;
			q1->rcb->rxq = q1;
			q1->rcb->bnad = bna->bnad;
			q1->rcb->id = 1;
			q1->buffer_size = (rx_cfg->rxp_type == BNA_RXP_HDS) ?
					rx_cfg->hds_config.forced_offset
					: rx_cfg->small_buff_size;
			q1->rx_packets = q1->rx_bytes = 0;
			q1->rx_packets_with_error = q1->rxbuf_alloc_failed = 0;

			bna_rxq_qpt_setup(q1, rxp, hpage_count, PAGE_SIZE,
				&hqpt_mem[i], &hsqpt_mem[i],
				&hpage_mem[i]);

			if (rx->rcb_setup_cbfn)
				rx->rcb_setup_cbfn(bnad, q1->rcb);
		}

		/* Setup CQ */

		rxp->cq.ccb = (struct bna_ccb *) ccb_mem[i].kva;
		rxp->cq.ccb->q_depth =	rx_cfg->q_depth +
					((rx_cfg->rxp_type == BNA_RXP_SINGLE) ?
					0 : rx_cfg->q_depth);
		rxp->cq.ccb->cq = &rxp->cq;
		rxp->cq.ccb->rcb[0] = q0->rcb;
		q0->rcb->ccb = rxp->cq.ccb;
		if (q1) {
			rxp->cq.ccb->rcb[1] = q1->rcb;
			q1->rcb->ccb = rxp->cq.ccb;
		}
		rxp->cq.ccb->hw_producer_index =
			(u32 *)rxp->cq.ib.ib_seg_host_addr_kva;
		rxp->cq.ccb->i_dbell = &rxp->cq.ib.door_bell;
		rxp->cq.ccb->intr_type = rxp->cq.ib.intr_type;
		rxp->cq.ccb->intr_vector = rxp->cq.ib.intr_vector;
		rxp->cq.ccb->rx_coalescing_timeo =
			rxp->cq.ib.coalescing_timeo;
		rxp->cq.ccb->pkt_rate.small_pkt_cnt = 0;
		rxp->cq.ccb->pkt_rate.large_pkt_cnt = 0;
		rxp->cq.ccb->bnad = bna->bnad;
		rxp->cq.ccb->id = i;

		bna_rxp_cqpt_setup(rxp, page_count, PAGE_SIZE,
			&cqpt_mem[i], &cswqpt_mem[i], &cpage_mem[i]);

		if (rx->ccb_setup_cbfn)
			rx->ccb_setup_cbfn(bnad, rxp->cq.ccb);
	}

	rx->hds_cfg = rx_cfg->hds_config;

	bna_rxf_init(&rx->rxf, rx, rx_cfg, res_info);

	bfa_fsm_set_state(rx, bna_rx_sm_stopped);

	rx_mod->rid_mask |= (1 << rx->rid);

	return rx;
}