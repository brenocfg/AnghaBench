#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_13__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  AccountName; } ;
struct TYPE_28__ {int /*<<< orphan*/  AccountName; } ;
struct TYPE_27__ {int /*<<< orphan*/  UpdateDateTime; int /*<<< orphan*/  CreateDateTime; TYPE_7__* ShortcutKey; int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  StartupAccount; TYPE_7__* ClientOption; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  lock; } ;
struct TYPE_26__ {int /*<<< orphan*/  AccountList; } ;
struct TYPE_25__ {TYPE_8__* ClientOption; TYPE_8__* ShortcutKey; TYPE_16__* ServerCert; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  StartupAccount; TYPE_13__* ClientAuth; } ;
struct TYPE_24__ {int is_compatible_bit; } ;
struct TYPE_23__ {int is_compatible_bit; } ;
struct TYPE_22__ {scalar_t__ AuthType; int /*<<< orphan*/ * ClientK; TYPE_1__* ClientX; } ;
typedef  TYPE_2__ RPC_CLIENT_CREATE_ACCOUNT ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  TYPE_3__ CLIENT ;
typedef  TYPE_4__ ACCOUNT ;

/* Variables and functions */
 scalar_t__ CLIENT_AUTHTYPE_CERT ; 
 int /*<<< orphan*/  CLog (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiNormalizeAccountVLan (TYPE_3__*) ; 
 int /*<<< orphan*/  CiNotify (TYPE_3__*) ; 
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_3__*) ; 
 int /*<<< orphan*/  CiSetError (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloneX (TYPE_16__*) ; 
 int /*<<< orphan*/  Copy (TYPE_7__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  CopyClientAuth (TYPE_13__*) ; 
 int /*<<< orphan*/  ERR_ACCOUNT_ALREADY_EXISTS ; 
 int /*<<< orphan*/  ERR_INVALID_VALUE ; 
 int /*<<< orphan*/  ERR_NOT_RSA_1024 ; 
 int /*<<< orphan*/  Free (TYPE_7__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ IsZero (TYPE_8__*,int) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  Rand (TYPE_7__*,int) ; 
 int SHA1_SIZE ; 
 TYPE_4__* Search (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  SystemTime64 () ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ UniStrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 

bool CtCreateAccount(CLIENT *c, RPC_CLIENT_CREATE_ACCOUNT *a, bool inner)
{
	// Validate arguments
	if (c == NULL || a == NULL)
	{
		return false;
	}


	// Check whether an account already exists
	LockList(c->AccountList);
	{
		ACCOUNT t, *ret, *new_account;
		t.ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
		UniStrCpy(t.ClientOption->AccountName, sizeof(t.ClientOption->AccountName),
			a->ClientOption->AccountName);

		ret = Search(c->AccountList, &t);
		if (ret != NULL)
		{
			// Already exist
			UnlockList(c->AccountList);
			Free(t.ClientOption);

			CiSetError(c, ERR_ACCOUNT_ALREADY_EXISTS);

			return false;
		}

		Free(t.ClientOption);

		if (UniStrLen(a->ClientOption->AccountName) == 0)
		{
			// The name is invalid
			UnlockList(c->AccountList);
			CiSetError(c, ERR_INVALID_VALUE);
			return false;
		}

		if (a->ClientAuth->AuthType == CLIENT_AUTHTYPE_CERT)
		{
			if (a->ClientAuth->ClientX == NULL ||
				a->ClientAuth->ClientX->is_compatible_bit == false ||
				a->ClientAuth->ClientK == NULL)
			{
				// The client certificate is invalid
				UnlockList(c->AccountList);
				CiSetError(c, ERR_NOT_RSA_1024);
				return false;
			}
		}

		if (a->ServerCert != NULL && a->ServerCert->is_compatible_bit == false)
		{
			// The server certificate is invalid
			UnlockList(c->AccountList);
			CiSetError(c, ERR_NOT_RSA_1024);
			return false;
		}

		// Add a new account
		new_account = ZeroMalloc(sizeof(ACCOUNT));
		new_account->lock = NewLock();

		// Copy the client authentication data
		new_account->ClientAuth = CopyClientAuth(a->ClientAuth);

		// Copy the client option
		new_account->ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
		Copy(new_account->ClientOption, a->ClientOption, sizeof(CLIENT_OPTION));

		new_account->StartupAccount = a->StartupAccount;

		new_account->CheckServerCert = a->CheckServerCert;
		new_account->RetryOnServerCert = a->RetryOnServerCert;
		if (a->ServerCert != NULL)
		{
			new_account->ServerCert = CloneX(a->ServerCert);
		}

		// Shortcut Key
		if (IsZero(a->ShortcutKey, SHA1_SIZE))
		{
			Rand(new_account->ShortcutKey, SHA1_SIZE);
		}
		else
		{
			Copy(new_account->ShortcutKey, a->ShortcutKey, SHA1_SIZE);
		}

		new_account->CreateDateTime = new_account->UpdateDateTime = SystemTime64();

		// Insert into the list
		Insert(c->AccountList, new_account);

		CLog(c, "LC_NEW_ACCOUNT", a->ClientOption->AccountName);
	}
	UnlockList(c->AccountList);

	CiNormalizeAccountVLan(c);

	CiSaveConfigurationFile(c);

	CiNotify(c);

	return true;
}