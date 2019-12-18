#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  HubList; } ;
struct TYPE_7__ {scalar_t__ RadiusConvertAllMsChapv2AuthRequestToEap; } ;
typedef  TYPE_1__ HUB ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (TYPE_2__*) ; 
 int /*<<< orphan*/  UnlockHubList (TYPE_2__*) ; 

bool CedarIsThereAnyEapEnabledRadiusConfig(CEDAR *c)
{
	bool ret = false;
	UINT i;
	if (c == NULL)
	{
		return false;
	}

	LockHubList(c);
	{
		for (i = 0;i < LIST_NUM(c->HubList);i++)
		{
			HUB *hub = LIST_DATA(c->HubList, i);

			if (hub->RadiusConvertAllMsChapv2AuthRequestToEap)
			{
				ret = true;
				break;
			}
		}
	}
	UnlockHubList(c);

	return ret;
}