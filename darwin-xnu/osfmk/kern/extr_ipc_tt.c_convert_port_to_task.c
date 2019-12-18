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
typedef  int /*<<< orphan*/  task_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  convert_port_to_task_with_exec_token (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

task_t
convert_port_to_task(
	ipc_port_t		port)
{
	return convert_port_to_task_with_exec_token(port, NULL);
}