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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ lck_mtx_interlock_try_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ordered_load_mtx_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
lck_mtx_interlock_try_lock_disable_interrupts(
	lck_mtx_t *mutex,
	boolean_t *istate)
{
	uint32_t	state;

	*istate = ml_set_interrupts_enabled(FALSE);
	state = ordered_load_mtx_state(mutex);

	if (lck_mtx_interlock_try_lock(mutex, &state)) {
		return 1;
	} else {
		ml_set_interrupts_enabled(*istate);
		return 0;
	}
}