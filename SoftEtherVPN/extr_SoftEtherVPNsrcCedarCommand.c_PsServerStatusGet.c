#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  vv ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_6__ {scalar_t__ TotalMemory; scalar_t__ UsedMemory; scalar_t__ FreeMemory; scalar_t__ TotalPhys; scalar_t__ UsedPhys; scalar_t__ FreePhys; } ;
struct TYPE_7__ {scalar_t__ ServerType; char* CurrentTick; TYPE_1__ MemInfo; int /*<<< orphan*/  CurrentTime; int /*<<< orphan*/  StartTime; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  AssignedBridgeLicensesTotal; int /*<<< orphan*/  AssignedClientLicensesTotal; int /*<<< orphan*/  AssignedBridgeLicenses; int /*<<< orphan*/  AssignedClientLicenses; int /*<<< orphan*/  NumGroups; int /*<<< orphan*/  NumUsers; int /*<<< orphan*/  NumIpTables; int /*<<< orphan*/  NumMacTables; int /*<<< orphan*/  NumSessionsRemote; int /*<<< orphan*/  NumSessionsLocal; int /*<<< orphan*/  NumSessionsTotal; int /*<<< orphan*/  NumHubDynamic; int /*<<< orphan*/  NumHubStatic; int /*<<< orphan*/  NumHubTotal; int /*<<< orphan*/  NumTcpConnectionsRemote; int /*<<< orphan*/  NumTcpConnectionsLocal; int /*<<< orphan*/  NumTcpConnections; } ;
typedef  TYPE_2__ RPC_SERVER_STATUS ;
typedef  TYPE_3__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdInsertTrafficInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDateTimeStrEx64 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDateTimeStrMilli64 (char*,int,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 scalar_t__ ScGetServerStatus (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrToUni (char*,int,char*) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ToStr3 (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,char*) ; 
 int /*<<< orphan*/  UniToStru (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 char* _UU (char*) ; 

UINT PsServerStatusGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret;
	RPC_SERVER_STATUS t;
	wchar_t tmp[MAX_PATH];
	char tmp2[MAX_PATH];
	CT *ct;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));
	ret = ScGetServerStatus(ps->Rpc, &t);
	if (ret != ERR_NO_ERROR)
	{
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	ct = CtNew();

	CtInsertColumn(ct, _UU("SM_STATUS_COLUMN_1"), false);
	CtInsertColumn(ct, _UU("SM_STATUS_COLUMN_2"), false);

	// Type of server
	CtInsert(ct, _UU("SM_ST_SERVER_TYPE"),
		t.ServerType == SERVER_TYPE_STANDALONE ? _UU("SM_SERVER_STANDALONE") :
		t.ServerType == SERVER_TYPE_FARM_MEMBER ? _UU("SM_FARM_MEMBER") : _UU("SM_FARM_CONTROLLER"));

	// Number of TCP connections
	UniToStru(tmp, t.NumTcpConnections);
	CtInsert(ct, _UU("SM_ST_NUM_TCP"), tmp);

	if (t.ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		// Number of local TCP connections
		UniToStru(tmp, t.NumTcpConnectionsLocal);
		CtInsert(ct, _UU("SM_ST_NUM_TCP_LOCAL"), tmp);

		// Number of remote TCP connections
		UniToStru(tmp, t.NumTcpConnectionsRemote);
		CtInsert(ct, _UU("SM_ST_NUM_TCP_REMOTE"), tmp);
	}

	// Number of Virtual HUBs
	UniToStru(tmp, t.NumHubTotal);
	CtInsert(ct, _UU("SM_ST_NUM_HUB_TOTAL"), tmp);

	if (t.ServerType != SERVER_TYPE_STANDALONE)
	{
		// Number of static HUBs
		UniToStru(tmp, t.NumHubStatic);
		CtInsert(ct, _UU("SM_ST_NUM_HUB_STATIC"), tmp);

		// Number of dynamic HUBs
		UniToStru(tmp, t.NumHubDynamic);
		CtInsert(ct, _UU("SM_ST_NUM_HUB_DYNAMIC"), tmp);
	}

	// Number of sessions
	UniToStru(tmp, t.NumSessionsTotal);
	CtInsert(ct, _UU("SM_ST_NUM_SESSION_TOTAL"), tmp);

	if (t.ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		// Number of local sessions
		UniToStru(tmp, t.NumSessionsLocal);
		CtInsert(ct, _UU("SM_ST_NUM_SESSION_LOCAL"), tmp);

		// Number of remote sessions
		UniToStru(tmp, t.NumSessionsRemote);
		CtInsert(ct, _UU("SM_ST_NUM_SESSION_REMOTE"), tmp);
	}

	// Number of MAC tables
	UniToStru(tmp, t.NumMacTables);
	CtInsert(ct, _UU("SM_ST_NUM_MAC_TABLE"), tmp);

	// Number of IP tables
	UniToStru(tmp, t.NumIpTables);
	CtInsert(ct, _UU("SM_ST_NUM_IP_TABLE"), tmp);

	// Number of users
	UniToStru(tmp, t.NumUsers);
	CtInsert(ct, _UU("SM_ST_NUM_USERS"), tmp);

	// Number of groups
	UniToStru(tmp, t.NumGroups);
	CtInsert(ct, _UU("SM_ST_NUM_GROUPS"), tmp);

	// Number of assigned licenses
	UniToStru(tmp, t.AssignedClientLicenses);
	CtInsert(ct, _UU("SM_ST_CLIENT_LICENSE"), tmp);

	UniToStru(tmp, t.AssignedBridgeLicenses);
	CtInsert(ct, _UU("SM_ST_BRIDGE_LICENSE"), tmp);

	if (t.ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		UniToStru(tmp, t.AssignedClientLicensesTotal);
		CtInsert(ct, _UU("SM_ST_CLIENT_LICENSE_EX"), tmp);

		UniToStru(tmp, t.AssignedBridgeLicensesTotal);
		CtInsert(ct, _UU("SM_ST_BRIDGE_LICENSE_EX"), tmp);
	}

	// Traffic
	CmdInsertTrafficInfo(ct, &t.Traffic);

	// Server start-up time
	GetDateTimeStrEx64(tmp, sizeof(tmp), SystemToLocal64(t.StartTime), NULL);
	CtInsert(ct, _UU("SM_ST_START_TIME"), tmp);

	// Current time
	GetDateTimeStrMilli64(tmp2, sizeof(tmp2), SystemToLocal64(t.CurrentTime));
	StrToUni(tmp, sizeof(tmp), tmp2);
	CtInsert(ct, _UU("SM_ST_CURRENT_TIME"), tmp);

	// Tick value
	UniFormat(tmp, sizeof(tmp), L"%I64u", t.CurrentTick);
	CtInsert(ct, _UU("SM_ST_CURRENT_TICK"), tmp);

	// Memory information
	if (t.MemInfo.TotalMemory != 0)
	{
		char vv[128];

		ToStr3(vv, sizeof(vv), t.MemInfo.TotalMemory);
		UniFormat(tmp, sizeof(tmp), _UU("SM_ST_RAM_SIZE_KB"), vv);
		CtInsert(ct, _UU("SM_ST_TOTAL_MEMORY"), tmp);

		ToStr3(vv, sizeof(vv), t.MemInfo.UsedMemory);
		UniFormat(tmp, sizeof(tmp), _UU("SM_ST_RAM_SIZE_KB"), vv);
		CtInsert(ct, _UU("SM_ST_USED_MEMORY"), tmp);

		ToStr3(vv, sizeof(vv), t.MemInfo.FreeMemory);
		UniFormat(tmp, sizeof(tmp), _UU("SM_ST_RAM_SIZE_KB"), vv);
		CtInsert(ct, _UU("SM_ST_FREE_MEMORY"), tmp);

		ToStr3(vv, sizeof(vv), t.MemInfo.TotalPhys);
		UniFormat(tmp, sizeof(tmp), _UU("SM_ST_RAM_SIZE_KB"), vv);
		CtInsert(ct, _UU("SM_ST_TOTAL_PHYS"), tmp);

		ToStr3(vv, sizeof(vv), t.MemInfo.UsedPhys);
		UniFormat(tmp, sizeof(tmp), _UU("SM_ST_RAM_SIZE_KB"), vv);
		CtInsert(ct, _UU("SM_ST_USED_PHYS"), tmp);

		ToStr3(vv, sizeof(vv), t.MemInfo.FreePhys);
		UniFormat(tmp, sizeof(tmp), _UU("SM_ST_RAM_SIZE_KB"), vv);
		CtInsert(ct, _UU("SM_ST_FREE_PHYS"), tmp);
	}

	CtFree(ct, c);

	FreeParamValueList(o);

	return 0;
}