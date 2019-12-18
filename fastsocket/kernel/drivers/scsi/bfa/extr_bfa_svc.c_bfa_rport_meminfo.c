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
struct bfa_s {int dummy; } ;
struct bfa_rport_s {int dummy; } ;
struct bfa_meminfo_s {int dummy; } ;
struct bfa_mem_kva_s {int dummy; } ;
struct TYPE_2__ {int num_rports; } ;
struct bfa_iocfc_cfg_s {TYPE_1__ fwcfg; } ;

/* Variables and functions */
 struct bfa_mem_kva_s* BFA_MEM_RPORT_KVA (struct bfa_s*) ; 
 int BFA_RPORT_MIN ; 
 int /*<<< orphan*/  bfa_mem_kva_setup (struct bfa_meminfo_s*,struct bfa_mem_kva_s*,int) ; 

__attribute__((used)) static void
bfa_rport_meminfo(struct bfa_iocfc_cfg_s *cfg, struct bfa_meminfo_s *minfo,
		struct bfa_s *bfa)
{
	struct bfa_mem_kva_s *rport_kva = BFA_MEM_RPORT_KVA(bfa);

	if (cfg->fwcfg.num_rports < BFA_RPORT_MIN)
		cfg->fwcfg.num_rports = BFA_RPORT_MIN;

	/* kva memory */
	bfa_mem_kva_setup(minfo, rport_kva,
		cfg->fwcfg.num_rports * sizeof(struct bfa_rport_s));
}