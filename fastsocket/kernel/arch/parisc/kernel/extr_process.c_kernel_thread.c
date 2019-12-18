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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  __kernel_thread (int (*) (void*),void*,unsigned long) ; 

pid_t kernel_thread(int (*fn)(void *), void *arg, unsigned long flags)
{

	/*
	 * FIXME: Once we are sure we don't need any debug here,
	 *	  kernel_thread can become a #define.
	 */

	return __kernel_thread(fn, arg, flags);
}