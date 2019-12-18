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
struct bfa_fcs_s {TYPE_1__* bfa; int /*<<< orphan*/  min_cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  bfad; } ;

/* Variables and functions */
 int BFI_PBC_MAX_VPORTS ; 
 int /*<<< orphan*/  bfa_fcb_pbc_vport_create (int /*<<< orphan*/ ,struct bfi_pbc_vport_s) ; 
 int bfa_iocfc_get_pbc_vports (TYPE_1__*,struct bfi_pbc_vport_s*) ; 

void
bfa_fcs_pbc_vport_init(struct bfa_fcs_s *fcs)
{
	int i, npbc_vports;
	struct bfi_pbc_vport_s pbc_vports[BFI_PBC_MAX_VPORTS];

	/* Initialize pbc vports */
	if (!fcs->min_cfg) {
		npbc_vports =
			bfa_iocfc_get_pbc_vports(fcs->bfa, pbc_vports);
		for (i = 0; i < npbc_vports; i++)
			bfa_fcb_pbc_vport_create(fcs->bfa->bfad, pbc_vports[i]);
	}
}