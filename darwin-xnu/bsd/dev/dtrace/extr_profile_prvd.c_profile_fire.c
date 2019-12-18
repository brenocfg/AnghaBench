#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int cpsr; int pc; } ;
typedef  TYPE_2__ x86_saved_state_t ;
struct TYPE_15__ {int rip; } ;
struct TYPE_17__ {int cpsr; int pc; TYPE_1__ isf; } ;
typedef  TYPE_3__ x86_saved_state64_t ;
struct TYPE_18__ {int eip; } ;
typedef  TYPE_4__ x86_saved_state32_t ;
struct TYPE_19__ {int /*<<< orphan*/  prof_id; } ;
typedef  TYPE_5__ profile_probe_t ;
struct TYPE_20__ {scalar_t__ profc_interval; scalar_t__ profc_expected; TYPE_5__* profc_probe; } ;
typedef  TYPE_6__ profile_probe_percpu_t ;
typedef  scalar_t__ hrtime_t ;
typedef  TYPE_2__ arm_saved_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  VALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ dtrace_gethrtime () ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* find_kern_regs (int /*<<< orphan*/ ) ; 
 scalar_t__ find_user_regs (int /*<<< orphan*/ ) ; 
 int get_saved_state_pc (TYPE_2__*) ; 
 scalar_t__ is_saved_state64 (TYPE_2__*) ; 
 int /*<<< orphan*/  pal_register_cache_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* saved_state32 (TYPE_2__*) ; 
 TYPE_3__* saved_state64 (TYPE_2__*) ; 

__attribute__((used)) static void
profile_fire(void *arg)
{
	profile_probe_percpu_t *pcpu = arg;
	profile_probe_t *prof = pcpu->profc_probe;
	hrtime_t late;

	late = dtrace_gethrtime() - pcpu->profc_expected;
	pcpu->profc_expected += pcpu->profc_interval;

#if defined(__x86_64__)
	x86_saved_state_t *kern_regs = find_kern_regs(current_thread());

	if (NULL != kern_regs) {
		/* Kernel was interrupted. */
		dtrace_probe(prof->prof_id, saved_state64(kern_regs)->isf.rip,  0x0, late, 0, 0);

	} else {
		pal_register_cache_state(current_thread(), VALID);
		/* Possibly a user interrupt */
		x86_saved_state_t   *tagged_regs = (x86_saved_state_t *)find_user_regs(current_thread());

		if (NULL == tagged_regs) {
			/* Too bad, so sad, no useful interrupt state. */
			dtrace_probe(prof->prof_id, 0xcafebabe,
	    		0x0, late, 0, 0); /* XXX_BOGUS also see profile_usermode() below. */
		} else if (is_saved_state64(tagged_regs)) {
			x86_saved_state64_t *regs = saved_state64(tagged_regs);

			dtrace_probe(prof->prof_id, 0x0, regs->isf.rip, late, 0, 0);
		} else {
			x86_saved_state32_t *regs = saved_state32(tagged_regs);

			dtrace_probe(prof->prof_id, 0x0, regs->eip, late, 0, 0);
		}
	}
#elif defined(__arm__)
	{
		arm_saved_state_t *arm_kern_regs = (arm_saved_state_t *) find_kern_regs(current_thread());

		// We should only come in here from interrupt context, so we should always have valid kernel regs
		assert(NULL != arm_kern_regs);

		if (arm_kern_regs->cpsr & 0xF) {
			/* Kernel was interrupted. */
			dtrace_probe(prof->prof_id, arm_kern_regs->pc,  0x0, late, 0, 0);
		} else {
			/* Possibly a user interrupt */
			arm_saved_state_t   *arm_user_regs = (arm_saved_state_t *)find_user_regs(current_thread());

			if (NULL == arm_user_regs) {
				/* Too bad, so sad, no useful interrupt state. */
				dtrace_probe(prof->prof_id, 0xcafebabe, 0x0, late, 0, 0); /* XXX_BOGUS also see profile_usermode() below. */
			} else {
				dtrace_probe(prof->prof_id, 0x0, arm_user_regs->pc, late, 0, 0);
			}
		}
	}
#elif defined(__arm64__)
	{
		arm_saved_state_t *arm_kern_regs = (arm_saved_state_t *) find_kern_regs(current_thread());

		// We should only come in here from interrupt context, so we should always have valid kernel regs
		assert(NULL != arm_kern_regs);

		if (saved_state64(arm_kern_regs)->cpsr & 0xF) {
			/* Kernel was interrupted. */
			dtrace_probe(prof->prof_id, saved_state64(arm_kern_regs)->pc,  0x0, late, 0, 0);
		} else {
			/* Possibly a user interrupt */
			arm_saved_state_t   *arm_user_regs = (arm_saved_state_t *)find_user_regs(current_thread());

			if (NULL == arm_user_regs) {
				/* Too bad, so sad, no useful interrupt state. */
				dtrace_probe(prof->prof_id, 0xcafebabe, 0x0, late, 0, 0); /* XXX_BOGUS also see profile_usermode() below. */
			} else {
				dtrace_probe(prof->prof_id, 0x0, get_saved_state_pc(arm_user_regs), late, 0, 0);
			}
		}
	}
#else
#error Unknown architecture
#endif
}