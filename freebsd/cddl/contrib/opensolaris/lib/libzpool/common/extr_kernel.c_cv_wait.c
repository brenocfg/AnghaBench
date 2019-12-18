#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * m_owner; int /*<<< orphan*/  m_lock; } ;
typedef  TYPE_1__ kmutex_t ;
typedef  int /*<<< orphan*/  kcondvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EINTR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curthread ; 
 int /*<<< orphan*/ * mutex_owner (TYPE_1__*) ; 

void
cv_wait(kcondvar_t *cv, kmutex_t *mp)
{
	ASSERT(mutex_owner(mp) == curthread);
	mp->m_owner = NULL;
	int ret = cond_wait(cv, &mp->m_lock);
	VERIFY(ret == 0 || ret == EINTR);
	mp->m_owner = curthread;
}