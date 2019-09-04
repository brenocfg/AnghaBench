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
struct TYPE_3__ {int _a_policy; } ;
typedef  TYPE_1__ pthread_attr_t ;

/* Variables and functions */

int pthread_attr_getschedpolicy(const pthread_attr_t *restrict a, int *restrict policy)
{
	*policy = a->_a_policy;
	return 0;
}