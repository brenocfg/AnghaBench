#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  AccountName; } ;
struct TYPE_15__ {int /*<<< orphan*/  lock; TYPE_6__* ClientOption; int /*<<< orphan*/ * ClientSession; } ;
struct TYPE_14__ {int /*<<< orphan*/  AccountList; } ;
struct TYPE_13__ {int /*<<< orphan*/  NewName; int /*<<< orphan*/  OldName; } ;
typedef  TYPE_1__ RPC_RENAME_ACCOUNT ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  TYPE_2__ CLIENT ;
typedef  TYPE_3__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  CLog (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiNotify (TYPE_2__*) ; 
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_2__*) ; 
 int /*<<< orphan*/  CiSetError (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_ACCOUNT_ACTIVE ; 
 int /*<<< orphan*/  ERR_ACCOUNT_ALREADY_EXISTS ; 
 int /*<<< orphan*/  ERR_ACCOUNT_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_INVALID_VALUE ; 
 int /*<<< orphan*/  Free (TYPE_6__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_3__* Search (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  Sort (int /*<<< orphan*/ ) ; 
 scalar_t__ UniStrCmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ UniStrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 

bool CtRenameAccount(CLIENT *c, RPC_RENAME_ACCOUNT *rename, bool inner)
{
	bool ret;
	// Validate arguments
	if (c == NULL || rename == NULL)
	{
		return false;
	}


	ret = false;

	if (UniStrCmp(rename->NewName, rename->OldName) == 0)
	{
		// The name has not been changed
		return true;
	}

	LockList(c->AccountList);
	{
		ACCOUNT t, *r, *r2;

		if (UniStrLen(rename->NewName) == 0)
		{
			// Name is invalid
			CiSetError(c, ERR_INVALID_VALUE);
			UnlockList(c->AccountList);
			return false;
		}

		// Search for old account name
		t.ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
		UniStrCpy(t.ClientOption->AccountName, sizeof(t.ClientOption->AccountName), rename->OldName);

		r = Search(c->AccountList, &t);
		if (r == NULL)
		{
			// Specified account can not be found
			UnlockList(c->AccountList);

			Free(t.ClientOption);
			CiSetError(c, ERR_ACCOUNT_NOT_FOUND);
			return false;
		}

		Free(t.ClientOption);

		// Search for a new account name
		t.ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
		UniStrCpy(t.ClientOption->AccountName, sizeof(t.ClientOption->AccountName), rename->NewName);

		r2 = Search(c->AccountList, &t);
		if (r2 != NULL)
		{
			// Account with the specified name already exists
			UnlockList(c->AccountList);

			Free(t.ClientOption);
			CiSetError(c, ERR_ACCOUNT_ALREADY_EXISTS);
			return false;
		}

		Free(t.ClientOption);

		Lock(r->lock);
		{
			// Check the operating state of the account
			if (r->ClientSession != NULL)
			{
				// The Account is working
				Unlock(r->lock);
				UnlockList(c->AccountList);
				CiSetError(c, ERR_ACCOUNT_ACTIVE);

				return false;
			}

			// Update the account name
			UniStrCpy(r->ClientOption->AccountName, sizeof(r->ClientOption->AccountName),
				rename->NewName);

			CLog(c, "LC_RENAME_ACCOUNT", rename->OldName, rename->NewName);

			ret = true;
		}
		Unlock(r->lock);

		Sort(c->AccountList);

	}
	UnlockList(c->AccountList);

	CiSaveConfigurationFile(c);

	CiNotify(c);

	return ret;
}