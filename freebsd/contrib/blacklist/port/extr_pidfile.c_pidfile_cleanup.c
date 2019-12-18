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
 scalar_t__ getpid () ; 
 int /*<<< orphan*/ * pidfile_path ; 
 scalar_t__ pidfile_pid ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pidfile_cleanup(void)
{

	if ((pidfile_path != NULL) && (pidfile_pid == getpid()))
		(void) unlink(pidfile_path);
}