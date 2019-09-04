#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_13__ {int /*<<< orphan*/  lock; TYPE_1__* ClientOption; } ;
struct TYPE_12__ {int /*<<< orphan*/  AccountList; } ;
struct TYPE_11__ {int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_2__ CLIENT ;
typedef  TYPE_3__ ACCOUNT ;

/* Variables and functions */
 char* CiGetFirstVLan (TYPE_2__*) ; 
 int CiIsVLan (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiNotify (TYPE_2__*) ; 
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_2__*) ; 
 int /*<<< orphan*/  CiSendGlobalPulse (TYPE_2__*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void CiNormalizeAccountVLan(CLIENT *c)
{
	bool b = false;
	char *name;
	UINT i;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	name = CiGetFirstVLan(c);

	if (name != NULL)
	{
		LockList(c->AccountList);
		{
			for (i = 0;i < LIST_NUM(c->AccountList);i++)
			{
				ACCOUNT *a = LIST_DATA(c->AccountList, i);

				Lock(a->lock);
				{
					if (a->ClientOption != NULL)
					{
						if (CiIsVLan(c, a->ClientOption->DeviceName) == false)
						{
							StrCpy(a->ClientOption->DeviceName, sizeof(a->ClientOption->DeviceName),
								name);
							b = true;
						}
					}
				}
				Unlock(a->lock);
			}
		}
		UnlockList(c->AccountList);

		Free(name);
	}

	if (b)
	{
		CiNotify(c);
		CiSendGlobalPulse(c);
		CiSaveConfigurationFile(c);
	}
}