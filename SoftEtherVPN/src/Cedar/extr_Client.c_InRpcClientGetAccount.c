#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int StartupAccount; int CheckServerCert; int RetryOnServerCert; int /*<<< orphan*/  ShortcutKey; void* LastConnectDateTime; void* UpdateDateTime; void* CreateDateTime; void* ClientAuth; void* ClientOption; int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ RPC_CLIENT_GET_ACCOUNT ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  int /*<<< orphan*/  CLIENT_AUTH ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  BufToX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientAuth (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientOption (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PackGetBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetData2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PackGetInt (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 void* ZeroMalloc (int) ; 

void InRpcClientGetAccount(RPC_CLIENT_GET_ACCOUNT *c, PACK *p)
{
	BUF *b;
	// Validate arguments
	if (c == NULL || p == NULL)
	{
		return;
	}

	Zero(c, sizeof(RPC_CLIENT_GET_ACCOUNT));

	c->ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
	c->ClientAuth = ZeroMalloc(sizeof(CLIENT_AUTH));

	PackGetUniStr(p, "AccountName", c->AccountName, sizeof(c->AccountName));
	c->StartupAccount = PackGetInt(p, "StartupAccount") ? true : false;
	c->CheckServerCert = PackGetInt(p, "CheckServerCert") ? true : false;
	c->RetryOnServerCert = PackGetInt(p, "RetryOnServerCert") ? true : false;
	b = PackGetBuf(p, "ServerCert");
	if (b != NULL)
	{
		c->ServerCert = BufToX(b, false);
		FreeBuf(b);
	}

	InRpcClientOption(c->ClientOption, p);
	InRpcClientAuth(c->ClientAuth, p);

	c->CreateDateTime = PackGetInt64(p, "CreateDateTime");
	c->UpdateDateTime = PackGetInt64(p, "UpdateDateTime");
	c->LastConnectDateTime = PackGetInt64(p, "LastConnectDateTime");

	PackGetData2(p, "ShortcutKey", c->ShortcutKey, SHA1_SIZE);
}