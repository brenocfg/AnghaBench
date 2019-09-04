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
typedef  int /*<<< orphan*/  RPC_ADMIN_OPTION ;

/* Variables and functions */
 scalar_t__ GetHubAdminOptionData (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ INFINITE ; 

void GetHubAdminOptionDataAndSet(RPC_ADMIN_OPTION *ao, char *name, UINT *dest)
{
	UINT value;
	// Validate arguments
	if (ao == NULL || name == NULL || dest == NULL)
	{
		return;
	}

	value = GetHubAdminOptionData(ao, name);
	if (value == INFINITE)
	{
		return;
	}

	*dest = value;
}