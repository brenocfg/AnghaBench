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
typedef  scalar_t__ thread_t ;

/* Variables and functions */
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  thread_reference_internal (scalar_t__) ; 

void
thread_reference(
	thread_t	thread)
{
	if (thread != THREAD_NULL)
		thread_reference_internal(thread);
}