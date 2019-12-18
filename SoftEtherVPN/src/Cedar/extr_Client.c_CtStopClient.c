#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_14__ {int Halt; int /*<<< orphan*/  AccountList; } ;
struct TYPE_13__ {int /*<<< orphan*/  lock; TYPE_1__* ClientSession; } ;
struct TYPE_12__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ SESSION ;
typedef  TYPE_2__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiFreeKeep (TYPE_3__*) ; 
 int /*<<< orphan*/  CiFreeSaver (TYPE_3__*) ; 
 int /*<<< orphan*/  CiStopRpcServer (TYPE_3__*) ; 
 int /*<<< orphan*/  CncExit () ; 
 int /*<<< orphan*/  CtReleaseClient (TYPE_3__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__**) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_1__*) ; 
 int /*<<< orphan*/  StopSession (TYPE_1__*) ; 
 TYPE_2__** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_3__* client ; 

void CtStopClient()
{
	UINT i, num;
	ACCOUNT **account_list;
	if (client == NULL)
	{
		// It is not running yet
		return;
	}

	// Halting flag
	client->Halt = true;

	// Disconnect all the RPC
	CiStopRpcServer(client);

	// Exit the client notification service
	CncExit();

	// Exit the Keep
	CiFreeKeep(client);

	// Disconnect all accounts connected
	LockList(client->AccountList);
	{
		num = LIST_NUM(client->AccountList);
		account_list = ToArray(client->AccountList);
	}
	UnlockList(client->AccountList);

	for (i = 0;i < num;i++)
	{
		ACCOUNT *a = account_list[i];
		SESSION *s = NULL;

		Lock(a->lock);
		{
			if (a->ClientSession != NULL)
			{
				s = a->ClientSession;
				AddRef(s->ref);
			}
		}
		Unlock(a->lock);

		if (s != NULL)
		{
			StopSession(s);
			ReleaseSession(s);
			Lock(a->lock);
			{
				if (a->ClientSession != NULL)
				{
					ReleaseSession(a->ClientSession);
					a->ClientSession = NULL;
				}
			}
			Unlock(a->lock);
		}
	}

	Free(account_list);

	// Stop the Saver
	CiFreeSaver(client);

	// Release the client
	CtReleaseClient(client);
	client = NULL;
}