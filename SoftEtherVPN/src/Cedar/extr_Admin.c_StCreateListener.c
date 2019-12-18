#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {int /*<<< orphan*/  ServerListenerList; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_9__ {TYPE_5__* Server; } ;
struct TYPE_8__ {int Port; int /*<<< orphan*/  Enable; } ;
typedef  TYPE_1__ RPC_LISTENER ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_2__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_2__*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_LISTENER_ALREADY_EXISTS ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_5__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int SiAddListener (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

UINT StCreateListener(ADMIN *a, RPC_LISTENER *t)
{
	UINT ret = ERR_NO_ERROR;
	CEDAR *c = a->Server->Cedar;

	if (t->Port == 0 || t->Port > 65535)
	{
		return ERR_INVALID_PARAMETER;
	}

	SERVER_ADMIN_ONLY;

	LockList(a->Server->ServerListenerList);
	{
		if (SiAddListener(a->Server, t->Port, t->Enable) == false)
		{
			ret = ERR_LISTENER_ALREADY_EXISTS;
		}
		else
		{
			ALog(a, NULL, "LA_CREATE_LISTENER", t->Port);

			IncrementServerConfigRevision(a->Server);
		}
	}
	UnlockList(a->Server->ServerListenerList);

	SleepThread(250);

	return ret;
}