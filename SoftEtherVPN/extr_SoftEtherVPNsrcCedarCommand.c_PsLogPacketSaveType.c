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
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_19__ {int /*<<< orphan*/  (* Write ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_18__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_17__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_15__ {scalar_t__* PacketLogConfig; } ;
struct TYPE_16__ {TYPE_1__ LogSetting; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_2__ RPC_HUB_LOG ;
typedef  TYPE_3__ PS ;
typedef  TYPE_4__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_5__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamStr (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_5__*,char*,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 scalar_t__ ScGetHubLog (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ScSetHubLog (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ StrToPacketLogSaveInfoType (int /*<<< orphan*/ ) ; 
 scalar_t__ StrToPacketLogType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ ) ; 

UINT PsLogPacketSaveType(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_HUB_LOG t;
	UINT packet_type = INFINITE;
	UINT packet_save_info_type = INFINITE;
	// Parameter list that can be specified
	PARAM args[] =
	{
		{"TYPE", CmdPrompt, _UU("CMD_LogPacketSaveType_Prompt_TYPE"), NULL, NULL},
		{"SAVE", CmdPrompt, _UU("CMD_LogPacketSaveType_Prompt_SAVE"), NULL, NULL},
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
	
	packet_type = StrToPacketLogType(GetParamStr(o, "TYPE"));
	packet_save_info_type = StrToPacketLogSaveInfoType(GetParamStr(o, "SAVE"));

	if (packet_type == INFINITE || packet_save_info_type == INFINITE)
	{
		c->Write(c, _UU("CMD_LogEnable_Prompt_Error"));
		FreeParamValueList(o);
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);

	// RPC call
	ret = ScGetHubLog(ps->Rpc, &t);
	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	t.LogSetting.PacketLogConfig[packet_type] = packet_save_info_type;

	// RPC call
	ret = ScSetHubLog(ps->Rpc, &t);
	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	FreeParamValueList(o);

	return 0;
}