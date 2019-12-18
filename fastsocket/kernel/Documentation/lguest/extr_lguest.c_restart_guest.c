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
 unsigned int FD_SETSIZE ; 
 int /*<<< orphan*/  cleanup_devices () ; 
 int /*<<< orphan*/  close (unsigned int) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * main_args ; 

__attribute__((used)) static void __attribute__((noreturn)) restart_guest(void)
{
	unsigned int i;

	/*
	 * Since we don't track all open fds, we simply close everything beyond
	 * stderr.
	 */
	for (i = 3; i < FD_SETSIZE; i++)
		close(i);

	/* Reset all the devices (kills all threads). */
	cleanup_devices();

	execv(main_args[0], main_args);
	err(1, "Could not exec %s", main_args[0]);
}