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
struct TYPE_3__ {scalar_t__ _a_stacksize; scalar_t__ _a_stackaddr; } ;
typedef  TYPE_1__ pthread_attr_t ;

/* Variables and functions */
 scalar_t__ DEFAULT_STACK_SIZE ; 
 int EINVAL ; 
 size_t PTHREAD_STACK_MIN ; 
 int SIZE_MAX ; 

int pthread_attr_setstacksize(pthread_attr_t *a, size_t size)
{
	if (size-PTHREAD_STACK_MIN > SIZE_MAX/4) return EINVAL;
	a->_a_stackaddr = 0;
	a->_a_stacksize = size - DEFAULT_STACK_SIZE;
	return 0;
}