#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfi_iocfc_cfg_s {int /*<<< orphan*/  num_ioim_reqs; } ;
struct bfa_iocfc_s {struct bfi_iocfc_cfg_s* cfginfo; } ;
struct bfa_s {struct bfa_iocfc_s iocfc; } ;
struct bfa_iocfc_fwcfg_s {int /*<<< orphan*/  num_tskim_reqs; int /*<<< orphan*/  num_ioim_reqs; int /*<<< orphan*/  num_rports; int /*<<< orphan*/  num_uf_bufs; int /*<<< orphan*/  num_fcxp_reqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcp_res_recfg (struct bfa_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcxp_res_recfg (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_rport_res_recfg (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_tskim_res_recfg (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_uf_res_recfg (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocfc_res_recfg(struct bfa_s *bfa, struct bfa_iocfc_fwcfg_s *fwcfg)
{
	struct bfa_iocfc_s	*iocfc   = &bfa->iocfc;
	struct bfi_iocfc_cfg_s	*cfg_info = iocfc->cfginfo;

	bfa_fcxp_res_recfg(bfa, fwcfg->num_fcxp_reqs);
	bfa_uf_res_recfg(bfa, fwcfg->num_uf_bufs);
	bfa_rport_res_recfg(bfa, fwcfg->num_rports);
	bfa_fcp_res_recfg(bfa, cpu_to_be16(cfg_info->num_ioim_reqs),
			  fwcfg->num_ioim_reqs);
	bfa_tskim_res_recfg(bfa, fwcfg->num_tskim_reqs);
}