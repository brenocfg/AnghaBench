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
struct TYPE_3__ {int __attr; } ;
typedef  TYPE_1__ pthread_condattr_t ;

/* Variables and functions */

int pthread_condattr_getpshared(const pthread_condattr_t *restrict a, int *restrict pshared)
{
	*pshared = a->__attr>>31;
	return 0;
}