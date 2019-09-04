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
#define  EBUSY 128 
 scalar_t__ PTHREAD_MUTEX_NORMAL ; 
 int __pthread_mutex_trylock (TYPE_1__*) ; 
 int a_cas (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int thrd_busy ; 
 int thrd_error ; 
 int thrd_success ; 

int mtx_trylock(mtx_t *m)
{
	if (m->_m_type == PTHREAD_MUTEX_NORMAL)
		return (a_cas(&m->_m_lock, 0, EBUSY) & EBUSY) ? thrd_busy : thrd_success;

	int ret = __pthread_mutex_trylock(m);
	switch (ret) {
	default:    return thrd_error;
	case 0:     return thrd_success;
	case EBUSY: return thrd_busy;
	}
}