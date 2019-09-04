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
struct TYPE_3__ {size_t _a_guardsize; } ;
typedef  TYPE_1__ pthread_attr_t ;

/* Variables and functions */
 size_t DEFAULT_GUARD_SIZE ; 

int pthread_attr_getguardsize(const pthread_attr_t *restrict a, size_t *restrict size)
{
	*size = a->_a_guardsize + DEFAULT_GUARD_SIZE;
	return 0;
}