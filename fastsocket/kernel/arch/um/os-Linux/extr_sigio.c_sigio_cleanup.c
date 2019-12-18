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
 int /*<<< orphan*/  free_stack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_kill_process (int,int) ; 
 int write_sigio_pid ; 
 int /*<<< orphan*/  write_sigio_stack ; 

__attribute__((used)) static void sigio_cleanup(void)
{
	if (write_sigio_pid == -1)
		return;

	os_kill_process(write_sigio_pid, 1);
	free_stack(write_sigio_stack, 0);
	write_sigio_pid = -1;
}