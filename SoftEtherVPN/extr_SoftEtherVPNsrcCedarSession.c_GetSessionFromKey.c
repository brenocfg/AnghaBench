#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  HubList; } ;
struct TYPE_7__ {int /*<<< orphan*/  SessionList; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; int /*<<< orphan*/  SessionKey; } ;
typedef  TYPE_1__ SESSION ;
typedef  TYPE_2__ HUB ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

SESSION *GetSessionFromKey(CEDAR *cedar, UCHAR *session_key)
{
	HUB *h;
	UINT i, j;
	// Validate arguments
	if (cedar == NULL || session_key == NULL)
	{
		return NULL;
	}

	LockList(cedar->HubList);
	{
		for (i = 0;i < LIST_NUM(cedar->HubList);i++)
		{
			h = LIST_DATA(cedar->HubList, i);
			LockList(h->SessionList);
			{
				for (j = 0;j < LIST_NUM(h->SessionList);j++)
				{
					SESSION *s = LIST_DATA(h->SessionList, j);
					Lock(s->lock);
					{
						if (Cmp(s->SessionKey, session_key, SHA1_SIZE) == 0)
						{
							// Session found
							AddRef(s->ref);

							// Unlock
							Unlock(s->lock);
							UnlockList(h->SessionList);
							UnlockList(cedar->HubList);
							return s;
						}
					}
					Unlock(s->lock);
				}
			}
			UnlockList(h->SessionList);
		}
	}
	UnlockList(cedar->HubList);

	return NULL;
}