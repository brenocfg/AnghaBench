#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int KeepConnectInterval; scalar_t__ KeepConnectProtocol; int /*<<< orphan*/  KeepConnectPort; int /*<<< orphan*/  KeepConnectHost; } ;
struct TYPE_14__ {int /*<<< orphan*/  AccountList; int /*<<< orphan*/  UnixVLanList; TYPE_8__ Config; TYPE_1__* Keep; int /*<<< orphan*/  lock; } ;
struct TYPE_13__ {int KeepConnectPort; scalar_t__ NicDownOnDisconnect; scalar_t__ UseKeepConnect; int /*<<< orphan*/  KeepConnectHost; } ;
struct TYPE_12__ {int Interval; int UdpMode; int Enable; int /*<<< orphan*/  lock; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerName; } ;
typedef  TYPE_1__ KEEP ;
typedef  TYPE_2__ CLIENT_CONFIG ;
typedef  TYPE_3__ CLIENT ;

/* Variables and functions */
 scalar_t__ CONNECTION_UDP ; 
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_3__*) ; 
 int /*<<< orphan*/  CiSetError (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (TYPE_8__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  CtVLansDown (TYPE_3__*) ; 
 int /*<<< orphan*/  CtVLansUp (TYPE_3__*) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

bool CtSetClientConfig(CLIENT *c, CLIENT_CONFIG *o)
{
	KEEP *k;
	// Validate arguments
	if (c == NULL || o == NULL)
	{
		return false;
	}

	if (o->UseKeepConnect)
	{
		if (IsEmptyStr(o->KeepConnectHost) ||
			o->KeepConnectPort == 0 ||
			o->KeepConnectPort >= 65536)
		{
			CiSetError(c, ERR_INVALID_PARAMETER);
			return false;
		}
	}

	Lock(c->lock);
	{
		Copy(&c->Config, o, sizeof(CLIENT_CONFIG));
	}
	Unlock(c->lock);

	// Save the settings
	CiSaveConfigurationFile(c);

	// Apply the Keep Connect
	k = c->Keep;
	Lock(k->lock);
	{
		if (o->UseKeepConnect)
		{
			StrCpy(k->ServerName, sizeof(k->ServerName), c->Config.KeepConnectHost);
			k->ServerPort = c->Config.KeepConnectPort;
			k->Interval = c->Config.KeepConnectInterval * 1000;
			k->UdpMode = (c->Config.KeepConnectProtocol == CONNECTION_UDP) ? true : false;
			k->Enable = true;
		}
		else
		{
			k->Enable = false;
		}
	}
	Unlock(k->lock);

	// Apply TAP state
	LockList(c->AccountList);
	LockList(c->UnixVLanList);
	if (o->NicDownOnDisconnect)
	{
		CtVLansDown(c);
	}
	else
	{
		CtVLansUp(c);
	}
	UnlockList(c->UnixVLanList);
	UnlockList(c->AccountList);

	return true;
}