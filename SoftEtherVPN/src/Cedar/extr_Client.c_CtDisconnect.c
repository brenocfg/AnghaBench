#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  AccountName; } ;
struct TYPE_19__ {int /*<<< orphan*/  lock; TYPE_1__* ClientSession; TYPE_5__* ClientOption; } ;
struct TYPE_18__ {int /*<<< orphan*/  AccountList; } ;
struct TYPE_17__ {int /*<<< orphan*/  AccountName; } ;
struct TYPE_16__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ SESSION ;
typedef  TYPE_2__ RPC_CLIENT_CONNECT ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  TYPE_3__ CLIENT ;
typedef  TYPE_4__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLog (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiNotify (TYPE_3__*) ; 
 int /*<<< orphan*/  CiSetError (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_ACCOUNT_INACTIVE ; 
 int /*<<< orphan*/  ERR_ACCOUNT_NOT_FOUND ; 
 int /*<<< orphan*/  Free (TYPE_5__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_1__*) ; 
 TYPE_4__* Search (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  StopSession (TYPE_1__*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_5__* ZeroMalloc (int) ; 

bool CtDisconnect(CLIENT *c, RPC_CLIENT_CONNECT *connect, bool inner)
{
	bool ret = false;
	ACCOUNT t, *r;
	SESSION *s = NULL;
	// Validate arguments
	if (c == NULL || connect == NULL)
	{
		return false;
	}

	LockList(c->AccountList);
	{
		// Search for account
		t.ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
		UniStrCpy(t.ClientOption->AccountName, sizeof(t.ClientOption->AccountName), connect->AccountName);

		r = Search(c->AccountList, &t);
		if (r == NULL)
		{
			// Specified account isn't found
			UnlockList(c->AccountList);

			Free(t.ClientOption);
			CiSetError(c, ERR_ACCOUNT_NOT_FOUND);
			return false;
		}

		Free(t.ClientOption);

		Lock(r->lock);
		{
			if (r->ClientSession == NULL)
			{
				// Not connected
				CiSetError(c, ERR_ACCOUNT_INACTIVE);
			}
			else
			{
				s = r->ClientSession;
				AddRef(s->ref);
				// Disconnect complete
				r->ClientSession = NULL;
				ret = true;
			}
		}
		Unlock(r->lock);
	}
	UnlockList(c->AccountList);

	if (s != NULL)
	{
		// Disconnect the connection (Wait until the disconnection is complete)
		CLog(c, "LC_DISCONNECT", connect->AccountName);
		StopSession(s);
		ReleaseSession(s);
	}


	if (ret != false)
	{
		CiNotify(c);
	}

	return ret;
}