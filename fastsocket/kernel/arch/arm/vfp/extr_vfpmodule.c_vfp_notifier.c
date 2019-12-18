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
struct TYPE_2__ {size_t cpu; int fpexc; int /*<<< orphan*/  fpscr; } ;
union vfp_state {TYPE_1__ hard; } ;
typedef  int u32 ;
struct thread_info {size_t cpu; union vfp_state vfpstate; } ;
struct notifier_block {int dummy; } ;
typedef  size_t __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  FPEXC ; 
 int FPEXC_EN ; 
 int /*<<< orphan*/  FPSCR_ROUND_NEAREST ; 
 int NOTIFY_DONE ; 
 unsigned long THREAD_NOTIFY_FLUSH ; 
 unsigned long THREAD_NOTIFY_SWITCH ; 
 int fmrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmxr (int /*<<< orphan*/ ,int) ; 
 union vfp_state** last_VFP_context ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (union vfp_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfp_save_state (union vfp_state*,int) ; 

__attribute__((used)) static int vfp_notifier(struct notifier_block *self, unsigned long cmd, void *v)
{
	struct thread_info *thread = v;
	union vfp_state *vfp;
	__u32 cpu = thread->cpu;

	if (likely(cmd == THREAD_NOTIFY_SWITCH)) {
		u32 fpexc = fmrx(FPEXC);

#ifdef CONFIG_SMP
		/*
		 * On SMP, if VFP is enabled, save the old state in
		 * case the thread migrates to a different CPU. The
		 * restoring is done lazily.
		 */
		if ((fpexc & FPEXC_EN) && last_VFP_context[cpu]) {
			vfp_save_state(last_VFP_context[cpu], fpexc);
			last_VFP_context[cpu]->hard.cpu = cpu;
		}
		/*
		 * Thread migration, just force the reloading of the
		 * state on the new CPU in case the VFP registers
		 * contain stale data.
		 */
		if (thread->vfpstate.hard.cpu != cpu)
			last_VFP_context[cpu] = NULL;
#endif

		/*
		 * Always disable VFP so we can lazily save/restore the
		 * old state.
		 */
		fmxr(FPEXC, fpexc & ~FPEXC_EN);
		return NOTIFY_DONE;
	}

	vfp = &thread->vfpstate;
	if (cmd == THREAD_NOTIFY_FLUSH) {
		/*
		 * Per-thread VFP initialisation.
		 */
		memset(vfp, 0, sizeof(union vfp_state));

		vfp->hard.fpexc = FPEXC_EN;
		vfp->hard.fpscr = FPSCR_ROUND_NEAREST;

		/*
		 * Disable VFP to ensure we initialise it first.
		 */
		fmxr(FPEXC, fmrx(FPEXC) & ~FPEXC_EN);
	}

	/* flush and release case: Per-thread VFP cleanup. */
	if (last_VFP_context[cpu] == vfp)
		last_VFP_context[cpu] = NULL;

	return NOTIFY_DONE;
}