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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int ConsoleForServer; int /*<<< orphan*/  CmdLine; void* AdminHub; scalar_t__ LastError; void* HubName; int /*<<< orphan*/ * Rpc; int /*<<< orphan*/ * Console; void* ServerName; int /*<<< orphan*/  ServerPort; } ;
typedef  int /*<<< orphan*/  RPC ;
typedef  TYPE_1__ PS ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 void* CopyStr (char*) ; 
 int /*<<< orphan*/  CopyUniStr (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 scalar_t__ UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

PS *NewPs(CONSOLE *c, RPC *rpc, char *servername, UINT serverport, char *hubname, char *adminhub, wchar_t *cmdline)
{
	PS *ps;
	// Validate arguments
	if (c == NULL || rpc == NULL || servername == NULL)
	{
		return NULL;
	}

	if (IsEmptyStr(hubname))
	{
		hubname = NULL;
	}
	if (IsEmptyStr(adminhub))
	{
		adminhub = NULL;
	}
	if (UniIsEmptyStr(cmdline))
	{
		cmdline = NULL;
	}

	ps = ZeroMalloc(sizeof(PS));
	ps->ConsoleForServer = true;
	ps->ServerPort = serverport;
	ps->ServerName = CopyStr(servername);
	ps->Console = c;
	ps->Rpc = rpc;
	ps->HubName = CopyStr(hubname);
	ps->LastError = 0;
	ps->AdminHub = CopyStr(adminhub);
	ps->CmdLine = CopyUniStr(cmdline);

	return ps;
}