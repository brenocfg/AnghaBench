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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_ilk_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
lck_mtx_interlock_unlock_enable_interrupts(
	lck_mtx_t *mutex,
	boolean_t istate)
{
	lck_mtx_ilk_unlock(mutex);
	ml_set_interrupts_enabled(istate);
}