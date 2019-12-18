#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  c ;
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int /*<<< orphan*/ * AccountList; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; TYPE_1__* ClientOption; scalar_t__ StartupAccount; } ;
struct TYPE_13__ {int /*<<< orphan*/  AccountName; } ;
struct TYPE_12__ {int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_2__ RPC_CLIENT_CONNECT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiCheckOs () ; 
 int /*<<< orphan*/  CiInitKeep (TYPE_4__*) ; 
 int /*<<< orphan*/  CiInitSaver (TYPE_4__*) ; 
 TYPE_4__* CiNewClient () ; 
 int /*<<< orphan*/  CiStartRpcServer (TYPE_4__*) ; 
 int /*<<< orphan*/  CopyUniStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CtConnect (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 void* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegistWindowsFirewallAll () ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_4__* client ; 

void CtStartClient()
{
	UINT i;
	LIST *o;
	if (client != NULL)
	{
		// It is already in running
		return;
	}

	// OS check
	CiCheckOs();

#ifdef	OS_WIN32
	RegistWindowsFirewallAll();
#endif

	// Creating a client
	client = CiNewClient();

	// Start the Keep
	CiInitKeep(client);

	// Start the RPC server
	CiStartRpcServer(client);

	// Start the Saver
	CiInitSaver(client);

	// Start the startup connection
	o = NewListFast(NULL);
	LockList(client->AccountList);
	{
		for (i = 0;i < LIST_NUM(client->AccountList);i++)
		{
			ACCOUNT *a = LIST_DATA(client->AccountList, i);
			Lock(a->lock);
			{
				if (a->StartupAccount)
				{
					Add(o, CopyUniStr(a->ClientOption->AccountName));
				}
			}
			Unlock(a->lock);
		}
	}
	UnlockList(client->AccountList);

	for (i = 0;i < LIST_NUM(o);i++)
	{
		wchar_t *s = LIST_DATA(o, i);
		RPC_CLIENT_CONNECT c;
		Zero(&c, sizeof(c));
		UniStrCpy(c.AccountName, sizeof(c.AccountName), s);
		CtConnect(client, &c);
		Free(s);
	}
	ReleaseList(o);
}