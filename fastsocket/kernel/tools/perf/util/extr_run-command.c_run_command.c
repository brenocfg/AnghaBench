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
struct child_process {int dummy; } ;

/* Variables and functions */
 int finish_command (struct child_process*) ; 
 int start_command (struct child_process*) ; 

int run_command(struct child_process *cmd)
{
	int code = start_command(cmd);
	if (code)
		return code;
	return finish_command(cmd);
}