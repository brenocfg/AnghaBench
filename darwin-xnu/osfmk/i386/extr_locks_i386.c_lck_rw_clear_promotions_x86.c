#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct TYPE_5__ {scalar_t__ rwlock_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  lck_rw_clear_promotion (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__,TYPE_1__*) ; 

void
lck_rw_clear_promotions_x86(thread_t thread)
{
#if MACH_LDEBUG
	/* It's fatal to leave a RW lock locked and return to userspace */
	panic("%u rw lock(s) held on return to userspace for thread %p", thread->rwlock_count, thread);
#else
	/* Paper over the issue */
	thread->rwlock_count = 0;
	lck_rw_clear_promotion(thread, 0);
#endif
}