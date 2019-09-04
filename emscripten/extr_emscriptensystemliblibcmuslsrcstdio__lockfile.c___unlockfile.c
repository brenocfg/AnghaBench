#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; scalar_t__ waiters; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  __wake (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  a_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __unlockfile(FILE *f)
{
#ifndef __EMSCRIPTEN__
	a_store(&f->lock, 0);

	/* The following read is technically invalid under situations
	 * of self-synchronized destruction. Another thread may have
	 * called fclose as soon as the above store has completed.
	 * Nonetheless, since FILE objects always live in memory
	 * obtained by malloc from the heap, it's safe to assume
	 * the dereferences below will not fault. In the worst case,
	 * a spurious syscall will be made. If the implementation of
	 * malloc changes, this assumption needs revisiting. */

	if (f->waiters) __wake(&f->lock, 1, 1);
#endif
}