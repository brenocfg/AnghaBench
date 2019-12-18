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
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/  MaintenanceDaemonShmemInit ; 
 int /*<<< orphan*/  MaintenanceDaemonShmemSize () ; 
 int /*<<< orphan*/  RequestAddinShmemSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prev_shmem_startup_hook ; 
 int /*<<< orphan*/  shmem_startup_hook ; 

void
InitializeMaintenanceDaemon(void)
{
	if (!IsUnderPostmaster)
	{
		RequestAddinShmemSpace(MaintenanceDaemonShmemSize());
	}

	prev_shmem_startup_hook = shmem_startup_hook;
	shmem_startup_hook = MaintenanceDaemonShmemInit;
}