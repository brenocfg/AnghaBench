#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_9__ {int StopAllLinkFlag; int /*<<< orphan*/  LinkList; } ;
struct TYPE_8__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ LINK ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__**) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseLink (TYPE_1__*) ; 
 int /*<<< orphan*/  StopLink (TYPE_1__*) ; 
 TYPE_1__** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void StopAllLink(HUB *h)
{
	LINK **link_list;
	UINT num_link;
	UINT i;
	// Validate arguments
	if (h == NULL)
	{
		return;
	}

	h->StopAllLinkFlag = true;

	LockList(h->LinkList);
	{
		link_list = ToArray(h->LinkList);
		num_link = LIST_NUM(h->LinkList);
		for (i = 0;i < num_link;i++)
		{
			AddRef(link_list[i]->ref);
		}
	}
	UnlockList(h->LinkList);

	for (i = 0;i < num_link;i++)
	{
		StopLink(link_list[i]);
		ReleaseLink(link_list[i]);
	}

	Free(link_list);

	h->StopAllLinkFlag = false;
}