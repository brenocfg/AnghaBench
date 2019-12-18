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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lck_mtx_lock_acquire_inline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_try_lock_finish_inline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ordered_load_mtx_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) __attribute__((noinline))
static boolean_t
lck_mtx_try_lock_acquire_tail(
	lck_mtx_t	*mutex)
{
	lck_mtx_lock_acquire_inline(mutex);
	lck_mtx_try_lock_finish_inline(mutex, ordered_load_mtx_state(mutex));

	return TRUE;
}