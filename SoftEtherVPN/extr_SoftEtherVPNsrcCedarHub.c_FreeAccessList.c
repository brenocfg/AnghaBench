#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/ * AccessList; } ;
typedef  TYPE_1__ HUB ;
typedef  int /*<<< orphan*/  ACCESS ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void FreeAccessList(HUB *hub)
{
	UINT i;
	// Validate arguments
	if (hub == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(hub->AccessList);i++)
	{
		ACCESS *a = LIST_DATA(hub->AccessList, i);
		Free(a);
	}

	ReleaseList(hub->AccessList);
	hub->AccessList = NULL;
}