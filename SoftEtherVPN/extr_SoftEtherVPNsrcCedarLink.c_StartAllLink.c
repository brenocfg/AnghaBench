#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  LinkList; } ;
struct TYPE_5__ {int Offline; } ;
typedef  TYPE_1__ LINK ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 scalar_t__ LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartLink (TYPE_1__*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void StartAllLink(HUB *h)
{
	// Validate arguments
	if (h == NULL)
	{
		return;
	}

	LockList(h->LinkList);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(h->LinkList);i++)
		{
			LINK *k = (LINK *)LIST_DATA(h->LinkList, i);

			if (k->Offline == false)
			{
				StartLink(k);
			}
		}
	}
	UnlockList(h->LinkList);
}