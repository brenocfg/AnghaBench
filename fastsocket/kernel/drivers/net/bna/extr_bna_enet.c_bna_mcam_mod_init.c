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
struct TYPE_7__ {TYPE_1__* mdl; } ;
struct TYPE_8__ {TYPE_2__ mem_info; } ;
struct bna_res_info {TYPE_3__ res_u; } ;
struct bna_mcam_mod {struct bna* bna; int /*<<< orphan*/  free_handle_q; struct bna_mcam_handle* mchandle; int /*<<< orphan*/  free_q; struct bna_mac* mcmac; } ;
struct bna_mcam_handle {int /*<<< orphan*/  qe; } ;
struct bna_mac {int /*<<< orphan*/  qe; } ;
struct TYPE_9__ {int num_mcmac; } ;
struct TYPE_10__ {TYPE_4__ attr; } ;
struct bna {TYPE_5__ ioceth; } ;
struct TYPE_6__ {scalar_t__ kva; } ;

/* Variables and functions */
 size_t BNA_MOD_RES_MEM_T_MCHANDLE_ARRAY ; 
 size_t BNA_MOD_RES_MEM_T_MCMAC_ARRAY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_q_qe_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bna_mcam_mod_init(struct bna_mcam_mod *mcam_mod, struct bna *bna,
		  struct bna_res_info *res_info)
{
	int i;

	mcam_mod->mcmac = (struct bna_mac *)
	res_info[BNA_MOD_RES_MEM_T_MCMAC_ARRAY].res_u.mem_info.mdl[0].kva;

	INIT_LIST_HEAD(&mcam_mod->free_q);
	for (i = 0; i < bna->ioceth.attr.num_mcmac; i++) {
		bfa_q_qe_init(&mcam_mod->mcmac[i].qe);
		list_add_tail(&mcam_mod->mcmac[i].qe, &mcam_mod->free_q);
	}

	mcam_mod->mchandle = (struct bna_mcam_handle *)
	res_info[BNA_MOD_RES_MEM_T_MCHANDLE_ARRAY].res_u.mem_info.mdl[0].kva;

	INIT_LIST_HEAD(&mcam_mod->free_handle_q);
	for (i = 0; i < bna->ioceth.attr.num_mcmac; i++) {
		bfa_q_qe_init(&mcam_mod->mchandle[i].qe);
		list_add_tail(&mcam_mod->mchandle[i].qe,
				&mcam_mod->free_handle_q);
	}

	mcam_mod->bna = bna;
}