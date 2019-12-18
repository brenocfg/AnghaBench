#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  nic ;
typedef  int /*<<< orphan*/  hub ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_8__ {scalar_t__ NumItem; TYPE_1__* Items; } ;
struct TYPE_7__ {scalar_t__ Active; scalar_t__ Online; int /*<<< orphan*/  HubName; int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_1__ RPC_LOCALBRIDGE ;
typedef  TYPE_2__ RPC_ENUM_LOCALBRIDGE ;
typedef  TYPE_3__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumLocalBridge (TYPE_2__*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScEnumLocalBridge (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PsBridgeList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ENUM_LOCALBRIDGE t;
	UINT i;
	CT *ct;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScEnumLocalBridge(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	ct = CtNew();

	CtInsertColumn(ct, _UU("SM_BRIDGE_COLUMN_1"), false);
	CtInsertColumn(ct, _UU("SM_BRIDGE_COLUMN_2"), false);
	CtInsertColumn(ct, _UU("SM_BRIDGE_COLUMN_3"), false);
	CtInsertColumn(ct, _UU("SM_BRIDGE_COLUMN_4"), false);

	for (i = 0;i < t.NumItem;i++)
	{
		RPC_LOCALBRIDGE *e = &t.Items[i];
		wchar_t name[MAX_SIZE];
		wchar_t nic[MAX_SIZE];
		wchar_t hub[MAX_SIZE];
		wchar_t *status = _UU("SM_BRIDGE_OFFLINE");

		UniToStru(name, i + 1);
		StrToUni(nic, sizeof(nic), e->DeviceName);
		StrToUni(hub, sizeof(hub), e->HubName);

		if (e->Online)
		{
			status = e->Active ? _UU("SM_BRIDGE_ONLINE") : _UU("SM_BRIDGE_ERROR");
		}

		CtInsert(ct, name, hub, nic, status);
	}

	CtFree(ct, c);

	FreeRpcEnumLocalBridge(&t);

	FreeParamValueList(o);

	return 0;
}