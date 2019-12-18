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
struct waitq {int dummy; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_number () ; 
 int hwLockTimeOut ; 
 scalar_t__ machine_timeout_suspended () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 int /*<<< orphan*/  panic (char*,struct waitq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pltrace (scalar_t__) ; 
 int /*<<< orphan*/  waitq_held (struct waitq*) ; 
 scalar_t__ waitq_lock_to (struct waitq*,int) ; 

void waitq_lock(struct waitq *wq)
{
	if (__improbable(waitq_lock_to(wq,
				    hwLockTimeOut * 2) == 0)) {
		boolean_t wql_acquired = FALSE;

		while (machine_timeout_suspended()) {
			mp_enable_preemption();
			wql_acquired = waitq_lock_to(wq,
						  hwLockTimeOut * 2);
			if (wql_acquired)
				break;
		}
		if (wql_acquired == FALSE)
			panic("waitq deadlock - waitq=%p, cpu=%d\n",
			      wq, cpu_number());
	}
#if defined(__x86_64__)
	pltrace(FALSE);
#endif
	assert(waitq_held(wq));
}