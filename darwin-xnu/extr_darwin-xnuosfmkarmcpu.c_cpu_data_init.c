#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pmap {int dummy; } ;
struct TYPE_4__ {scalar_t__* cpu_asid_high_bits; int /*<<< orphan*/  cpu_number; scalar_t__ cpu_user_pmap_stamp; struct pmap* cpu_user_pmap; } ;
typedef  TYPE_1__ pmap_cpu_data_t ;
struct TYPE_5__ {int cpu_idle_latency; int cpu_idle_pop; int cpu_reset_type; int cpu_reset_handler; int cpu_reset_assist; int cpu_regmap_paddr; int cpu_phys_id; int cpu_sleep_token_last; int /*<<< orphan*/  halt_status; TYPE_1__ cpu_pmap_cpu_data; int /*<<< orphan*/ * cpu_xcall_p1; int /*<<< orphan*/ * cpu_xcall_p0; int /*<<< orphan*/  cpu_sleep_token; int /*<<< orphan*/ * cpu_set_decrementer_func; int /*<<< orphan*/ * cpu_get_decrementer_func; int /*<<< orphan*/ * cpu_tbd_hardware_val; int /*<<< orphan*/ * cpu_tbd_hardware_addr; int /*<<< orphan*/ * cpu_get_fiq_handler; int /*<<< orphan*/  cpu_signal; scalar_t__ cpu_l3_size; scalar_t__ cpu_l3_id; scalar_t__ cpu_l2_size; scalar_t__ cpu_l2_id; scalar_t__ cpu_cluster_id; int /*<<< orphan*/  cpu_cluster_type; scalar_t__ cpu_l2_access_penalty; void* cpu_idle_notify; scalar_t__ cpu_base_timebase_high; scalar_t__ cpu_base_timebase_low; int /*<<< orphan*/ * cpu_user_debug; int /*<<< orphan*/ * rtclock_datap; int /*<<< orphan*/  rtcPop; void* cpu_cache_dispatch; int /*<<< orphan*/  cpu_pending_ast; scalar_t__ cpu_int_state; scalar_t__ interrupts_enabled; scalar_t__ cpu_flags; } ;
typedef  TYPE_2__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_CPU_ON_SLEEP_PATH ; 
 int /*<<< orphan*/  AST_NONE ; 
 int /*<<< orphan*/  CLUSTER_TYPE_SMP ; 
 int /*<<< orphan*/  CPU_NOT_HALTED ; 
 int /*<<< orphan*/  EndOfAllTime ; 
 int /*<<< orphan*/  PMAP_INVALID_CPU_NUM ; 
 int /*<<< orphan*/  RTClockData ; 
 int /*<<< orphan*/  SIGPdisabled ; 

void
cpu_data_init(cpu_data_t *cpu_data_ptr)
{
	uint32_t i = 0;

	cpu_data_ptr->cpu_flags = 0;
#if	__arm__
	cpu_data_ptr->cpu_exc_vectors = (vm_offset_t)&ExceptionVectorsTable;
#endif
	cpu_data_ptr->interrupts_enabled = 0;
	cpu_data_ptr->cpu_int_state = 0;
	cpu_data_ptr->cpu_pending_ast = AST_NONE;
	cpu_data_ptr->cpu_cache_dispatch = (void *) 0;
	cpu_data_ptr->rtcPop = EndOfAllTime;
	cpu_data_ptr->rtclock_datap = &RTClockData;
	cpu_data_ptr->cpu_user_debug = NULL;
	cpu_data_ptr->cpu_base_timebase_low = 0;
	cpu_data_ptr->cpu_base_timebase_high = 0;
	cpu_data_ptr->cpu_idle_notify = (void *) 0;
	cpu_data_ptr->cpu_idle_latency = 0x0ULL;
	cpu_data_ptr->cpu_idle_pop = 0x0ULL;
	cpu_data_ptr->cpu_reset_type = 0x0UL;
	cpu_data_ptr->cpu_reset_handler = 0x0UL;
	cpu_data_ptr->cpu_reset_assist = 0x0UL;
	cpu_data_ptr->cpu_regmap_paddr = 0x0ULL;
	cpu_data_ptr->cpu_phys_id = 0x0UL;
	cpu_data_ptr->cpu_l2_access_penalty = 0;
	cpu_data_ptr->cpu_cluster_type = CLUSTER_TYPE_SMP;
	cpu_data_ptr->cpu_cluster_id = 0;
	cpu_data_ptr->cpu_l2_id = 0;
	cpu_data_ptr->cpu_l2_size = 0;
	cpu_data_ptr->cpu_l3_id = 0;
	cpu_data_ptr->cpu_l3_size = 0;

	cpu_data_ptr->cpu_signal = SIGPdisabled;

#if DEBUG || DEVELOPMENT
	cpu_data_ptr->failed_xcall = NULL;
	cpu_data_ptr->failed_signal = 0;
	cpu_data_ptr->failed_signal_count = 0;
#endif

	cpu_data_ptr->cpu_get_fiq_handler = NULL;
	cpu_data_ptr->cpu_tbd_hardware_addr = NULL;
	cpu_data_ptr->cpu_tbd_hardware_val = NULL;
	cpu_data_ptr->cpu_get_decrementer_func = NULL;
	cpu_data_ptr->cpu_set_decrementer_func = NULL;
	cpu_data_ptr->cpu_sleep_token = ARM_CPU_ON_SLEEP_PATH;
	cpu_data_ptr->cpu_sleep_token_last = 0x00000000UL;
	cpu_data_ptr->cpu_xcall_p0 = NULL;
	cpu_data_ptr->cpu_xcall_p1 = NULL;

#if	__ARM_SMP__ && defined(ARMA7)
	cpu_data_ptr->cpu_CLWFlush_req = 0x0ULL;
	cpu_data_ptr->cpu_CLWFlush_last = 0x0ULL;
	cpu_data_ptr->cpu_CLWClean_req = 0x0ULL;
	cpu_data_ptr->cpu_CLWClean_last = 0x0ULL;
	cpu_data_ptr->cpu_CLW_active = 0x1UL;
#endif

	pmap_cpu_data_t * pmap_cpu_data_ptr = &cpu_data_ptr->cpu_pmap_cpu_data;

	pmap_cpu_data_ptr->cpu_user_pmap = (struct pmap *) NULL;
	pmap_cpu_data_ptr->cpu_user_pmap_stamp = 0;
	pmap_cpu_data_ptr->cpu_number = PMAP_INVALID_CPU_NUM;

	for (i = 0; i < (sizeof(pmap_cpu_data_ptr->cpu_asid_high_bits) / sizeof(*pmap_cpu_data_ptr->cpu_asid_high_bits)); i++) {
		pmap_cpu_data_ptr->cpu_asid_high_bits[i] = 0;
	}
	cpu_data_ptr->halt_status = CPU_NOT_HALTED;
}