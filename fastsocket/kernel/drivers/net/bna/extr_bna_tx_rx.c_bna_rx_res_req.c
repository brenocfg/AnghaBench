#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bna_rx_config {int q_depth; scalar_t__ rxp_type; int num_paths; } ;
struct TYPE_3__ {int num; int /*<<< orphan*/  intr_type; } ;
struct bna_mem_info {int len; int num; void* mem_type; } ;
struct TYPE_4__ {TYPE_1__ intr_info; struct bna_mem_info mem_info; } ;
struct bna_res_info {TYPE_2__ res_u; void* res_type; } ;
struct bna_rcb {int dummy; } ;
struct bna_dma_addr {int dummy; } ;
struct bna_ccb {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int BFI_CQ_WI_SIZE ; 
 int BFI_ENET_RSS_RIT_MAX ; 
 int BFI_IBIDX_SIZE ; 
 int BFI_RXQ_WI_SIZE ; 
 int BNA_GET_RXQS (struct bna_rx_config*) ; 
 int /*<<< orphan*/  BNA_INTR_T_MSIX ; 
 void* BNA_MEM_T_DMA ; 
 void* BNA_MEM_T_KVA ; 
 void* BNA_RES_T_INTR ; 
 void* BNA_RES_T_MEM ; 
 scalar_t__ BNA_RXP_SINGLE ; 
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
 size_t BNA_RX_RES_MEM_T_RIT ; 
 size_t BNA_RX_RES_T_INTR ; 
 int /*<<< orphan*/  BNA_TO_POWER_OF_2_HIGH (int) ; 
 int PAGE_SIZE ; 
 int SIZE_TO_PAGES (int) ; 

void
bna_rx_res_req(struct bna_rx_config *q_cfg, struct bna_res_info *res_info)
{
	u32 cq_size, hq_size, dq_size;
	u32 cpage_count, hpage_count, dpage_count;
	struct bna_mem_info *mem_info;
	u32 cq_depth;
	u32 hq_depth;
	u32 dq_depth;

	dq_depth = q_cfg->q_depth;
	hq_depth = ((q_cfg->rxp_type == BNA_RXP_SINGLE) ? 0 : q_cfg->q_depth);
	cq_depth = dq_depth + hq_depth;

	BNA_TO_POWER_OF_2_HIGH(cq_depth);
	cq_size = cq_depth * BFI_CQ_WI_SIZE;
	cq_size = ALIGN(cq_size, PAGE_SIZE);
	cpage_count = SIZE_TO_PAGES(cq_size);

	BNA_TO_POWER_OF_2_HIGH(dq_depth);
	dq_size = dq_depth * BFI_RXQ_WI_SIZE;
	dq_size = ALIGN(dq_size, PAGE_SIZE);
	dpage_count = SIZE_TO_PAGES(dq_size);

	if (BNA_RXP_SINGLE != q_cfg->rxp_type) {
		BNA_TO_POWER_OF_2_HIGH(hq_depth);
		hq_size = hq_depth * BFI_RXQ_WI_SIZE;
		hq_size = ALIGN(hq_size, PAGE_SIZE);
		hpage_count = SIZE_TO_PAGES(hq_size);
	} else
		hpage_count = 0;

	res_info[BNA_RX_RES_MEM_T_CCB].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_CCB].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = sizeof(struct bna_ccb);
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_RCB].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_RCB].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = sizeof(struct bna_rcb);
	mem_info->num = BNA_GET_RXQS(q_cfg);

	res_info[BNA_RX_RES_MEM_T_CQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_CQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = cpage_count * sizeof(struct bna_dma_addr);
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_CSWQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_CSWQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = cpage_count * sizeof(void *);
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_CQPT_PAGE].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_CQPT_PAGE].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = PAGE_SIZE * cpage_count;
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_DQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_DQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = dpage_count * sizeof(struct bna_dma_addr);
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_DSWQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_DSWQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = dpage_count * sizeof(void *);
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_DPAGE].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_DPAGE].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = PAGE_SIZE * dpage_count;
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_HQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_HQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = hpage_count * sizeof(struct bna_dma_addr);
	mem_info->num = (hpage_count ? q_cfg->num_paths : 0);

	res_info[BNA_RX_RES_MEM_T_HSWQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_HSWQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = hpage_count * sizeof(void *);
	mem_info->num = (hpage_count ? q_cfg->num_paths : 0);

	res_info[BNA_RX_RES_MEM_T_HPAGE].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_HPAGE].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = PAGE_SIZE * hpage_count;
	mem_info->num = (hpage_count ? q_cfg->num_paths : 0);

	res_info[BNA_RX_RES_MEM_T_IBIDX].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_IBIDX].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = BFI_IBIDX_SIZE;
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_RIT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_RIT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = BFI_ENET_RSS_RIT_MAX;
	mem_info->num = 1;

	res_info[BNA_RX_RES_T_INTR].res_type = BNA_RES_T_INTR;
	res_info[BNA_RX_RES_T_INTR].res_u.intr_info.intr_type = BNA_INTR_T_MSIX;
	res_info[BNA_RX_RES_T_INTR].res_u.intr_info.num = q_cfg->num_paths;
}