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
struct TYPE_4__ {scalar_t__ _m_type; int /*<<< orphan*/  _m_lock; } ;
typedef  TYPE_1__ mtx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 scalar_t__ PTHREAD_MUTEX_NORMAL ; 
 int /*<<< orphan*/  a_cas (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mtx_timedlock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int thrd_success ; 

int mtx_lock(mtx_t *m)
{
	if (m->_m_type == PTHREAD_MUTEX_NORMAL && !a_cas(&m->_m_lock, 0, EBUSY))
		return thrd_success;
	/* Calling mtx_timedlock with a null pointer is an extension.
	 * It is convenient, here to avoid duplication of the logic
	 * for return values. */
	return mtx_timedlock(m, 0);
}