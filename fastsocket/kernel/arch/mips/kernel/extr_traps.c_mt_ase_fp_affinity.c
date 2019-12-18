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
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_4__ {int /*<<< orphan*/  user_cpus_allowed; int /*<<< orphan*/  emulated_fp; } ;
struct TYPE_5__ {int /*<<< orphan*/  cpus_allowed; TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_FPUBOUND ; 
 int /*<<< orphan*/  cpus_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpus_intersects (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 scalar_t__ mt_fpemul_threshold ; 
 int /*<<< orphan*/  mt_fpu_cpumask ; 
 int /*<<< orphan*/  set_cpus_allowed (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt_ase_fp_affinity(void)
{
#ifdef CONFIG_MIPS_MT_FPAFF
	if (mt_fpemul_threshold > 0 &&
	     ((current->thread.emulated_fp++ > mt_fpemul_threshold))) {
		/*
		 * If there's no FPU present, or if the application has already
		 * restricted the allowed set to exclude any CPUs with FPUs,
		 * we'll skip the procedure.
		 */
		if (cpus_intersects(current->cpus_allowed, mt_fpu_cpumask)) {
			cpumask_t tmask;

			current->thread.user_cpus_allowed
				= current->cpus_allowed;
			cpus_and(tmask, current->cpus_allowed,
				mt_fpu_cpumask);
			set_cpus_allowed(current, tmask);
			set_thread_flag(TIF_FPUBOUND);
		}
	}
#endif /* CONFIG_MIPS_MT_FPAFF */
}