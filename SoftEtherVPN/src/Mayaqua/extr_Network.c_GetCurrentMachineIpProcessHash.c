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
 int /*<<< orphan*/  Copy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentMachineIpProcessHashInternal (int /*<<< orphan*/ ) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_ip_process_hash ; 
 int /*<<< orphan*/  machine_ip_process_hash_lock ; 

void GetCurrentMachineIpProcessHash(void *hash)
{
	// Validate arguments
	if (hash == NULL)
	{
		return;
	}

	Lock(machine_ip_process_hash_lock);
	{
		if (IsZero(machine_ip_process_hash, SHA1_SIZE))
		{
			GetCurrentMachineIpProcessHashInternal(machine_ip_process_hash);
		}

		Copy(hash, machine_ip_process_hash, SHA1_SIZE);
	}
	Unlock(machine_ip_process_hash_lock);
}