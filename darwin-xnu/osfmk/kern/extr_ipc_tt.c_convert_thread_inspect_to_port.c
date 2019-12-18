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
typedef  int /*<<< orphan*/  thread_inspect_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  IP_NULL ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 

ipc_port_t
convert_thread_inspect_to_port(thread_inspect_t thread)
{
	thread_deallocate(thread);
	return IP_NULL;
}