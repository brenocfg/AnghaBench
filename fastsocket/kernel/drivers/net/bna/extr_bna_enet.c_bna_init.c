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
struct bnad {int dummy; } ;
struct TYPE_11__ {TYPE_4__* mdl; } ;
struct TYPE_12__ {TYPE_5__ mem_info; } ;
struct bna_res_info {TYPE_6__ res_u; } ;
struct bfa_pcidev {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  lsb; int /*<<< orphan*/  msb; } ;
struct TYPE_8__ {TYPE_1__ hw_stats_dma; struct bfi_enet_stats* hw_stats_kva; } ;
struct bna {int /*<<< orphan*/  ethport; int /*<<< orphan*/  enet; int /*<<< orphan*/  ioceth; struct bfa_pcidev pcidev; TYPE_2__ stats; struct bnad* bnad; } ;
struct bfi_enet_stats {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  lsb; int /*<<< orphan*/  msb; } ;
struct TYPE_10__ {TYPE_3__ dma; scalar_t__ kva; } ;

/* Variables and functions */
 size_t BNA_RES_MEM_T_STATS ; 
 int /*<<< orphan*/  bna_enet_init (int /*<<< orphan*/ *,struct bna*) ; 
 int /*<<< orphan*/  bna_ethport_init (int /*<<< orphan*/ *,struct bna*) ; 
 int /*<<< orphan*/  bna_ioceth_init (int /*<<< orphan*/ *,struct bna*,struct bna_res_info*) ; 
 int /*<<< orphan*/  bna_reg_addr_init (struct bna*,struct bfa_pcidev*) ; 

void
bna_init(struct bna *bna, struct bnad *bnad,
		struct bfa_pcidev *pcidev, struct bna_res_info *res_info)
{
	bna->bnad = bnad;
	bna->pcidev = *pcidev;

	bna->stats.hw_stats_kva = (struct bfi_enet_stats *)
		res_info[BNA_RES_MEM_T_STATS].res_u.mem_info.mdl[0].kva;
	bna->stats.hw_stats_dma.msb =
		res_info[BNA_RES_MEM_T_STATS].res_u.mem_info.mdl[0].dma.msb;
	bna->stats.hw_stats_dma.lsb =
		res_info[BNA_RES_MEM_T_STATS].res_u.mem_info.mdl[0].dma.lsb;

	bna_reg_addr_init(bna, &bna->pcidev);

	/* Also initializes diag, cee, sfp, phy_port, msgq */
	bna_ioceth_init(&bna->ioceth, bna, res_info);

	bna_enet_init(&bna->enet, bna);
	bna_ethport_init(&bna->ethport, bna);
}