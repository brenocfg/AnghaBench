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
typedef  int /*<<< orphan*/  thread_t ;
struct mt_cpu {int /*<<< orphan*/ * mtc_counts; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDBG_RELEASE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MT_CORE_CYCLES ; 
 int /*<<< orphan*/  MT_KDBG_IC_CPU_CSWITCH ; 
 scalar_t__ kdebug_debugid_explicitly_enabled (int /*<<< orphan*/ ) ; 
 struct mt_cpu* mt_cur_cpu () ; 
 int mt_update_thread (int /*<<< orphan*/ ) ; 

void
mt_sched_update(thread_t thread)
{
	bool updated = mt_update_thread(thread);
	if (!updated) {
		return;
	}

	if (kdebug_debugid_explicitly_enabled(MT_KDBG_IC_CPU_CSWITCH)) {
		struct mt_cpu *mtc = mt_cur_cpu();

		KDBG_RELEASE(MT_KDBG_IC_CPU_CSWITCH,
#ifdef MT_CORE_INSTRS
				mtc->mtc_counts[MT_CORE_INSTRS],
#else /* defined(MT_CORE_INSTRS) */
				0,
#endif /* !defined(MT_CORE_INSTRS) */
				mtc->mtc_counts[MT_CORE_CYCLES]);
	}
}