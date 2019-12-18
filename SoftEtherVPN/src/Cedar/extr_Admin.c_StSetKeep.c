#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_12__ {TYPE_1__* Server; } ;
struct TYPE_11__ {int Server; int ServerPort; int Interval; int /*<<< orphan*/  lock; int /*<<< orphan*/  UdpMode; int /*<<< orphan*/  ServerName; scalar_t__ Enable; } ;
struct TYPE_10__ {int KeepConnectPort; int KeepConnectInterval; int /*<<< orphan*/  KeepConnectProtocol; int /*<<< orphan*/  KeepConnectHost; scalar_t__ UseKeepConnect; } ;
struct TYPE_9__ {TYPE_3__* Keep; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_KEEP ;
typedef  TYPE_3__ KEEP ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_4__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

UINT StSetKeep(ADMIN *a, RPC_KEEP *t)
{
	SERVER *s = a->Server;

	if (t->UseKeepConnect)
	{
		if (IsEmptyStr(t->KeepConnectHost) ||
			t->KeepConnectPort == 0 ||
			t->KeepConnectPort >= 65536)
		{
			return ERR_INVALID_PARAMETER;
		}
	}

	SERVER_ADMIN_ONLY;

	Lock(s->Keep->lock);
	{
		KEEP *keep = s->Keep;
		keep->Enable = t->UseKeepConnect;
		keep->Server = true;
		StrCpy(keep->ServerName, sizeof(keep->ServerName), t->KeepConnectHost);
		keep->ServerPort = t->KeepConnectPort;
		keep->UdpMode = t->KeepConnectProtocol;
		keep->Interval = t->KeepConnectInterval * 1000;
		if (keep->Interval < 5000)
		{
			keep->Interval = 5000;
		}
		else if (keep->Interval > 600000)
		{
			keep->Interval = 600000;
		}
	}
	Unlock(s->Keep->lock);

	ALog(a, NULL, "LA_SET_KEEP");

	IncrementServerConfigRevision(s);

	return ERR_NO_ERROR;
}