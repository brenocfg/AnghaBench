#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  TYPE_1__* clock_t ;
struct TYPE_3__ {int /*<<< orphan*/  cl_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipc_port_make_send (int /*<<< orphan*/ ) ; 

ipc_port_t
convert_clock_ctrl_to_port(
	clock_t		clock)
{
	ipc_port_t	port;

	port = ipc_port_make_send(clock->cl_control);
	return (port);
}