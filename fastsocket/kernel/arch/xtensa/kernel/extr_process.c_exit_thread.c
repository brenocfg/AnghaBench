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

/* Variables and functions */
 int /*<<< orphan*/  coprocessor_release_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread_info () ; 

void exit_thread(void)
{
#if XTENSA_HAVE_COPROCESSORS
	coprocessor_release_all(current_thread_info());
#endif
}