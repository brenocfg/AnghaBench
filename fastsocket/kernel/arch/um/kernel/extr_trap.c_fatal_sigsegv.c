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
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  do_signal () ; 
 int /*<<< orphan*/  force_sigsegv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_dump_core () ; 

void fatal_sigsegv(void)
{
	force_sigsegv(SIGSEGV, current);
	do_signal();
	/*
	 * This is to tell gcc that we're not returning - do_signal
	 * can, in general, return, but in this case, it's not, since
	 * we just got a fatal SIGSEGV queued.
	 */
	os_dump_core();
}