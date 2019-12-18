#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp5 ;
typedef  int /*<<< orphan*/  tmp4 ;
typedef  int /*<<< orphan*/  tmp3 ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_19__ {int /*<<< orphan*/  (* Write ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_18__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; } ;
struct TYPE_17__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_16__ {scalar_t__ NumIpTable; TYPE_1__* IpTables; int /*<<< orphan*/  HubName; } ;
struct TYPE_15__ {char* SessionName; int DhcpAllocated; char* RemoteHostname; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  IpV6; int /*<<< orphan*/  Key; } ;
typedef  TYPE_1__ RPC_ENUM_IP_TABLE_ITEM ;
typedef  TYPE_2__ RPC_ENUM_IP_TABLE ;
typedef  TYPE_3__ PS ;
typedef  TYPE_4__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_5__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  CtFreeEx (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumIpTable (TYPE_2__*) ; 
 int /*<<< orphan*/  GetDateTimeStr64Uni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_5__*,char*,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 scalar_t__ ScEnumIpTable (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 

UINT PsIpTable(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ENUM_IP_TABLE t;
	UINT i;

	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[session_name]", NULL, NULL, NULL, NULL,}
	};

	// If virtual HUB is not selected, it's an error
	if (ps->HubName == NULL)
	{
		c->Write(c, _UU("CMD_Hub_Not_Selected"));
		return ERR_INVALID_PARAMETER;
	}

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));
	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);

	// RPC call
	ret = ScEnumIpTable(ps->Rpc, &t);

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
		char *session_name = GetParamStr(o, "[session_name]");

		if (IsEmptyStr(session_name))
		{
			session_name = NULL;
		}

		CtInsertColumn(ct, _UU("CMD_ID"), false);
		CtInsertColumn(ct, _UU("SM_IP_COLUMN_1"), false);
		CtInsertColumn(ct, _UU("SM_IP_COLUMN_2"), false);
		CtInsertColumn(ct, _UU("SM_IP_COLUMN_3"), false);
		CtInsertColumn(ct, _UU("SM_IP_COLUMN_4"), false);
		CtInsertColumn(ct, _UU("SM_IP_COLUMN_5"), false);

		for (i = 0;i < t.NumIpTable;i++)
		{
			char str[MAX_SIZE];
			wchar_t tmp0[128];
			wchar_t tmp1[MAX_SIZE];
			wchar_t tmp2[MAX_SIZE];
			wchar_t tmp3[MAX_SIZE];
			wchar_t tmp4[MAX_SIZE];
			wchar_t tmp5[MAX_SIZE];
			RPC_ENUM_IP_TABLE_ITEM *e = &t.IpTables[i];

			if (session_name == NULL || StrCmpi(e->SessionName, session_name) == 0)
			{
				UniToStru(tmp0, e->Key);

				StrToUni(tmp1, sizeof(tmp1), e->SessionName);

				if (e->DhcpAllocated == false)
				{
					IPToStr(str, sizeof(str), &e->IpV6);
					StrToUni(tmp2, sizeof(tmp2), str);
				}
				else
				{
					IPToStr(str, sizeof(str), &e->IpV6);
					UniFormat(tmp2, sizeof(tmp2), _UU("SM_MAC_IP_DHCP"), str);
				}

				GetDateTimeStr64Uni(tmp3, sizeof(tmp3), SystemToLocal64(e->CreatedTime));

				GetDateTimeStr64Uni(tmp4, sizeof(tmp4), SystemToLocal64(e->UpdatedTime));

				if (StrLen(e->RemoteHostname) == 0)
				{
					UniStrCpy(tmp5, sizeof(tmp5), _UU("SM_MACIP_LOCAL"));
				}
				else
				{
					UniFormat(tmp5, sizeof(tmp5), _UU("SM_MACIP_SERVER"), e->RemoteHostname);
				}

				CtInsert(ct,
					tmp0, tmp1, tmp2, tmp3, tmp4, tmp5);
			}
		}

		CtFreeEx(ct, c, true);
	}

	FreeRpcEnumIpTable(&t);

	FreeParamValueList(o);

	return 0;
}