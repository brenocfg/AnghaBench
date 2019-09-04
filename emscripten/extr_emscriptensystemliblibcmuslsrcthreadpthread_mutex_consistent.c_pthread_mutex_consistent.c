#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int _m_type; int _m_lock; } ;
typedef  TYPE_1__ pthread_mutex_t ;
struct TYPE_5__ {int tid; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 TYPE_3__* __pthread_self () ; 

int pthread_mutex_consistent(pthread_mutex_t *m)
{
	if (!(m->_m_type & 8)) return EINVAL;
	if ((m->_m_lock & 0x7fffffff) != __pthread_self()->tid)
		return EPERM;
	m->_m_type &= ~8U;
	return 0;
}