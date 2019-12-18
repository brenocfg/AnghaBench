#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_12__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_11__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_10__ {char* Hostname; scalar_t__ Point; scalar_t__ Weight; scalar_t__ NumPort; scalar_t__* Ports; scalar_t__ NumFarmHub; scalar_t__ NumSessions; scalar_t__ NumTcpConnections; TYPE_1__* FarmHubs; int /*<<< orphan*/  Ip; int /*<<< orphan*/  ConnectedTime; scalar_t__ Controller; int /*<<< orphan*/  Id; } ;
struct TYPE_9__ {scalar_t__ HubName; scalar_t__ DynamicHub; } ;
typedef  TYPE_2__ RPC_FARM_INFO ;
typedef  TYPE_3__ PS ;
typedef  TYPE_4__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcFarmInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  GetDateTimeStrEx64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  IPToStr32 (char*,int,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 scalar_t__ ScGetFarmInfo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  UniToInt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PsClusterMemberInfoGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_FARM_INFO t;
	CT *ct;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[id]", CmdPrompt, _UU("CMD_ClusterMemberInfoGet_PROMPT_ID"), NULL, NULL},
	};

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));
	t.Id = UniToInt(GetParamUniStr(o, "[id]"));

	// RPC call
	ret = ScGetFarmInfo(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	ct = CtNewStandard();

	{
		wchar_t tmp[MAX_SIZE];
		char str[MAX_SIZE];
		UINT i;

		CtInsert(ct, _UU("SM_FMINFO_TYPE"),
			t.Controller ? _UU("SM_FARM_CONTROLLER") : _UU("SM_FARM_MEMBER"));

		GetDateTimeStrEx64(tmp, sizeof(tmp), SystemToLocal64(t.ConnectedTime), NULL);
		CtInsert(ct, _UU("SM_FMINFO_CONNECT_TIME"), tmp);

		IPToStr32(str, sizeof(str), t.Ip);
		StrToUni(tmp, sizeof(tmp), str);
		CtInsert(ct, _UU("SM_FMINFO_IP"), tmp);

		StrToUni(tmp, sizeof(tmp), t.Hostname);
		CtInsert(ct, _UU("SM_FMINFO_HOSTNAME"), tmp);

		UniToStru(tmp, t.Point);
		CtInsert(ct, _UU("SM_FMINFO_POINT"), tmp);

		UniToStru(tmp, t.Weight);
		CtInsert(ct, _UU("SM_FMINFO_WEIGHT"), tmp);

		UniToStru(tmp, t.NumPort);
		CtInsert(ct, _UU("SM_FMINFO_NUM_PORT"), tmp);

		for (i = 0;i < t.NumPort;i++)
		{
			wchar_t tmp2[MAX_SIZE];
			UniFormat(tmp, sizeof(tmp), _UU("SM_FMINFO_PORT"), i + 1);
			UniToStru(tmp2, t.Ports[i]);
			CtInsert(ct, tmp, tmp2);
		}

		UniToStru(tmp, t.NumFarmHub);
		CtInsert(ct, _UU("SM_FMINFO_NUM_HUB"), tmp);

		for (i = 0;i < t.NumFarmHub;i++)
		{
			wchar_t tmp2[MAX_SIZE];
			UniFormat(tmp, sizeof(tmp), _UU("SM_FMINFO_HUB"), i + 1);
			UniFormat(tmp2, sizeof(tmp2),
				t.FarmHubs[i].DynamicHub ? _UU("SM_FMINFO_HUB_TAG_2") : _UU("SM_FMINFO_HUB_TAG_1"),
				t.FarmHubs[i].HubName);
			CtInsert(ct, tmp, tmp2);
		}

		UniToStru(tmp, t.NumSessions);
		CtInsert(ct, _UU("SM_FMINFO_NUM_SESSION"), tmp);

		UniToStru(tmp, t.NumTcpConnections);
		CtInsert(ct, _UU("SM_FMINFO_NUN_CONNECTION"), tmp);
	}

	CtFree(ct, c);

	FreeRpcFarmInfo(&t);

	FreeParamValueList(o);

	return 0;
}