#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct cpumask {int dummy; } ;
struct lpfc_vector_map_info {int phys_id; int irq; int channel_id; struct cpumask maskbits; scalar_t__ core_id; } ;
struct TYPE_4__ {int num_present_cpu; int num_online_cpu; struct lpfc_vector_map_info* cpu_map; TYPE_1__* msix_entries; } ;
struct lpfc_hba {scalar_t__ cfg_fcp_cpu_map; int cfg_fcp_io_channel; int /*<<< orphan*/  cfg_fcp_io_sched; TYPE_2__ sli4_hba; } ;
struct cpuinfo_x86 {int phys_proc_id; scalar_t__ cpu_core_id; } ;
struct TYPE_3__ {int vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_INIT ; 
 scalar_t__ LPFC_DRIVER_CPU_MAP ; 
 int /*<<< orphan*/  LPFC_FCP_IO_CHAN_MAX ; 
 int /*<<< orphan*/  LPFC_FCP_SCHED_BY_CPU ; 
 int LPFC_VECTOR_MAP_EMPTY ; 
 struct cpuinfo_x86 cpu_data (int) ; 
 int /*<<< orphan*/  cpumask_clear (struct cpumask*) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,struct cpumask*) ; 
 int irq_set_affinity_hint (int,struct cpumask*) ; 
 int lpfc_find_next_cpu (struct lpfc_hba*,int) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int* lpfc_used_cpu ; 
 int /*<<< orphan*/  memset (struct lpfc_vector_map_info*,int,int) ; 

__attribute__((used)) static int
lpfc_sli4_set_affinity(struct lpfc_hba *phba, int vectors)
{
	int i, idx, saved_chann, used_chann, cpu, phys_id;
	int max_phys_id, num_io_channel, first_cpu;
	struct lpfc_vector_map_info *cpup;
#ifdef CONFIG_X86
	struct cpuinfo_x86 *cpuinfo;
#endif
	struct cpumask *mask;
	uint8_t chann[LPFC_FCP_IO_CHAN_MAX+1];

	/* If there is no mapping, just return */
	if (!phba->cfg_fcp_cpu_map)
		return 1;

	/* Init cpu_map array */
	memset(phba->sli4_hba.cpu_map, 0xff,
	       (sizeof(struct lpfc_vector_map_info) *
		phba->sli4_hba.num_present_cpu));

	max_phys_id = 0;
	phys_id = 0;
	num_io_channel = 0;
	first_cpu = LPFC_VECTOR_MAP_EMPTY;

	/* Update CPU map with physical id and core id of each CPU */
	cpup = phba->sli4_hba.cpu_map;
	for (cpu = 0; cpu < phba->sli4_hba.num_present_cpu; cpu++) {
#ifdef CONFIG_X86
		cpuinfo = &cpu_data(cpu);
		cpup->phys_id = cpuinfo->phys_proc_id;
		cpup->core_id = cpuinfo->cpu_core_id;
#else
		/* No distinction between CPUs for other platforms */
		cpup->phys_id = 0;
		cpup->core_id = 0;
#endif

		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
				"3328 CPU physid %d coreid %d\n",
				cpup->phys_id, cpup->core_id);

		if (cpup->phys_id > max_phys_id)
			max_phys_id = cpup->phys_id;
		cpup++;
	}

	/* Now associate the HBA vectors with specific CPUs */
	for (idx = 0; idx < vectors; idx++) {
		cpup = phba->sli4_hba.cpu_map;
		cpu = lpfc_find_next_cpu(phba, phys_id);
		if (cpu == LPFC_VECTOR_MAP_EMPTY) {

			/* Try for all phys_id's */
			for (i = 1; i < max_phys_id; i++) {
				phys_id++;
				if (phys_id > max_phys_id)
					phys_id = 0;
				cpu = lpfc_find_next_cpu(phba, phys_id);
				if (cpu == LPFC_VECTOR_MAP_EMPTY)
					continue;
				goto found;
			}

			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"3329 Cannot set affinity:"
					"Error mapping vector %d (%d)\n",
					idx, vectors);
			return 0;
		}
found:
		cpup += cpu;
		if (phba->cfg_fcp_cpu_map == LPFC_DRIVER_CPU_MAP)
			lpfc_used_cpu[cpu] = phys_id;

		/* Associate vector with selected CPU */
		cpup->irq = phba->sli4_hba.msix_entries[idx].vector;

		/* Associate IO channel with selected CPU */
		cpup->channel_id = idx;
		num_io_channel++;

		if (first_cpu == LPFC_VECTOR_MAP_EMPTY)
			first_cpu = cpu;

		/* Now affinitize to the selected CPU */
		mask = &cpup->maskbits;
		cpumask_clear(mask);
		cpumask_set_cpu(cpu, mask);
		i = irq_set_affinity_hint(phba->sli4_hba.msix_entries[idx].
					  vector, mask);

		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
				"3330 Set Affinity: CPU %d channel %d "
				"irq %d (%x)\n",
				cpu, cpup->channel_id,
				phba->sli4_hba.msix_entries[idx].vector, i);

		/* Spread vector mapping across multple physical CPU nodes */
		phys_id++;
		if (phys_id > max_phys_id)
			phys_id = 0;
	}

	/*
	 * Finally fill in the IO channel for any remaining CPUs.
	 * At this point, all IO channels have been assigned to a specific
	 * MSIx vector, mapped to a specific CPU.
	 * Base the remaining IO channel assigned, to IO channels already
	 * assigned to other CPUs on the same phys_id.
	 */
	for (i = 0; i <= max_phys_id; i++) {
		/*
		 * If there are no io channels already mapped to
		 * this phys_id, just round robin thru the io_channels.
		 * Setup chann[] for round robin.
		 */
		for (idx = 0; idx < phba->cfg_fcp_io_channel; idx++)
			chann[idx] = idx;

		saved_chann = 0;
		used_chann = 0;

		/*
		 * First build a list of IO channels already assigned
		 * to this phys_id before reassigning the same IO
		 * channels to the remaining CPUs.
		 */
		cpup = phba->sli4_hba.cpu_map;
		cpu = first_cpu;
		cpup += cpu;
		for (idx = 0; idx < phba->sli4_hba.num_present_cpu;
		     idx++) {
			if (cpup->phys_id == i) {
				/*
				 * Save any IO channels that are
				 * already mapped to this phys_id.
				 */
				if (cpup->irq != LPFC_VECTOR_MAP_EMPTY) {
					chann[saved_chann] =
						cpup->channel_id;
					saved_chann++;
					goto out;
				}

				/* See if we are using round-robin */
				if (saved_chann == 0)
					saved_chann =
						phba->cfg_fcp_io_channel;

				/* Associate next IO channel with CPU */
				cpup->channel_id = chann[used_chann];
				num_io_channel++;
				used_chann++;
				if (used_chann == saved_chann)
					used_chann = 0;

				lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
						"3331 Set IO_CHANN "
						"CPU %d channel %d\n",
						idx, cpup->channel_id);
			}
out:
			cpu++;
			if (cpu >= phba->sli4_hba.num_present_cpu) {
				cpup = phba->sli4_hba.cpu_map;
				cpu = 0;
			} else {
				cpup++;
			}
		}
	}

	if (phba->sli4_hba.num_online_cpu != phba->sli4_hba.num_present_cpu) {
		cpup = phba->sli4_hba.cpu_map;
		for (idx = 0; idx < phba->sli4_hba.num_present_cpu; idx++) {
			if (cpup->channel_id == LPFC_VECTOR_MAP_EMPTY) {
				cpup->channel_id = 0;
				num_io_channel++;

				lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
						"3332 Assign IO_CHANN "
						"CPU %d channel %d\n",
						idx, cpup->channel_id);
			}
			cpup++;
		}
	}

	/* Sanity check */
	if (num_io_channel != phba->sli4_hba.num_present_cpu)
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3333 Set affinity mismatch:"
				"%d chann != %d cpus: %d vactors\n",
				num_io_channel, phba->sli4_hba.num_present_cpu,
				vectors);

	phba->cfg_fcp_io_sched = LPFC_FCP_SCHED_BY_CPU;
	return 1;
}