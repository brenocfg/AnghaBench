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
typedef  scalar_t__ uint64_t ;
struct mt_cpu {scalar_t__* mtc_snaps; } ;

/* Variables and functions */
 size_t MT_CORE_CYCLES ; 
 size_t MT_CORE_INSTRS ; 
 int /*<<< orphan*/  mt_core_supported ; 
 struct mt_cpu* mt_cur_cpu () ; 

void
mt_perfcontrol(uint64_t *instrs, uint64_t *cycles)
{
	if (!mt_core_supported) {
		*instrs = 0;
		*cycles = 0;
		return;
	}

	struct mt_cpu *mtc = mt_cur_cpu();

	/*
	 * The performance controller queries the hardware directly, so provide the
	 * last snapshot we took for the core.  This is the value from when we
	 * updated the thread counts.
	 */

#ifdef MT_CORE_INSTRS
	*instrs = mtc->mtc_snaps[MT_CORE_INSTRS];
#else /* defined(MT_CORE_INSTRS) */
	*instrs = 0;
#endif /* !defined(MT_CORE_INSTRS) */

	*cycles = mtc->mtc_snaps[MT_CORE_CYCLES];
}