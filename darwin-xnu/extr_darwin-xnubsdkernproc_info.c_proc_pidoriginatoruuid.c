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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int proc_pidoriginatorpid_uuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
proc_pidoriginatoruuid(uuid_t uuid, uint32_t buffersize)
{
	pid_t originator_pid;
	return (proc_pidoriginatorpid_uuid(uuid, buffersize, &originator_pid));
}