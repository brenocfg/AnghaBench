#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {size_t Value; int /*<<< orphan*/  Name; } ;
struct TYPE_4__ {size_t NumItem; TYPE_2__* Items; } ;
typedef  TYPE_1__ RPC_ADMIN_OPTION ;
typedef  TYPE_2__ ADMIN_OPTION ;

/* Variables and functions */
 size_t INFINITE ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 

UINT GetHubAdminOptionData(RPC_ADMIN_OPTION *ao, char *name)
{
	UINT i;
	// Validate arguments
	if (ao == NULL || name == NULL)
	{
		return INFINITE;
	}

	for (i = 0;i < ao->NumItem;i++)
	{
		ADMIN_OPTION *a = &ao->Items[i];

		if (StrCmpi(a->Name, name) == 0)
		{
			return a->Value;
		}
	}

	return INFINITE;
}