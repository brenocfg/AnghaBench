#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {int /*<<< orphan*/  ShortcutKey; int /*<<< orphan*/ * ServerCert; int /*<<< orphan*/  LastConnectDateTime; int /*<<< orphan*/  UpdateDateTime; int /*<<< orphan*/  CreateDateTime; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  ClientOption; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;
typedef  TYPE_1__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CiWriteClientAuth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiWriteClientOption (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int IsZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/ * XToBuf (int /*<<< orphan*/ *,int) ; 

void CiWriteAccountData(FOLDER *f, ACCOUNT *a)
{
	// Validate arguments
	if (f == NULL || a == NULL)
	{
		return;
	}

	// Client Option
	CiWriteClientOption(CfgCreateFolder(f, "ClientOption"), a->ClientOption);

	// Client authentication data
	CiWriteClientAuth(CfgCreateFolder(f, "ClientAuth"), a->ClientAuth);

	// Startup account
	CfgAddBool(f, "StartupAccount", a->StartupAccount);

	// Server certificate check flag
	CfgAddBool(f, "CheckServerCert", a->CheckServerCert);

	// Retry on invalid server certificate flag
	CfgAddBool(f, "RetryOnServerCert", a->RetryOnServerCert);

	// Date and time
	CfgAddInt64(f, "CreateDateTime", a->CreateDateTime);
	CfgAddInt64(f, "UpdateDateTime", a->UpdateDateTime);
	CfgAddInt64(f, "LastConnectDateTime", a->LastConnectDateTime);

	// Server certificate body
	if (a->ServerCert != NULL)
	{
		BUF *b = XToBuf(a->ServerCert, false);
		if (b != NULL)
		{
			CfgAddBuf(f, "ServerCert", b);
			FreeBuf(b);
		}
	}

	// Shortcut Key
	if (IsZero(a->ShortcutKey, SHA1_SIZE) == false)
	{
		char tmp[64];
		BinToStr(tmp, sizeof(tmp), a->ShortcutKey, SHA1_SIZE);
		CfgAddStr(f, "ShortcutKey", tmp);
	}
}