#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_offset_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_1__* pmap_t ;
typedef  scalar_t__ pmap_paddr_t ;
struct TYPE_20__ {int pfc_invalid_global; int pfc_cpus; } ;
typedef  TYPE_3__ pmap_flush_context ;
typedef  int cpumask_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_19__ {scalar_t__ pm_cr3; scalar_t__ pm_shared; scalar_t__ pm_eptp; } ;
struct TYPE_18__ {scalar_t__ cpu_tlb_invalid; scalar_t__ cpu_tlb_invalid_local; scalar_t__ cpu_tlb_invalid_global; } ;
struct TYPE_17__ {long cpu_active_cr3; scalar_t__ cpu_task_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC ; 
 int /*<<< orphan*/  CPUMASK_ALL ; 
 scalar_t__ CPU_CR3_IS_ACTIVE (unsigned int) ; 
 scalar_t__ CPU_GET_ACTIVE_CR3 (unsigned int) ; 
 scalar_t__ CPU_GET_TASK_CR3 (unsigned int) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 scalar_t__ FALSE ; 
 scalar_t__ LockTimeOut ; 
 int /*<<< orphan*/  MP_TLB_FLUSH ; 
 long NMIPI_acks ; 
 int /*<<< orphan*/  NMIPI_panic (int,int /*<<< orphan*/ ) ; 
 int PMAP_CODE (int /*<<< orphan*/ ) ; 
 int PMAP_DELAY_TLB_FLUSH ; 
 int /*<<< orphan*/  PMAP_TRACE_CONSTANT (int,TYPE_1__*,int,...) ; 
 int /*<<< orphan*/  PMAP__FLUSH_EPT ; 
 int /*<<< orphan*/  PMAP__FLUSH_KERN_TLBS ; 
 int /*<<< orphan*/  PMAP__FLUSH_TLBS ; 
 int /*<<< orphan*/  PMAP__FLUSH_TLBS_TO ; 
 scalar_t__ TLBTimeOut ; 
 int /*<<< orphan*/  TLB_FLUSH_TIMEOUT ; 
 scalar_t__ TRUE ; 
 TYPE_1__* VM_KERNEL_UNSLIDE_OR_PERM (TYPE_1__*) ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_13__* cpu_datap (unsigned int) ; 
 int /*<<< orphan*/  cpu_is_running (unsigned int) ; 
 unsigned int cpu_number () ; 
 int /*<<< orphan*/  cpu_pause () ; 
 TYPE_12__* current_cpu_datap () ; 
 int /*<<< orphan*/  flush_tlb_raw () ; 
 scalar_t__ get_preemption_level () ; 
 int /*<<< orphan*/  i386_signal_cpu (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invept ; 
 scalar_t__ is_ept_pmap (TYPE_1__*) ; 
 TYPE_1__* kernel_pmap ; 
 scalar_t__ mach_absolute_time () ; 
 scalar_t__ machine_timeout_suspended () ; 
 int /*<<< orphan*/  mfence () ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  mp_cpus_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  panic (char*,int,scalar_t__,long,scalar_t__) ; 
 int /*<<< orphan*/  pmap_pcid_invalidate_all_cpus (TYPE_1__*) ; 
 scalar_t__ pmap_pcid_ncpus ; 
 int /*<<< orphan*/  pmap_pcid_validate_cpu (TYPE_1__*,unsigned int) ; 
 int processor_avail_count ; 
 unsigned int real_ncpus ; 
 int /*<<< orphan*/  tlb_flush_global () ; 

void
pmap_flush_tlbs(pmap_t	pmap, vm_map_offset_t startv, vm_map_offset_t endv, int options, pmap_flush_context *pfc)
{
	unsigned int	cpu;
	cpumask_t	cpu_bit;
	cpumask_t	cpus_to_signal = 0;
	unsigned int	my_cpu = cpu_number();
	pmap_paddr_t	pmap_cr3 = pmap->pm_cr3;
	boolean_t	flush_self = FALSE;
	uint64_t	deadline;
	boolean_t	pmap_is_shared = (pmap->pm_shared || (pmap == kernel_pmap));
	boolean_t	need_global_flush = FALSE;
	uint32_t	event_code;
	vm_map_offset_t	event_startv, event_endv;
	boolean_t	is_ept = is_ept_pmap(pmap);

	assert((processor_avail_count < 2) ||
	       (ml_get_interrupts_enabled() && get_preemption_level() != 0));

	if (pmap == kernel_pmap) {
		event_code = PMAP_CODE(PMAP__FLUSH_KERN_TLBS);
		event_startv = VM_KERNEL_UNSLIDE_OR_PERM(startv);
		event_endv = VM_KERNEL_UNSLIDE_OR_PERM(endv);
	} else if (is_ept) {
		event_code = PMAP_CODE(PMAP__FLUSH_EPT);
		event_startv = startv;
		event_endv = endv;
	} else {
		event_code = PMAP_CODE(PMAP__FLUSH_TLBS);
		event_startv = startv;
		event_endv = endv;
	}

	PMAP_TRACE_CONSTANT(event_code | DBG_FUNC_START,
	                    VM_KERNEL_UNSLIDE_OR_PERM(pmap), options,
	                    event_startv, event_endv);

	if (is_ept) {
		mp_cpus_call(CPUMASK_ALL, ASYNC, invept, (void*)pmap->pm_eptp);
		goto out;
	}

	/*
	 * Scan other cpus for matching active or task CR3.
	 * For idle cpus (with no active map) we mark them invalid but
	 * don't signal -- they'll check as they go busy.
	 */
	if (pmap_pcid_ncpus) {
		if (pmap_is_shared)
			need_global_flush = TRUE;
		pmap_pcid_invalidate_all_cpus(pmap);
		mfence();
	}
	for (cpu = 0, cpu_bit = 1; cpu < real_ncpus; cpu++, cpu_bit <<= 1) {
		if (!cpu_is_running(cpu))
			continue;
		uint64_t	cpu_active_cr3 = CPU_GET_ACTIVE_CR3(cpu);
		uint64_t	cpu_task_cr3 = CPU_GET_TASK_CR3(cpu);
//recall that the shadowed task cr3 is pre-composed
		if ((pmap_cr3 == cpu_task_cr3) ||
		    (pmap_cr3 == cpu_active_cr3) ||
		    (pmap_is_shared)) {

			if (options & PMAP_DELAY_TLB_FLUSH) {
				if (need_global_flush == TRUE)
					pfc->pfc_invalid_global |= cpu_bit;
				pfc->pfc_cpus |= cpu_bit;

				continue;
			}
			if (cpu == my_cpu) {
				flush_self = TRUE;
				continue;
			}
			if (need_global_flush == TRUE)
				cpu_datap(cpu)->cpu_tlb_invalid_global = TRUE;
			else
				cpu_datap(cpu)->cpu_tlb_invalid_local = TRUE;
			mfence();

			/*
			 * We don't need to signal processors which will flush
			 * lazily at the idle state or kernel boundary.
			 * For example, if we're invalidating the kernel pmap,
			 * processors currently in userspace don't need to flush
			 * their TLBs until the next time they enter the kernel.
			 * Alterations to the address space of a task active
			 * on a remote processor result in a signal, to
			 * account for copy operations. (There may be room
			 * for optimization in such cases).
			 * The order of the loads below with respect
			 * to the store to the "cpu_tlb_invalid" field above
			 * is important--hence the barrier.
			 */
			if (CPU_CR3_IS_ACTIVE(cpu) &&
			    (pmap_cr3 == CPU_GET_ACTIVE_CR3(cpu) ||
			     pmap->pm_shared ||
			     (pmap_cr3 == CPU_GET_TASK_CR3(cpu)))) {
				cpus_to_signal |= cpu_bit;
				i386_signal_cpu(cpu, MP_TLB_FLUSH, ASYNC);
			}
		}
	}
	if ((options & PMAP_DELAY_TLB_FLUSH))
		goto out;

	/*
	 * Flush local tlb if required.
	 * Do this now to overlap with other processors responding.
	 */
	if (flush_self) {
		if (pmap_pcid_ncpus) {
			pmap_pcid_validate_cpu(pmap, my_cpu);
			if (pmap_is_shared)
				tlb_flush_global();
			else
				flush_tlb_raw();
		}
		else
			flush_tlb_raw();
	}

	if (cpus_to_signal) {
		cpumask_t	cpus_to_respond = cpus_to_signal;

		deadline = mach_absolute_time() +
				(TLBTimeOut ? TLBTimeOut : LockTimeOut);
		boolean_t is_timeout_traced = FALSE;

		/*
		 * Wait for those other cpus to acknowledge
		 */
		while (cpus_to_respond != 0) {
			long orig_acks = 0;

			for (cpu = 0, cpu_bit = 1; cpu < real_ncpus; cpu++, cpu_bit <<= 1) {
				/* Consider checking local/global invalidity
				 * as appropriate in the PCID case.
				 */
				if ((cpus_to_respond & cpu_bit) != 0) {
					if (!cpu_is_running(cpu) ||
					    cpu_datap(cpu)->cpu_tlb_invalid == FALSE ||
					    !CPU_CR3_IS_ACTIVE(cpu)) {
						cpus_to_respond &= ~cpu_bit;
					}
					cpu_pause();
				}
				if (cpus_to_respond == 0)
					break;
			}
			if (cpus_to_respond && (mach_absolute_time() > deadline)) {
				if (machine_timeout_suspended())
					continue;
				if (TLBTimeOut == 0) {
					/* cut tracepoint but don't panic */
					if (is_timeout_traced)
						continue;

					PMAP_TRACE_CONSTANT(PMAP_CODE(PMAP__FLUSH_TLBS_TO),
					                    VM_KERNEL_UNSLIDE_OR_PERM(pmap),
					                    cpus_to_signal,
					                    cpus_to_respond);

					is_timeout_traced = TRUE;
					continue;
				}
				orig_acks = NMIPI_acks;

				NMIPI_panic(cpus_to_respond, TLB_FLUSH_TIMEOUT);
				panic("TLB invalidation IPI timeout, unresponsive CPU bitmap: 0x%llx, NMIPI acks: 0x%lx, now: 0x%lx, deadline: %llu",
				      cpus_to_respond, orig_acks, NMIPI_acks, deadline);
			}
		}
	}

	if (__improbable((pmap == kernel_pmap) && (flush_self != TRUE))) {
		panic("pmap_flush_tlbs: pmap == kernel_pmap && flush_self != TRUE; kernel CR3: 0x%llX, pmap_cr3: 0x%llx, CPU active CR3: 0x%llX, CPU Task Map: %d", kernel_pmap->pm_cr3, pmap_cr3, current_cpu_datap()->cpu_active_cr3, current_cpu_datap()->cpu_task_map);
	}

out:
	PMAP_TRACE_CONSTANT(event_code | DBG_FUNC_END,
	                    VM_KERNEL_UNSLIDE_OR_PERM(pmap), cpus_to_signal,
	                    event_startv, event_endv);

}