#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  AccountName; } ;
struct TYPE_15__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ClientSession; TYPE_4__* ClientOption; } ;
struct TYPE_14__ {int /*<<< orphan*/  AccountList; } ;
struct TYPE_13__ {int /*<<< orphan*/  AccountName; } ;
typedef  int /*<<< orphan*/  SESSION ;
typedef  TYPE_1__ RPC_CLIENT_GET_CONNECTION_STATUS ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  TYPE_2__ CLIENT ;
typedef  TYPE_3__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  CiGetSessionStatus (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiSetError (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_ACCOUNT_NOT_FOUND ; 
 int /*<<< orphan*/  Free (TYPE_4__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_3__* Search (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 TYPE_4__* ZeroMalloc (int) ; 

bool CtGetAccountStatus(CLIENT *c, RPC_CLIENT_GET_CONNECTION_STATUS *st)
{
	// Validate arguments
	if (c == NULL || st == NULL)
	{
		return false;
	}

	LockList(c->AccountList);
	{
		ACCOUNT t, *r;

		// Search for account
		t.ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
		UniStrCpy(t.ClientOption->AccountName, sizeof(t.ClientOption->AccountName), st->AccountName);

		r = Search(c->AccountList, &t);
		if (r == NULL)
		{
			// Specified account is not found
			UnlockList(c->AccountList);

			Free(t.ClientOption);
			CiSetError(c, ERR_ACCOUNT_NOT_FOUND);
			return false;
		}

		Free(t.ClientOption);

		Lock(r->lock);
		{
			Zero(st, sizeof(RPC_CLIENT_GET_CONNECTION_STATUS));
			if (r->ClientSession != NULL)
			{
				SESSION *s = r->ClientSession;
				CiGetSessionStatus(st, s);
			}
		}
		Unlock(r->lock);
	}
	UnlockList(c->AccountList);

	return true;
}