#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfa_s {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  qe; } ;
struct TYPE_5__ {int /*<<< orphan*/  qe; } ;
struct bfa_meminfo_s {TYPE_2__ kva_info; TYPE_1__ dma_info; } ;
struct bfa_mem_dma_s {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  min_cfg; } ;
struct bfa_iocfc_cfg_s {TYPE_3__ drvcfg; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* meminfo ) (struct bfa_iocfc_cfg_s*,struct bfa_meminfo_s*,struct bfa_s*) ;} ;

/* Variables and functions */
 struct bfa_mem_dma_s* BFA_MEM_ABLK_DMA (struct bfa_s*) ; 
 struct bfa_mem_dma_s* BFA_MEM_CEE_DMA (struct bfa_s*) ; 
 struct bfa_mem_dma_s* BFA_MEM_DIAG_DMA (struct bfa_s*) ; 
 struct bfa_mem_dma_s* BFA_MEM_FLASH_DMA (struct bfa_s*) ; 
 struct bfa_mem_dma_s* BFA_MEM_FRU_DMA (struct bfa_s*) ; 
 struct bfa_mem_dma_s* BFA_MEM_PHY_DMA (struct bfa_s*) ; 
 struct bfa_mem_dma_s* BFA_MEM_PORT_DMA (struct bfa_s*) ; 
 struct bfa_mem_dma_s* BFA_MEM_SFP_DMA (struct bfa_s*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_ablk_meminfo () ; 
 int /*<<< orphan*/  bfa_cee_meminfo () ; 
 int /*<<< orphan*/  bfa_diag_meminfo () ; 
 int /*<<< orphan*/  bfa_flash_meminfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fru_meminfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_iocfc_meminfo (struct bfa_iocfc_cfg_s*,struct bfa_meminfo_s*,struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_mem_dma_setup (struct bfa_meminfo_s*,struct bfa_mem_dma_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_phy_meminfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_port_meminfo () ; 
 int /*<<< orphan*/  bfa_sfp_meminfo () ; 
 TYPE_4__** hal_mods ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct bfa_iocfc_cfg_s*,struct bfa_meminfo_s*,struct bfa_s*) ; 

void
bfa_cfg_get_meminfo(struct bfa_iocfc_cfg_s *cfg, struct bfa_meminfo_s *meminfo,
		struct bfa_s *bfa)
{
	int		i;
	struct bfa_mem_dma_s *port_dma = BFA_MEM_PORT_DMA(bfa);
	struct bfa_mem_dma_s *ablk_dma = BFA_MEM_ABLK_DMA(bfa);
	struct bfa_mem_dma_s *cee_dma = BFA_MEM_CEE_DMA(bfa);
	struct bfa_mem_dma_s *sfp_dma = BFA_MEM_SFP_DMA(bfa);
	struct bfa_mem_dma_s *flash_dma = BFA_MEM_FLASH_DMA(bfa);
	struct bfa_mem_dma_s *diag_dma = BFA_MEM_DIAG_DMA(bfa);
	struct bfa_mem_dma_s *phy_dma = BFA_MEM_PHY_DMA(bfa);
	struct bfa_mem_dma_s *fru_dma = BFA_MEM_FRU_DMA(bfa);

	WARN_ON((cfg == NULL) || (meminfo == NULL));

	memset((void *)meminfo, 0, sizeof(struct bfa_meminfo_s));

	/* Initialize the DMA & KVA meminfo queues */
	INIT_LIST_HEAD(&meminfo->dma_info.qe);
	INIT_LIST_HEAD(&meminfo->kva_info.qe);

	bfa_iocfc_meminfo(cfg, meminfo, bfa);

	for (i = 0; hal_mods[i]; i++)
		hal_mods[i]->meminfo(cfg, meminfo, bfa);

	/* dma info setup */
	bfa_mem_dma_setup(meminfo, port_dma, bfa_port_meminfo());
	bfa_mem_dma_setup(meminfo, ablk_dma, bfa_ablk_meminfo());
	bfa_mem_dma_setup(meminfo, cee_dma, bfa_cee_meminfo());
	bfa_mem_dma_setup(meminfo, sfp_dma, bfa_sfp_meminfo());
	bfa_mem_dma_setup(meminfo, flash_dma,
			  bfa_flash_meminfo(cfg->drvcfg.min_cfg));
	bfa_mem_dma_setup(meminfo, diag_dma, bfa_diag_meminfo());
	bfa_mem_dma_setup(meminfo, phy_dma,
			  bfa_phy_meminfo(cfg->drvcfg.min_cfg));
	bfa_mem_dma_setup(meminfo, fru_dma,
			  bfa_fru_meminfo(cfg->drvcfg.min_cfg));
}