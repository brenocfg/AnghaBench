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
struct TYPE_10__ {int /*<<< orphan*/  ServerListenerList; } ;
struct TYPE_9__ {TYPE_5__* Server; } ;
struct TYPE_8__ {int /*<<< orphan*/  Port; } ;
typedef  TYPE_1__ RPC_LISTENER ;
typedef  TYPE_2__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_2__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_LISTENER_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_5__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int SiDeleteListener (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

UINT StDeleteListener(ADMIN *a, RPC_LISTENER *t)
{
	UINT ret = ERR_NO_ERROR;

	SERVER_ADMIN_ONLY;


	LockList(a->Server->ServerListenerList);
	{
		if (SiDeleteListener(a->Server, t->Port) == false)
		{
			ret = ERR_LISTENER_NOT_FOUND;
		}
		else
		{
			ALog(a, NULL, "LA_DELETE_LISTENER", t->Port);

			IncrementServerConfigRevision(a->Server);
		}
	}
	UnlockList(a->Server->ServerListenerList);

	return ret;
}