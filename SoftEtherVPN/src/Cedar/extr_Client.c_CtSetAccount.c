#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  AccountName; } ;
struct TYPE_23__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  UpdateDateTime; int /*<<< orphan*/ * ServerCert; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  StartupAccount; TYPE_7__* ClientOption; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/ * ClientSession; } ;
struct TYPE_22__ {int /*<<< orphan*/  AccountList; } ;
struct TYPE_21__ {TYPE_13__* ServerCert; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  StartupAccount; TYPE_12__* ClientOption; TYPE_10__* ClientAuth; } ;
struct TYPE_20__ {int is_compatible_bit; } ;
struct TYPE_19__ {int is_compatible_bit; } ;
struct TYPE_18__ {int /*<<< orphan*/  AccountName; } ;
struct TYPE_17__ {scalar_t__ AuthType; int /*<<< orphan*/ * ClientK; TYPE_1__* ClientX; } ;
typedef  TYPE_2__ RPC_CLIENT_CREATE_ACCOUNT ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  TYPE_3__ CLIENT ;
typedef  TYPE_4__ ACCOUNT ;

/* Variables and functions */
 scalar_t__ CLIENT_AUTHTYPE_CERT ; 
 int /*<<< orphan*/  CiFreeClientAuth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiNotify (TYPE_3__*) ; 
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_3__*) ; 
 int /*<<< orphan*/  CiSetError (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CloneX (TYPE_13__*) ; 
 int /*<<< orphan*/  Copy (TYPE_7__*,TYPE_12__*,int) ; 
 int /*<<< orphan*/  CopyClientAuth (TYPE_10__*) ; 
 int /*<<< orphan*/  ERR_ACCOUNT_ACTIVE ; 
 int /*<<< orphan*/  ERR_ACCOUNT_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_NOT_RSA_1024 ; 
 int /*<<< orphan*/  Free (TYPE_7__*) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_4__* Search (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  SystemTime64 () ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 

bool CtSetAccount(CLIENT *c, RPC_CLIENT_CREATE_ACCOUNT *a, bool inner)
{
	// Validate arguments
	if (c == NULL || a == NULL)
	{
		return false;
	}


	// Check whether an account already exists
	LockList(c->AccountList);
	{
		ACCOUNT t, *ret;
		t.ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
		UniStrCpy(t.ClientOption->AccountName, sizeof(t.ClientOption->AccountName),
			a->ClientOption->AccountName);

		ret = Search(c->AccountList, &t);
		if (ret == NULL)
		{
			// Not exist
			UnlockList(c->AccountList);
			Free(t.ClientOption);

			CiSetError(c, ERR_ACCOUNT_NOT_FOUND);

			return false;
		}
		Free(t.ClientOption);

		if (a->ClientAuth->AuthType == CLIENT_AUTHTYPE_CERT)
		{
			if (a->ClientAuth->ClientX == NULL ||
				a->ClientAuth->ClientX->is_compatible_bit == false ||
				a->ClientAuth->ClientK == NULL)
			{
				// Client certificate is invalid
				UnlockList(c->AccountList);
				CiSetError(c, ERR_NOT_RSA_1024);
				return false;
			}
		}

		if (a->ServerCert != NULL && a->ServerCert->is_compatible_bit == false)
		{
			// Server certificate is invalid
			UnlockList(c->AccountList);
			CiSetError(c, ERR_NOT_RSA_1024);
			return false;
		}

		Lock(ret->lock);
		{

#if	0
			// Rewriting of the configuration is done even account running in the current version
			// (New setting isn't applied until connecting next time)
			if (ret->ClientSession != NULL)
			{
				// The account is operating
				Unlock(ret->lock);
				UnlockList(c->AccountList);

				CiSetError(c, ERR_ACCOUNT_ACTIVE);

				return false;
			}
#endif

			// Delete the client authentication data
			CiFreeClientAuth(ret->ClientAuth);

			// Copy the client authentication data
			ret->ClientAuth = CopyClientAuth(a->ClientAuth);

			// Delete the client option
			Free(ret->ClientOption);

			// Copy the client option
			ret->ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
			Copy(ret->ClientOption, a->ClientOption, sizeof(CLIENT_OPTION));

			ret->StartupAccount = a->StartupAccount;

			ret->CheckServerCert = a->CheckServerCert;
			ret->RetryOnServerCert = a->RetryOnServerCert;

			if (a->ServerCert != NULL)
			{
				if (ret->ServerCert != NULL)
				{
					FreeX(ret->ServerCert);
				}
				ret->ServerCert = CloneX(a->ServerCert);
			}
			else
			{
				if (ret->ServerCert != NULL)
				{
					FreeX(ret->ServerCert);
				}
				ret->ServerCert = false;
			}

			ret->UpdateDateTime = SystemTime64();
		}
		Unlock(ret->lock);
	}
	UnlockList(c->AccountList);

	CiSaveConfigurationFile(c);

	CiNotify(c);

	return true;
}