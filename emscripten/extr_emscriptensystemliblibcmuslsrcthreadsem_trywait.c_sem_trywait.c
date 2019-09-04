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
 int /*<<< orphan*/  EAGAIN ; 
 int a_cas (int*,int,int) ; 
 int /*<<< orphan*/  errno ; 

int sem_trywait(sem_t *sem)
{
	int val;
	while ((val=sem->__val[0]) > 0) {
		int new = val-1-(val==1 && sem->__val[1]);
		if (a_cas(sem->__val, val, new)==val) return 0;
	}
	errno = EAGAIN;
	return -1;
}