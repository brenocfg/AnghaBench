#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_13__ {int /*<<< orphan*/  (* Write ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_11__ {scalar_t__ HubType; scalar_t__ LastLoginTime; scalar_t__ LastCommTime; scalar_t__ CreatedTime; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  NumIpTables; int /*<<< orphan*/  NumMacTables; int /*<<< orphan*/  NumGroups; int /*<<< orphan*/  NumUsers; int /*<<< orphan*/  NumAccessLists; int /*<<< orphan*/  NumSessionsBridge; int /*<<< orphan*/  NumSessionsClient; int /*<<< orphan*/  NumSessions; scalar_t__ SecureNATEnabled; scalar_t__ Online; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_HUB_STATUS ;
typedef  TYPE_2__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_3__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdInsertTrafficInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/ * CopyStrToUni (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDateTimeStr64Uni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetHubTypeStr (scalar_t__) ; 
 scalar_t__ HUB_TYPE_STANDALONE ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_3__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScGetHubStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SystemToLocal64 (scalar_t__) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

UINT PsStatusGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_HUB_STATUS t;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// If virtual HUB is not selected, it's an error
	if (ps->HubName == NULL)
	{
		c->Write(c, _UU("CMD_Hub_Not_Selected"));
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);

	// RPC call
	ret = ScGetHubStatus(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		CT *ct = CtNewStandard();
		wchar_t *s;
		wchar_t tmp[MAX_SIZE];

		// HUB name
		s = CopyStrToUni(t.HubName);
		CtInsert(ct, _UU("SM_HUB_STATUS_HUBNAME"), s);
		Free(s);

		// Online
		CtInsert(ct, _UU("SM_HUB_STATUS_ONLINE"),
			t.Online ? _UU("SM_HUB_ONLINE") : _UU("SM_HUB_OFFLINE"));

		// Type of HUB
		CtInsert(ct, _UU("SM_HUB_TYPE"),
			GetHubTypeStr(t.HubType));

		if (t.HubType == HUB_TYPE_STANDALONE)
		{
			// Enable / Disable the SecureNAT
			CtInsert(ct, _UU("SM_HUB_SECURE_NAT"),
				t.SecureNATEnabled ? _UU("SM_HUB_SECURE_NAT_YES") : _UU("SM_HUB_SECURE_NAT_NO"));
		}

		// Other values
		UniToStru(tmp, t.NumSessions);
		CtInsert(ct, _UU("SM_HUB_NUM_SESSIONS"), tmp);

		if (t.NumSessionsClient != 0 || t.NumSessionsBridge != 0)
		{
			UniToStru(tmp, t.NumSessionsClient);
			CtInsert(ct, _UU("SM_HUB_NUM_SESSIONS_CLIENT"), tmp);
			UniToStru(tmp, t.NumSessionsBridge);
			CtInsert(ct, _UU("SM_HUB_NUM_SESSIONS_BRIDGE"), tmp);
		}

		UniToStru(tmp, t.NumAccessLists);
		CtInsert(ct, _UU("SM_HUB_NUM_ACCESSES"), tmp);

		UniToStru(tmp, t.NumUsers);
		CtInsert(ct, _UU("SM_HUB_NUM_USERS"), tmp);
		UniToStru(tmp, t.NumGroups);
		CtInsert(ct, _UU("SM_HUB_NUM_GROUPS"), tmp);

		UniToStru(tmp, t.NumMacTables);
		CtInsert(ct, _UU("SM_HUB_NUM_MAC_TABLES"), tmp);
		UniToStru(tmp, t.NumIpTables);
		CtInsert(ct, _UU("SM_HUB_NUM_IP_TABLES"), tmp);

		// Usage status
		UniToStru(tmp, t.NumLogin);
		CtInsert(ct, _UU("SM_HUB_NUM_LOGIN"), tmp);

		if (t.LastLoginTime != 0)
		{
			GetDateTimeStr64Uni(tmp, sizeof(tmp), SystemToLocal64(t.LastLoginTime));
		}
		else
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("COMMON_UNKNOWN"));
		}
		CtInsert(ct, _UU("SM_HUB_LAST_LOGIN_TIME"), tmp);

		if (t.LastCommTime != 0)
		{
			GetDateTimeStr64Uni(tmp, sizeof(tmp), SystemToLocal64(t.LastCommTime));
		}
		else
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("COMMON_UNKNOWN"));
		}
		CtInsert(ct, _UU("SM_HUB_LAST_COMM_TIME"), tmp);

		if (t.CreatedTime != 0)
		{
			GetDateTimeStr64Uni(tmp, sizeof(tmp), SystemToLocal64(t.CreatedTime));
		}
		else
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("COMMON_UNKNOWN"));
		}
		CtInsert(ct, _UU("SM_HUB_CREATED_TIME"), tmp);

		// Traffic information
		CmdInsertTrafficInfo(ct, &t.Traffic);

		CtFree(ct, c);
	}

	FreeParamValueList(o);

	return 0;
}