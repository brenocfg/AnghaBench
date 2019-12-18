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
struct bfa_uf_mod_s {int /*<<< orphan*/  uf_unused_q; int /*<<< orphan*/  uf_posted_q; int /*<<< orphan*/  uf_free_q; int /*<<< orphan*/  num_ufs; struct bfa_s* bfa; } ;
struct bfa_s {int dummy; } ;
struct bfa_pcidev_s {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_uf_bufs; } ;
struct bfa_iocfc_cfg_s {TYPE_1__ fwcfg; } ;

/* Variables and functions */
 struct bfa_uf_mod_s* BFA_UF_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uf_mem_claim (struct bfa_uf_mod_s*) ; 

__attribute__((used)) static void
bfa_uf_attach(struct bfa_s *bfa, void *bfad, struct bfa_iocfc_cfg_s *cfg,
		struct bfa_pcidev_s *pcidev)
{
	struct bfa_uf_mod_s *ufm = BFA_UF_MOD(bfa);

	ufm->bfa = bfa;
	ufm->num_ufs = cfg->fwcfg.num_uf_bufs;
	INIT_LIST_HEAD(&ufm->uf_free_q);
	INIT_LIST_HEAD(&ufm->uf_posted_q);
	INIT_LIST_HEAD(&ufm->uf_unused_q);

	uf_mem_claim(ufm);
}