#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  _restore_fp_context ; 
 int /*<<< orphan*/  _save_fp_context ; 
 scalar_t__ cpu_has_fpu ; 
 int /*<<< orphan*/  fpu_emulator_restore_context ; 
 int /*<<< orphan*/  fpu_emulator_save_context ; 
 int /*<<< orphan*/  restore_fp_context ; 
 int /*<<< orphan*/  save_fp_context ; 
 int /*<<< orphan*/  smp_restore_fp_context ; 
 int /*<<< orphan*/  smp_save_fp_context ; 

__attribute__((used)) static inline void signal_init(void)
{
#ifdef CONFIG_SMP
	/* For now just do the cpu_has_fpu check when the functions are invoked */
	save_fp_context = smp_save_fp_context;
	restore_fp_context = smp_restore_fp_context;
#else
	if (cpu_has_fpu) {
		save_fp_context = _save_fp_context;
		restore_fp_context = _restore_fp_context;
	} else {
		save_fp_context = fpu_emulator_save_context;
		restore_fp_context = fpu_emulator_restore_context;
	}
#endif
}