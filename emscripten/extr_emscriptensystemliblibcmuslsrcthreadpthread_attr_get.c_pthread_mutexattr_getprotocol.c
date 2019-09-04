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
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;

/* Variables and functions */
 int PTHREAD_PRIO_NONE ; 

int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *restrict a, int *restrict protocol)
{
	*protocol = PTHREAD_PRIO_NONE;
	return 0;
}