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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  memory_entry_access_tracking_internal (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

kern_return_t
mach_memory_entry_access_tracking(
	ipc_port_t	entry_port,
	int		*access_tracking,
	uint32_t	*access_tracking_reads,
	uint32_t	*access_tracking_writes)
{
	return memory_entry_access_tracking_internal(entry_port,
						     access_tracking,
						     access_tracking_reads,
						     access_tracking_writes);
}