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
typedef  int /*<<< orphan*/  sthread_t ;

/* Variables and functions */
 int /*<<< orphan*/ * sthread_create_with_priority (void (*) (void*),void*,int /*<<< orphan*/ ) ; 

sthread_t *sthread_create(void (*thread_func)(void*), void *userdata)
{
	return sthread_create_with_priority(thread_func, userdata, 0);
}