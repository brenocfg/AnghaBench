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
typedef  int /*<<< orphan*/  lck_mtx_t ;

/* Variables and functions */

__attribute__((used)) static inline void
lck_mtx_check_preemption(lck_mtx_t *lock)
{
#if	DEVELOPMENT || DEBUG
	int pl = get_preemption_level();

	if (pl != 0)
		panic("Attempt to take mutex with preemption disabled. Lock=%p, level=%d", lock, pl);
#else
	(void)lock;
#endif
}