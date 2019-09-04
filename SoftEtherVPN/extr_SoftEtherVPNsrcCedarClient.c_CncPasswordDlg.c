#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* Username; char* Password; char* ServerName; int /*<<< orphan*/  Type; void* ProxyServer; void* NoSavePassword; void* ShowNoSavePassword; void* AdminMode; int /*<<< orphan*/  RetryIntervalSec; } ;
typedef  TYPE_1__ UI_PASSWORD_DLG ;
struct TYPE_11__ {int HaltThread; int /*<<< orphan*/  Event; int /*<<< orphan*/ * Sock; TYPE_2__* Session; } ;
struct TYPE_10__ {int /*<<< orphan*/  RetryInterval; int /*<<< orphan*/  HaltEvent; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_2__ SESSION ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_3__ CNC_CONNECT_ERROR_DLG_THREAD_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/ * CncConnect () ; 
 int /*<<< orphan*/  CncConnectErrorDlgHaltThread ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_3__*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/ * RecvPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendPack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* ZeroMalloc (int) ; 

bool CncPasswordDlg(SESSION *session, UI_PASSWORD_DLG *dlg)
{
	SOCK *s;
	PACK *p;
	CNC_CONNECT_ERROR_DLG_THREAD_PARAM *dp;
	THREAD *t;
	bool ret = false;
	// Validate arguments
	if (dlg == NULL || session == NULL)
	{
		return false;
	}

	s = CncConnect();
	if (s == NULL)
	{
		Wait(session->HaltEvent, session->RetryInterval);
		return true;
	}

	p = NewPack();
	PackAddStr(p, "function", "password_dialog");
	PackAddInt(p, "Type", dlg->Type);
	PackAddStr(p, "Username", dlg->Username);
	PackAddStr(p, "Password", dlg->Password);
	PackAddStr(p, "ServerName", dlg->ServerName);
	PackAddInt(p, "RetryIntervalSec", dlg->RetryIntervalSec);
	PackAddBool(p, "ProxyServer", dlg->ProxyServer);
	PackAddBool(p, "AdminMode", dlg->AdminMode);
	PackAddBool(p, "ShowNoSavePassword", dlg->ShowNoSavePassword);
	PackAddBool(p, "NoSavePassword", dlg->NoSavePassword);

	SendPack(s, p);
	FreePack(p);

	dp = ZeroMalloc(sizeof(CNC_CONNECT_ERROR_DLG_THREAD_PARAM));
	dp->Session = session;
	dp->Sock = s;
	dp->Event = NewEvent();

	t = NewThread(CncConnectErrorDlgHaltThread, dp);

	p = RecvPack(s);
	if (p != NULL)
	{
		ret = PackGetBool(p, "ok");
		dlg->NoSavePassword = PackGetBool(p, "NoSavePassword");
		dlg->ProxyServer = PackGetBool(p, "ProxyServer");
		dlg->Type = PackGetInt(p, "Type");
		PackGetStr(p, "Username", dlg->Username, sizeof(dlg->Username));
		PackGetStr(p, "Password", dlg->Password, sizeof(dlg->Password));

		FreePack(p);
	}

	dp->HaltThread = true;
	Set(dp->Event);

	WaitThread(t, INFINITE);

	ReleaseEvent(dp->Event);
	Free(dp);
	ReleaseThread(t);

	Disconnect(s);
	ReleaseSock(s);

	return ret;
}