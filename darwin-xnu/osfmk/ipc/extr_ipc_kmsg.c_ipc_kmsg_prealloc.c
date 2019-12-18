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
typedef  scalar_t__ mach_msg_size_t ;
typedef  int /*<<< orphan*/  ipc_kmsg_t ;

/* Variables and functions */
 int /*<<< orphan*/  IKM_NULL ; 
 scalar_t__ LEGACY_HEADER_SIZE_DELTA ; 
 scalar_t__ MACH_MSG_SIZE_MAX ; 
 int /*<<< orphan*/  ipc_kmsg_alloc (scalar_t__) ; 

ipc_kmsg_t
ipc_kmsg_prealloc(mach_msg_size_t size)
{
#if defined(__LP64__)
	if (size > MACH_MSG_SIZE_MAX - LEGACY_HEADER_SIZE_DELTA)
		return IKM_NULL;

	size += LEGACY_HEADER_SIZE_DELTA;
#endif
	return ipc_kmsg_alloc(size);
}