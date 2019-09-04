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
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_8__ {scalar_t__ NumFarm; TYPE_1__* Farms; } ;
struct TYPE_7__ {scalar_t__ Controller; int /*<<< orphan*/  Id; int /*<<< orphan*/  AssignedBridgeLicense; int /*<<< orphan*/  AssignedClientLicense; int /*<<< orphan*/  NumHubs; int /*<<< orphan*/  NumTcpConnections; int /*<<< orphan*/  NumSessions; int /*<<< orphan*/  Point; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  ConnectedTime; } ;
typedef  TYPE_1__ RPC_ENUM_FARM_ITEM ;
typedef  TYPE_2__ RPC_ENUM_FARM ;
typedef  TYPE_3__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumFarm (TYPE_2__*) ; 
 int /*<<< orphan*/  GetDateTimeStrEx64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScEnumFarmMember (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PsClusterMemberList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ENUM_FARM t;
	CT *ct;
	UINT i;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScEnumFarmMember(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	ct = CtNew();

	CtInsertColumn(ct, _UU("CMD_ID"), true);
	CtInsertColumn(ct, _UU("SM_FM_COLUMN_1"), false);
	CtInsertColumn(ct, _UU("SM_FM_COLUMN_2"), false);
	CtInsertColumn(ct, _UU("SM_FM_COLUMN_3"), false);
	CtInsertColumn(ct, _UU("SM_FM_COLUMN_4"), true);
	CtInsertColumn(ct, _UU("SM_FM_COLUMN_5"), true);
	CtInsertColumn(ct, _UU("SM_FM_COLUMN_6"), true);
	CtInsertColumn(ct, _UU("SM_FM_COLUMN_7"), true);
	CtInsertColumn(ct, _UU("SM_FM_COLUMN_8"), true);
	CtInsertColumn(ct, _UU("SM_FM_COLUMN_9"), true);

	for (i = 0;i < t.NumFarm;i++)
	{
		RPC_ENUM_FARM_ITEM *e = &t.Farms[i];
		wchar_t tmp0[64];
		wchar_t tmp1[MAX_SIZE];
		wchar_t tmp2[MAX_SIZE];
		wchar_t tmp3[64];
		wchar_t tmp4[64];
		wchar_t tmp5[64];
		wchar_t tmp6[64];
		wchar_t tmp7[64];
		wchar_t tmp8[64];

		GetDateTimeStrEx64(tmp1, sizeof(tmp1), SystemToLocal64(e->ConnectedTime), NULL);
		StrToUni(tmp2, sizeof(tmp2), e->Hostname);
		UniToStru(tmp3, e->Point);
		UniToStru(tmp4, e->NumSessions);
		UniToStru(tmp5, e->NumTcpConnections);
		UniToStru(tmp6, e->NumHubs);
		UniToStru(tmp7, e->AssignedClientLicense);
		UniToStru(tmp8, e->AssignedBridgeLicense);

		UniToStru(tmp0, e->Id);

		CtInsert(ct, tmp0,
			e->Controller ? _UU("SM_FM_CONTROLLER") : _UU("SM_FM_MEMBER"),
			tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8);
	}

	CtFree(ct, c);

	FreeRpcEnumFarm(&t);

	FreeParamValueList(o);

	return 0;
}