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
typedef  int /*<<< orphan*/  X ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {TYPE_1__* HubDb; } ;
struct TYPE_4__ {int /*<<< orphan*/  RootCertList; } ;
typedef  TYPE_1__ HUBDB ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  CloneX (int /*<<< orphan*/ *) ; 
 scalar_t__ CompareX (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_HUB_CERTS ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void AddRootCert(HUB *hub, X *x)
{
	HUBDB *db;
	// Validate arguments
	if (hub == NULL || x == NULL)
	{
		return;
	}

	db = hub->HubDb;
	if (db != NULL)
	{
		LockList(db->RootCertList);
		{
			if (LIST_NUM(db->RootCertList) < MAX_HUB_CERTS)
			{
				UINT i;
				bool ok = true;

				for (i = 0;i < LIST_NUM(db->RootCertList);i++)
				{
					X *exist_x = LIST_DATA(db->RootCertList, i);
					if (CompareX(exist_x, x))
					{
						ok = false;
						break;
					}
				}

				if (ok)
				{
					Insert(db->RootCertList, CloneX(x));
				}
			}
		}
		UnlockList(db->RootCertList);
	}
}