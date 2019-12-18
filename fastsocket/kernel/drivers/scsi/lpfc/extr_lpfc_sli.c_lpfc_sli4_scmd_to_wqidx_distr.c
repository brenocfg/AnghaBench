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
typedef  int uint32_t ;
struct lpfc_vector_map_info {int channel_id; } ;
struct TYPE_2__ {int num_present_cpu; struct lpfc_vector_map_info* cpu_map; } ;
struct lpfc_hba {scalar_t__ cfg_fcp_io_sched; int cfg_fcp_io_channel; int /*<<< orphan*/  fcp_qidx; TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 scalar_t__ LPFC_FCP_SCHED_BY_CPU ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int smp_processor_id () ; 

__attribute__((used)) static inline uint32_t
lpfc_sli4_scmd_to_wqidx_distr(struct lpfc_hba *phba)
{
	struct lpfc_vector_map_info *cpup;
	int chann, cpu;

	if (phba->cfg_fcp_io_sched == LPFC_FCP_SCHED_BY_CPU) {
		cpu = smp_processor_id();
		if (cpu < phba->sli4_hba.num_present_cpu) {
			cpup = phba->sli4_hba.cpu_map;
			cpup += cpu;
			return cpup->channel_id;
		}
		chann = cpu;
	}
	chann = atomic_add_return(1, &phba->fcp_qidx);
	chann = (chann % phba->cfg_fcp_io_channel);
	return chann;
}