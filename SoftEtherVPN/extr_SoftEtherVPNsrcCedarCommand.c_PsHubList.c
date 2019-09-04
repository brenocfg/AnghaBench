#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  s9 ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int /*<<< orphan*/  s7 ;
typedef  int /*<<< orphan*/  s10 ;
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_14__ {scalar_t__ NumHub; TYPE_4__* Hubs; } ;
struct TYPE_11__ {scalar_t__ UnicastCount; scalar_t__ BroadcastCount; scalar_t__ UnicastBytes; scalar_t__ BroadcastBytes; } ;
struct TYPE_10__ {scalar_t__ UnicastCount; scalar_t__ BroadcastCount; scalar_t__ UnicastBytes; scalar_t__ BroadcastBytes; } ;
struct TYPE_12__ {TYPE_2__ Send; TYPE_1__ Recv; } ;
struct TYPE_13__ {scalar_t__ LastLoginTime; scalar_t__ LastCommTime; int IsTrafficFilled; int /*<<< orphan*/  HubType; scalar_t__ Online; int /*<<< orphan*/  HubName; TYPE_3__ Traffic; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  NumIpTables; int /*<<< orphan*/  NumMacTables; int /*<<< orphan*/  NumSessions; int /*<<< orphan*/  NumGroups; int /*<<< orphan*/  NumUsers; } ;
typedef  TYPE_4__ RPC_ENUM_HUB_ITEM ;
typedef  TYPE_5__ RPC_ENUM_HUB ;
typedef  TYPE_6__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFreeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumHub (TYPE_5__*) ; 
 int /*<<< orphan*/  GetDateTimeStr64Uni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetHubTypeStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScEnumHub (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemToLocal64 (scalar_t__) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStr3 (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_5__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PsHubList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ENUM_HUB t;
	UINT i;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScEnumHub(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		CT *ct = CtNew();

		CtInsertColumn(ct, _UU("SM_HUB_COLUMN_1"), false);
		CtInsertColumn(ct, _UU("SM_HUB_COLUMN_2"), false);
		CtInsertColumn(ct, _UU("SM_HUB_COLUMN_3"), false);
		CtInsertColumn(ct, _UU("SM_HUB_COLUMN_4"), false);
		CtInsertColumn(ct, _UU("SM_HUB_COLUMN_5"), false);
		CtInsertColumn(ct, _UU("SM_HUB_COLUMN_6"), false);
		CtInsertColumn(ct, _UU("SM_HUB_COLUMN_7"), false);
		CtInsertColumn(ct, _UU("SM_HUB_COLUMN_8"), false);
		CtInsertColumn(ct, _UU("SM_HUB_COLUMN_9"), false);
		CtInsertColumn(ct, _UU("SM_HUB_COLUMN_10"), false);
		CtInsertColumn(ct, _UU("SM_HUB_COLUMN_11"), false);
		CtInsertColumn(ct, _UU("SM_SESS_COLUMN_6"), false);
		CtInsertColumn(ct, _UU("SM_SESS_COLUMN_7"), false);

		for (i = 0;i < t.NumHub;i++)
		{
			RPC_ENUM_HUB_ITEM *e = &t.Hubs[i];
			wchar_t name[MAX_HUBNAME_LEN + 1];
			wchar_t s1[64], s2[64], s3[64], s4[64], s5[64];
			wchar_t s6[64], s7[128], s8[128];
			wchar_t s9[64], s10[64];

			UniToStru(s1, e->NumUsers);
			UniToStru(s2, e->NumGroups);
			UniToStru(s3, e->NumSessions);
			UniToStru(s4, e->NumMacTables);
			UniToStru(s5, e->NumIpTables);

			UniToStru(s6, e->NumLogin);

			if (e->LastLoginTime != 0)
			{
				GetDateTimeStr64Uni(s7, sizeof(s7), SystemToLocal64(e->LastLoginTime));
			}
			else
			{
				UniStrCpy(s7, sizeof(s7), _UU("COMMON_UNKNOWN"));
			}

			if (e->LastCommTime != 0)
			{
				GetDateTimeStr64Uni(s8, sizeof(s8), SystemToLocal64(e->LastCommTime));
			}
			else
			{
				UniStrCpy(s8, sizeof(s8), _UU("COMMON_UNKNOWN"));
			}

			if (e->IsTrafficFilled == false)
			{
				UniStrCpy(s9, sizeof(s9), _UU("CM_ST_NONE"));
				UniStrCpy(s10, sizeof(s10), _UU("CM_ST_NONE"));
			}
			else
			{
				UniToStr3(s9, sizeof(s9),
					e->Traffic.Recv.BroadcastBytes + e->Traffic.Recv.UnicastBytes +
					e->Traffic.Send.BroadcastBytes + e->Traffic.Send.UnicastBytes);

				UniToStr3(s10, sizeof(s10),
					e->Traffic.Recv.BroadcastCount + e->Traffic.Recv.UnicastCount +
					e->Traffic.Send.BroadcastCount + e->Traffic.Send.UnicastCount);
			}

			StrToUni(name, sizeof(name), e->HubName);

			CtInsert(ct,
				name,
				e->Online ? _UU("SM_HUB_ONLINE") : _UU("SM_HUB_OFFLINE"),
				GetHubTypeStr(e->HubType),
				s1, s2, s3, s4, s5, s6, s7, s8, s9, s10);
		}

		CtFreeEx(ct, c, true);
	}

	FreeRpcEnumHub(&t);

	FreeParamValueList(o);

	return 0;
}