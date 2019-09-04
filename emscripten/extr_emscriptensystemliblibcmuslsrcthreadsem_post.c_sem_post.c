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
struct TYPE_3__ {int* __val; } ;
typedef  TYPE_1__ sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 int SEM_VALUE_MAX ; 
 int /*<<< orphan*/  __wake (int*,int,int) ; 
 int a_cas (int*,int,int) ; 
 int /*<<< orphan*/  errno ; 

int sem_post(sem_t *sem)
{
	int val, waiters, priv = sem->__val[2];
	do {
		val = sem->__val[0];
		waiters = sem->__val[1];
		if (val == SEM_VALUE_MAX) {
			errno = EOVERFLOW;
			return -1;
		}
	} while (a_cas(sem->__val, val, val+1+(val<0)) != val);
	if (val<0 || waiters) __wake(sem->__val, 1, priv);
	return 0;
}