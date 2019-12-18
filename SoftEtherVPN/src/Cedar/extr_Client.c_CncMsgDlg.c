#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ServerName; char* HubName; int /*<<< orphan*/  Msg; } ;
typedef  TYPE_1__ UI_MSG_DLG ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/ * CncConnectEx (int) ; 
 char* CopyUniToUtf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  SendPack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrLen (char*) ; 

SOCK *CncMsgDlg(UI_MSG_DLG *dlg)
{
	SOCK *s;
	PACK *p;
	char *utf;
	// Validate arguments
	if (dlg == NULL)
	{
		return NULL;
	}

	s = CncConnectEx(200);
	if (s == NULL)
	{
		return NULL;
	}

	p = NewPack();
	PackAddStr(p, "function", "msg_dialog");
	PackAddStr(p, "ServerName", dlg->ServerName);
	PackAddStr(p, "HubName", dlg->HubName);
	utf = CopyUniToUtf(dlg->Msg);
	PackAddData(p, "Msg", utf, StrLen(utf));
	Free(utf);

	SendPack(s, p);
	FreePack(p);

	return s;
}