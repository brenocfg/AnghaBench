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
struct bfi_pbc_vport_s {int dummy; } ;
struct TYPE_2__ {int nvports; int /*<<< orphan*/  vport; } ;
struct bfi_iocfc_cfgrsp_s {TYPE_1__ pbc_cfg; } ;
struct bfa_iocfc_s {struct bfi_iocfc_cfgrsp_s* cfgrsp; } ;
struct bfa_s {struct bfa_iocfc_s iocfc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct bfi_pbc_vport_s*,int /*<<< orphan*/ ,int) ; 

int
bfa_iocfc_get_pbc_vports(struct bfa_s *bfa, struct bfi_pbc_vport_s *pbc_vport)
{
	struct bfa_iocfc_s *iocfc = &bfa->iocfc;
	struct bfi_iocfc_cfgrsp_s *cfgrsp = iocfc->cfgrsp;

	memcpy(pbc_vport, cfgrsp->pbc_cfg.vport, sizeof(cfgrsp->pbc_cfg.vport));
	return cfgrsp->pbc_cfg.nvports;
}