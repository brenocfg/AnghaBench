#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
#define  PTHREAD_SCOPE_PROCESS 129 
#define  PTHREAD_SCOPE_SYSTEM 128 

int pthread_attr_setscope(pthread_attr_t *a, int scope)
{
	switch (scope) {
	case PTHREAD_SCOPE_SYSTEM:
		return 0;
	case PTHREAD_SCOPE_PROCESS:
		return ENOTSUP;
	default:
		return EINVAL;
	}
}