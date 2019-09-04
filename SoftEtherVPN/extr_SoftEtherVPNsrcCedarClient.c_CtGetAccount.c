#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  AccountName; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  UpdateDateTime; int /*<<< orphan*/  LastConnectDateTime; int /*<<< orphan*/  CreateDateTime; TYPE_6__* ShortcutKey; int /*<<< orphan*/ * ServerCert; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  ClientAuth; TYPE_6__* ClientOption; } ;
struct TYPE_13__ {int /*<<< orphan*/  AccountList; } ;
struct TYPE_12__ {int /*<<< orphan*/  UpdateDateTime; int /*<<< orphan*/  LastConnectDateTime; int /*<<< orphan*/  CreateDateTime; TYPE_6__* ShortcutKey; int /*<<< orphan*/ * ServerCert; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/ * ClientAuth; TYPE_6__* ClientOption; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ RPC_CLIENT_GET_ACCOUNT ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  TYPE_2__ CLIENT ;
typedef  TYPE_3__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  CiFreeClientAuth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiSetError (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CloneX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (TYPE_6__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/ * CopyClientAuth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_ACCOUNT_NOT_FOUND ; 
 int /*<<< orphan*/  Free (TYPE_6__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int SHA1_SIZE ; 
 TYPE_3__* Search (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 

bool CtGetAccount(CLIENT *c, RPC_CLIENT_GET_ACCOUNT *a)
{
	// Validate arguments
	if (c == NULL || a == NULL)
	{
		return false;
	}

	LockList(c->AccountList);
	{
		ACCOUNT t, *r;

		// Search for account
		t.ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
		UniStrCpy(t.ClientOption->AccountName, sizeof(t.ClientOption->AccountName), a->AccountName);

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

		Lock(r->lock);
		{
			// Copy the client option
			if (a->ClientOption != NULL)
			{
				Free(a->ClientOption);
			}
			a->ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
			Copy(a->ClientOption, r->ClientOption, sizeof(CLIENT_OPTION));

			// Copy the authentication data
			if (a->ClientAuth != NULL)
			{
				CiFreeClientAuth(a->ClientAuth);
			}
			a->ClientAuth = CopyClientAuth(r->ClientAuth);

			a->StartupAccount = r->StartupAccount;

			a->CheckServerCert = r->CheckServerCert;
			a->RetryOnServerCert = r->RetryOnServerCert;
			a->ServerCert = NULL;
			if (r->ServerCert != NULL)
			{
				a->ServerCert = CloneX(r->ServerCert);
			}

			// Shortcut Key
			Copy(a->ShortcutKey, r->ShortcutKey, SHA1_SIZE);

			a->CreateDateTime = r->CreateDateTime;
			a->LastConnectDateTime = r->LastConnectDateTime;
			a->UpdateDateTime = r->UpdateDateTime;
		}
		Unlock(r->lock);

	}
	UnlockList(c->AccountList);

	return true;
}