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
 int /*<<< orphan*/  do_uml_exitcalls () ; 
 int /*<<< orphan*/  kill_off_processes () ; 
 scalar_t__ kmalloc_ok ; 

void uml_cleanup(void)
{
	kmalloc_ok = 0;
	do_uml_exitcalls();
	kill_off_processes();
}