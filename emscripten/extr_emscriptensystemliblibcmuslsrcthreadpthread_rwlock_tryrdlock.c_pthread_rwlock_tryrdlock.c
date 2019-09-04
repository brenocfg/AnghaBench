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
struct TYPE_3__ {int _rw_lock; } ;
typedef  TYPE_1__ pthread_rwlock_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int a_cas (int*,int,int) ; 

int pthread_rwlock_tryrdlock(pthread_rwlock_t *rw)
{
	int val, cnt;
	do {
		val = rw->_rw_lock;
		cnt = val & 0x7fffffff;
		if (cnt == 0x7fffffff) return EBUSY;
		if (cnt == 0x7ffffffe) return EAGAIN;
	} while (a_cas(&rw->_rw_lock, val, val+1) != val);
	return 0;
}