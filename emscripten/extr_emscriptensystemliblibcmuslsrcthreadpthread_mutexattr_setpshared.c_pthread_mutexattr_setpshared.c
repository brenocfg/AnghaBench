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
struct TYPE_3__ {unsigned int __attr; } ;
typedef  TYPE_1__ pthread_mutexattr_t ;

/* Variables and functions */
 int EINVAL ; 

int pthread_mutexattr_setpshared(pthread_mutexattr_t *a, int pshared)
{
	if (pshared > 1U) return EINVAL;
	a->__attr &= ~128U;
	a->__attr |= pshared<<7;
	return 0;
}