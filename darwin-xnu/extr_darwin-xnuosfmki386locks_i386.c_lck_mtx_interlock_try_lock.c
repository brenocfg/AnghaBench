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

/* Variables and functions */
 int lck_mtx_interlock_try_lock_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
lck_mtx_interlock_try_lock(
	lck_mtx_t *mutex,
	uint32_t *new_state)
{
	return lck_mtx_interlock_try_lock_set_flags(mutex, 0, new_state);
}