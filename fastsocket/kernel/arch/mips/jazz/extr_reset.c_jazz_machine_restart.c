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
 int /*<<< orphan*/  jazz_write_command (int) ; 
 int /*<<< orphan*/  jazz_write_output (int) ; 
 int /*<<< orphan*/  kb_wait () ; 

void jazz_machine_restart(char *command)
{
	while(1) {
		kb_wait();
		jazz_write_command(0xd1);
		kb_wait();
		jazz_write_output(0x00);
	}
}