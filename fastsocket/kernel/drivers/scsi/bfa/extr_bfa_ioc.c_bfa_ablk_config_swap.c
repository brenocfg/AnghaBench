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
typedef  void* u16 ;
struct bfa_ablk_cfg_s {struct bfa_ablk_cfg_inst_s* inst; } ;
struct bfa_ablk_cfg_inst_s {TYPE_1__* pf_cfg; } ;
struct TYPE_2__ {void* bw_max; void* bw_min; void* num_vectors; void* num_qpairs; void* pers; } ;

/* Variables and functions */
 int BFA_ABLK_MAX ; 
 int BFA_ABLK_MAX_PFS ; 
 void* be16_to_cpu (void*) ; 

__attribute__((used)) static void
bfa_ablk_config_swap(struct bfa_ablk_cfg_s *cfg)
{
	struct bfa_ablk_cfg_inst_s *cfg_inst;
	int i, j;
	u16	be16;

	for (i = 0; i < BFA_ABLK_MAX; i++) {
		cfg_inst = &cfg->inst[i];
		for (j = 0; j < BFA_ABLK_MAX_PFS; j++) {
			be16 = cfg_inst->pf_cfg[j].pers;
			cfg_inst->pf_cfg[j].pers = be16_to_cpu(be16);
			be16 = cfg_inst->pf_cfg[j].num_qpairs;
			cfg_inst->pf_cfg[j].num_qpairs = be16_to_cpu(be16);
			be16 = cfg_inst->pf_cfg[j].num_vectors;
			cfg_inst->pf_cfg[j].num_vectors = be16_to_cpu(be16);
			be16 = cfg_inst->pf_cfg[j].bw_min;
			cfg_inst->pf_cfg[j].bw_min = be16_to_cpu(be16);
			be16 = cfg_inst->pf_cfg[j].bw_max;
			cfg_inst->pf_cfg[j].bw_max = be16_to_cpu(be16);
		}
	}
}