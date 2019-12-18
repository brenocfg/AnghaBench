#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bna_txq {int /*<<< orphan*/  qe; } ;
struct bna_tx_mod {int iscsi_prio; int /*<<< orphan*/  iscsi_over_cee; scalar_t__ default_prio; int /*<<< orphan*/  prio_map; int /*<<< orphan*/  txq_free_q; struct bna_txq* txq; int /*<<< orphan*/  tx_free_q; struct bna_tx* tx; int /*<<< orphan*/  tx_active_q; scalar_t__ flags; struct bna* bna; } ;
struct bna_tx {int rid; int /*<<< orphan*/  qe; } ;
struct TYPE_7__ {TYPE_1__* mdl; } ;
struct TYPE_8__ {TYPE_2__ mem_info; } ;
struct bna_res_info {TYPE_3__ res_u; } ;
struct TYPE_9__ {int num_txq; } ;
struct TYPE_10__ {TYPE_4__ attr; } ;
struct bna {TYPE_5__ ioceth; } ;
struct TYPE_6__ {scalar_t__ kva; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_TX_PRIO_MAP_ALL ; 
 size_t BNA_MOD_RES_MEM_T_TXQ_ARRAY ; 
 size_t BNA_MOD_RES_MEM_T_TX_ARRAY ; 
 int /*<<< orphan*/  BNA_STATUS_T_DISABLED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_q_qe_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bna_tx_mod_init(struct bna_tx_mod *tx_mod, struct bna *bna,
		struct bna_res_info *res_info)
{
	int i;

	tx_mod->bna = bna;
	tx_mod->flags = 0;

	tx_mod->tx = (struct bna_tx *)
		res_info[BNA_MOD_RES_MEM_T_TX_ARRAY].res_u.mem_info.mdl[0].kva;
	tx_mod->txq = (struct bna_txq *)
		res_info[BNA_MOD_RES_MEM_T_TXQ_ARRAY].res_u.mem_info.mdl[0].kva;

	INIT_LIST_HEAD(&tx_mod->tx_free_q);
	INIT_LIST_HEAD(&tx_mod->tx_active_q);

	INIT_LIST_HEAD(&tx_mod->txq_free_q);

	for (i = 0; i < bna->ioceth.attr.num_txq; i++) {
		tx_mod->tx[i].rid = i;
		bfa_q_qe_init(&tx_mod->tx[i].qe);
		list_add_tail(&tx_mod->tx[i].qe, &tx_mod->tx_free_q);
		bfa_q_qe_init(&tx_mod->txq[i].qe);
		list_add_tail(&tx_mod->txq[i].qe, &tx_mod->txq_free_q);
	}

	tx_mod->prio_map = BFI_TX_PRIO_MAP_ALL;
	tx_mod->default_prio = 0;
	tx_mod->iscsi_over_cee = BNA_STATUS_T_DISABLED;
	tx_mod->iscsi_prio = -1;
}