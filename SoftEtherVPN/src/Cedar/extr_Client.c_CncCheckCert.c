#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* ServerName; void* SaveServerCert; void* DiffWarning; void* Ok; int /*<<< orphan*/  old_x; int /*<<< orphan*/  parent_x; int /*<<< orphan*/  x; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ UI_CHECKCERT ;
struct TYPE_8__ {int HaltThread; int /*<<< orphan*/  Event; int /*<<< orphan*/ * Session; int /*<<< orphan*/ * Sock; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  SESSION ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ CNC_CONNECT_ERROR_DLG_THREAD_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  CncCheckCertHaltThread ; 
 int /*<<< orphan*/ * CncConnect () ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddX (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * RecvPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendPack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ZeroMalloc (int) ; 

void CncCheckCert(SESSION *session, UI_CHECKCERT *dlg)
{
	SOCK *s;
	PACK *p;
	CNC_CONNECT_ERROR_DLG_THREAD_PARAM *dp;
	THREAD *t;
	// Validate arguments
	if (dlg == NULL || session == NULL)
	{
		return;
	}

	s = CncConnect();
	if (s == NULL)
	{
		return;
	}

	p = NewPack();
	PackAddStr(p, "function", "check_cert");
	PackAddUniStr(p, "AccountName", dlg->AccountName);
	PackAddStr(p, "ServerName", dlg->ServerName);
	PackAddX(p, "x", dlg->x);
	PackAddX(p, "parent_x", dlg->parent_x);
	PackAddX(p, "old_x", dlg->old_x);
	PackAddBool(p, "DiffWarning", dlg->DiffWarning);
	PackAddBool(p, "Ok", dlg->Ok);
	PackAddBool(p, "SaveServerCert", dlg->SaveServerCert);

	SendPack(s, p);
	FreePack(p);

	dp = ZeroMalloc(sizeof(CNC_CONNECT_ERROR_DLG_THREAD_PARAM));
	dp->Sock = s;
	dp->Event = NewEvent();
	dp->Session = session;

	t = NewThread(CncCheckCertHaltThread, dp);

	p = RecvPack(s);
	if (p != NULL)
	{
		dlg->Ok = PackGetBool(p, "Ok");
		dlg->DiffWarning = PackGetBool(p, "DiffWarning");
		dlg->SaveServerCert = PackGetBool(p, "SaveServerCert");

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
}