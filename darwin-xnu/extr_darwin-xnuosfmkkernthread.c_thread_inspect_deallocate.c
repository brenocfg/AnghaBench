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
typedef  int /*<<< orphan*/  thread_t ;
typedef  scalar_t__ thread_inspect_t ;

/* Variables and functions */
 void thread_deallocate (int /*<<< orphan*/ ) ; 

void
thread_inspect_deallocate(
	thread_inspect_t		thread_inspect)
{
	return(thread_deallocate((thread_t)thread_inspect));
}