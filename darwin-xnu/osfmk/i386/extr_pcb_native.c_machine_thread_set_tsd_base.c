#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
struct real_descriptor {int limit_low; int base_low; int base_med; int base_high; int access; int granularity; int /*<<< orphan*/  limit_high; } ;
typedef  TYPE_3__* pcb_t ;
typedef  int mach_vm_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_12__ {int cu_user_gs_base; } ;
struct TYPE_15__ {TYPE_1__ cpu_uber; } ;
typedef  TYPE_4__ cpu_data_t ;
struct TYPE_16__ {int /*<<< orphan*/  gs; } ;
struct TYPE_14__ {int cthread_self; struct real_descriptor cthread_desc; int /*<<< orphan*/  iss; } ;
struct TYPE_13__ {scalar_t__ task; } ;

/* Variables and functions */
 int ACC_DATA_W ; 
 int ACC_P ; 
 int ACC_PL_U ; 
 int /*<<< orphan*/  IS_USERADDR64_CANONICAL (int) ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  MSR_IA32_KERNEL_GS_BASE ; 
 int SZ_32 ; 
 int SZ_G ; 
 TYPE_3__* THREAD_TO_PCB (TYPE_2__*) ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  USER_CTHREAD ; 
 TYPE_4__* current_cpu_datap () ; 
 TYPE_2__* current_thread () ; 
 scalar_t__ kernel_task ; 
 struct real_descriptor* ldt_desc_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 int rdmsr64 (int /*<<< orphan*/ ) ; 
 TYPE_6__* saved_state32 (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_is_64bit_addr (TYPE_2__*) ; 
 int /*<<< orphan*/  wrmsr64 (int /*<<< orphan*/ ,int) ; 

kern_return_t
machine_thread_set_tsd_base(
	thread_t			thread,
	mach_vm_offset_t	tsd_base)
{

	if (thread->task == kernel_task) {
		return KERN_INVALID_ARGUMENT;
	}

	if (thread_is_64bit_addr(thread)) {
		/* check for canonical address, set 0 otherwise  */
		if (!IS_USERADDR64_CANONICAL(tsd_base))
			tsd_base = 0ULL;
	} else {
		if (tsd_base > UINT32_MAX)
			tsd_base = 0ULL;
	}

	pcb_t pcb = THREAD_TO_PCB(thread);
	pcb->cthread_self = tsd_base;

	if (!thread_is_64bit_addr(thread)) {
		/* Set up descriptor for later use */
		struct real_descriptor desc = {
			.limit_low = 1,
			.limit_high = 0,
			.base_low = tsd_base & 0xffff,
			.base_med = (tsd_base >> 16) & 0xff,
			.base_high = (tsd_base >> 24) & 0xff,
			.access = ACC_P|ACC_PL_U|ACC_DATA_W,
			.granularity = SZ_32|SZ_G,
		};

		pcb->cthread_desc = desc;
		saved_state32(pcb->iss)->gs = USER_CTHREAD;
	}

	/* For current thread, make the TSD base active immediately */
	if (thread == current_thread()) {

		if (thread_is_64bit_addr(thread)) {
			cpu_data_t              *cdp;

			mp_disable_preemption();
			cdp = current_cpu_datap();
			if ((cdp->cpu_uber.cu_user_gs_base != pcb->cthread_self) ||
				(pcb->cthread_self != rdmsr64(MSR_IA32_KERNEL_GS_BASE)))
				wrmsr64(MSR_IA32_KERNEL_GS_BASE, tsd_base);
			cdp->cpu_uber.cu_user_gs_base = tsd_base;
			mp_enable_preemption();
		} else {

			/* assign descriptor */
			mp_disable_preemption();
			*ldt_desc_p(USER_CTHREAD) = pcb->cthread_desc;
			mp_enable_preemption();
		}
	}

	return KERN_SUCCESS;
}