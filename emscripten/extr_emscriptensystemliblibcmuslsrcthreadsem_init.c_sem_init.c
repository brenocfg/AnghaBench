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
struct TYPE_3__ {unsigned int* __val; } ;
typedef  TYPE_1__ sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 unsigned int SEM_VALUE_MAX ; 
 int /*<<< orphan*/  errno ; 

int sem_init(sem_t *sem, int pshared, unsigned value)
{
	if (value > SEM_VALUE_MAX) {
		errno = EINVAL;
		return -1;
	}
	sem->__val[0] = value;
	sem->__val[1] = 0;
	sem->__val[2] = pshared ? 0 : 128;
	return 0;
}