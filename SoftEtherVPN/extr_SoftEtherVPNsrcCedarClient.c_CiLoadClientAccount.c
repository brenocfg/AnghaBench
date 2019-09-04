#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_10__ {int /*<<< orphan*/  ShortcutKey; int /*<<< orphan*/  ServerCert; void* LastConnectDateTime; void* UpdateDateTime; void* CreateDateTime; void* RetryOnServerCert; void* CheckServerCert; void* StartupAccount; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  ClientOption; int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {scalar_t__ Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ BUF ;
typedef  TYPE_2__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  BufToX (TYPE_1__*,int) ; 
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* CfgGetBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetInt64 (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  CiLoadClientAuth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiLoadClientOption (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SHA1_SIZE ; 
 TYPE_1__* StrToBin (char*) ; 
 TYPE_2__* ZeroMalloc (int) ; 

ACCOUNT *CiLoadClientAccount(FOLDER *f)
{
	ACCOUNT *a;
	FOLDER *client_option_folder, *client_auth_folder;
	BUF *b;
	char tmp[64];
	// Validate arguments
	if (f == NULL)
	{
		return NULL;
	}

	client_option_folder = CfgGetFolder(f, "ClientOption");

	if (client_option_folder != NULL)
	{
		// Compare whether it matches to the account name that is already registered
	}

	client_auth_folder = CfgGetFolder(f, "ClientAuth");

	if (client_option_folder == NULL || client_auth_folder == NULL)
	{
		return NULL;
	}

	a = ZeroMalloc(sizeof(ACCOUNT));
	a->lock = NewLock();

	a->ClientOption = CiLoadClientOption(client_option_folder);
	a->ClientAuth = CiLoadClientAuth(client_auth_folder);

	a->StartupAccount = CfgGetBool(f, "StartupAccount");
	a->CheckServerCert = CfgGetBool(f, "CheckServerCert");
	a->RetryOnServerCert = CfgGetBool(f, "RetryOnServerCert");
	a->CreateDateTime = CfgGetInt64(f, "CreateDateTime");
	a->UpdateDateTime = CfgGetInt64(f, "UpdateDateTime");
	a->LastConnectDateTime = CfgGetInt64(f, "LastConnectDateTime");

	b = CfgGetBuf(f, "ServerCert");
	if (b != NULL)
	{
		a->ServerCert = BufToX(b, false);
		FreeBuf(b);
	}

	if (CfgGetStr(f, "ShortcutKey", tmp, sizeof(tmp)))
	{
		BUF *b = StrToBin(tmp);
		if (b->Size == SHA1_SIZE)
		{
			Copy(a->ShortcutKey, b->Buf, SHA1_SIZE);
		}
		FreeBuf(b);
	}

	if (IsZero(a->ShortcutKey, SHA1_SIZE))
	{
		Rand(a->ShortcutKey, SHA1_SIZE);
	}

	return a;
}