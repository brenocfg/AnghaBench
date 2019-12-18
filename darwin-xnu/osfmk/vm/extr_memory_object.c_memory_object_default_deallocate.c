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
typedef  int /*<<< orphan*/  memory_object_default_t ;

/* Variables and functions */
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ ) ; 

void
memory_object_default_deallocate(
	memory_object_default_t dmm)
{
	ipc_port_release_send(dmm);
}