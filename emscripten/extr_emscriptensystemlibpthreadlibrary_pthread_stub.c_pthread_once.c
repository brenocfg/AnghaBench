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
typedef  scalar_t__ pthread_once_t ;

/* Variables and functions */
 scalar_t__ PTHREAD_ONCE_MAGIC_ID ; 

int pthread_once(pthread_once_t *once_control, void (*init_routine)(void))
{
	if (*once_control != PTHREAD_ONCE_MAGIC_ID)
	{
		init_routine();
		*once_control = PTHREAD_ONCE_MAGIC_ID;
	}
}