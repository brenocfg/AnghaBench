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
 int /*<<< orphan*/  ENOSYS ; 
 int FUTEX_REQUEUE ; 
 int /*<<< orphan*/  SYS_futex ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int volatile*,int,int /*<<< orphan*/ ,int,int volatile*) ; 
 int /*<<< orphan*/  __wake (int volatile*,int,int) ; 
 int /*<<< orphan*/  a_store (int volatile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void unlock_requeue(volatile int *l, volatile int *r, int w)
{
	a_store(l, 0);
#ifdef __EMSCRIPTEN__
	// Here the intent is to wake one waiter, and requeue all other waiters from waiting on address 'l'
	// to wait on address 'r' instead. This is not possible at the moment with SharedArrayBuffer Atomics,
	// as it does not have a "wake X waiters and requeue the rest" primitive. However this kind of
	// primitive is strictly not needed, since it is more like an optimization to avoid spuriously waking
	// all waiters, just to make them wait on another location immediately afterwards. Here we do exactly
	// that: wake every waiter.
	emscripten_futex_wake(l, 0x7FFFFFFF);
#else
	if (w) __wake(l, 1, 1);
	else __syscall(SYS_futex, l, FUTEX_REQUEUE|128, 0, 1, r) != -ENOSYS
		|| __syscall(SYS_futex, l, FUTEX_REQUEUE, 0, 1, r);
#endif
}