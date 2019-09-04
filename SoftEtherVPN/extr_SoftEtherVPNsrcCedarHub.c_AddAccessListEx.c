#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_12__ {int IsSrcUsernameIncludeOrExclude; int IsDestUsernameIncludeOrExclude; scalar_t__ SrcPortStart; scalar_t__ DestPortStart; scalar_t__ Id; void* Loss; void* Jitter; void* Delay; void* DestPortEnd; void* SrcPortEnd; int /*<<< orphan*/  DestUsername; void* DestUsernameHash; int /*<<< orphan*/  SrcUsername; void* SrcUsernameHash; } ;
struct TYPE_11__ {int /*<<< orphan*/  AccessList; } ;
typedef  TYPE_1__ HUB ;
typedef  TYPE_2__ ACCESS ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_LIST_EXCLUDED_PREFIX ; 
 int /*<<< orphan*/  ACCESS_LIST_INCLUDED_PREFIX ; 
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Copy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  HUB_ACCESSLIST_DELAY_MAX ; 
 int /*<<< orphan*/  HUB_ACCESSLIST_JITTER_MAX ; 
 int /*<<< orphan*/  HUB_ACCESSLIST_LOSS_MAX ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int IsEmptyStr (int /*<<< orphan*/ ) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 void* MAKESURE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* MAX (void*,scalar_t__) ; 
 scalar_t__ MAX_ACCESSLISTS ; 
 int /*<<< orphan*/  MakeSimpleUsernameRemoveNtDomain (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* Malloc (int) ; 
 int StartWith (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 void* UsernameToInt64 (int /*<<< orphan*/ ) ; 

void AddAccessListEx(HUB *hub, ACCESS *a, bool no_sort, bool no_reassign_id)
{
	// Validate arguments
	if (hub == NULL || a == NULL)
	{
		return;
	}

	LockList(hub->AccessList);
	{
		ACCESS *access;
		UINT i;

		// Check the number of items
		if (LIST_NUM(hub->AccessList) >= MAX_ACCESSLISTS)
		{
			UnlockList(hub->AccessList);
			return;
		}

		access = Malloc(sizeof(ACCESS));
		Copy(access, a, sizeof(ACCESS));

		access->IsSrcUsernameIncludeOrExclude = false;
		access->IsDestUsernameIncludeOrExclude = false;

		// User name correction
		if (IsEmptyStr(access->SrcUsername) == false)
		{
			if (StartWith(access->SrcUsername, ACCESS_LIST_INCLUDED_PREFIX) == false && StartWith(access->SrcUsername, ACCESS_LIST_EXCLUDED_PREFIX) == false)
			{
				MakeSimpleUsernameRemoveNtDomain(access->SrcUsername, sizeof(access->SrcUsername), access->SrcUsername);
			}
			else
			{
				access->IsSrcUsernameIncludeOrExclude = true;
			}
		}
		if (IsEmptyStr(access->DestUsername) == false)
		{
			if (StartWith(access->DestUsername, ACCESS_LIST_INCLUDED_PREFIX) == false && StartWith(access->DestUsername, ACCESS_LIST_EXCLUDED_PREFIX) == false)
			{
				MakeSimpleUsernameRemoveNtDomain(access->DestUsername, sizeof(access->DestUsername), access->DestUsername);
			}
			else
			{
				access->IsDestUsernameIncludeOrExclude = true;
			}
		}

		access->SrcUsernameHash = UsernameToInt64(access->SrcUsername);
		access->DestUsernameHash = UsernameToInt64(access->DestUsername);

		// Port number correction
		if (access->SrcPortStart != 0)
		{
			access->SrcPortEnd = MAX(access->SrcPortEnd, access->SrcPortStart);
		}
		if (access->DestPortStart != 0)
		{
			access->DestPortEnd = MAX(access->DestPortEnd, access->DestPortStart);
		}

		// Correct delay, jitter, and packet loss
		access->Delay = MAKESURE(access->Delay, 0, HUB_ACCESSLIST_DELAY_MAX);
		access->Jitter = MAKESURE(access->Jitter, 0, HUB_ACCESSLIST_JITTER_MAX);
		access->Loss = MAKESURE(access->Loss, 0, HUB_ACCESSLIST_LOSS_MAX);

		if (no_sort == false)
		{
			Insert(hub->AccessList, access);
		}
		else
		{
			Add(hub->AccessList, access);
		}

		// Reassign the ID
		if (no_reassign_id == false)
		{
			for (i = 0;i < LIST_NUM(hub->AccessList);i++)
			{
				ACCESS *a = LIST_DATA(hub->AccessList, i);
				a->Id = (i + 1);
			}
		}
	}
	UnlockList(hub->AccessList);
}