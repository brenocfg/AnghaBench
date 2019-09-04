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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  ClearStr (char*,scalar_t__) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fqdn ; 
 int /*<<< orphan*/  current_fqdn_lock ; 

void GetCurrentDDnsFqdn(char *name, UINT size)
{
	ClearStr(name, size);
	// Validate arguments
	if (name == NULL || size == 0)
	{
		return;
	}

	Lock(current_fqdn_lock);
	{
		StrCpy(name, size, current_fqdn);
	}
	Unlock(current_fqdn_lock);

	Trim(name);
}