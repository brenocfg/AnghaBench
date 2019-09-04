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
struct TYPE_4__ {int _m_type; int /*<<< orphan*/  _m_lock; } ;
typedef  TYPE_1__ pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int PTHREAD_MUTEX_NORMAL ; 
 int __pthread_mutex_timedlock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_cas (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __pthread_mutex_lock(pthread_mutex_t *m)
{
	if ((m->_m_type&15) == PTHREAD_MUTEX_NORMAL
	    && !a_cas(&m->_m_lock, 0, EBUSY))
		return 0;

	return __pthread_mutex_timedlock(m, 0);
}