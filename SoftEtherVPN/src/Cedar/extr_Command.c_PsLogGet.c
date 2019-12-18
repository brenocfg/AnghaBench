#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,char*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_12__ {int* PacketLogConfig; int /*<<< orphan*/  PacketLogSwitchType; scalar_t__ SavePacketLog; int /*<<< orphan*/  SecurityLogSwitchType; scalar_t__ SaveSecurityLog; } ;
struct TYPE_13__ {TYPE_1__ LogSetting; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_2__ RPC_HUB_LOG ;
typedef  TYPE_3__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 char* GetLogSwitchStr (int /*<<< orphan*/ ) ; 
 char* GetPacketLogNameStr (scalar_t__) ; 
#define  PACKET_LOG_ALL 130 
#define  PACKET_LOG_HEADER 129 
#define  PACKET_LOG_NONE 128 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScGetHubLog (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,char*) ; 

UINT PsLogGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_HUB_LOG t;

	// If virtual HUB is not selected, it's an error
	if (ps->HubName == NULL)
	{
		c->Write(c, _UU("CMD_Hub_Not_Selected"));
		return ERR_INVALID_PARAMETER;
	}

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
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
	else
	{
		CT *ct = CtNewStandard();

		CtInsert(ct, _UU("CMD_Log_SecurityLog"),
			t.LogSetting.SaveSecurityLog ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));
		if (t.LogSetting.SaveSecurityLog)
		{
			CtInsert(ct, _UU("CMD_Log_SwitchType"), GetLogSwitchStr(t.LogSetting.SecurityLogSwitchType));
		}

		CtInsert(ct, L"", L"");

		CtInsert(ct, _UU("CMD_Log_PacketLog"),
			t.LogSetting.SavePacketLog ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));
		if (t.LogSetting.SavePacketLog)
		{
			UINT i;

			CtInsert(ct, _UU("CMD_Log_SwitchType"), GetLogSwitchStr(t.LogSetting.PacketLogSwitchType));

			for (i = 0;i <= 7;i++)
			{
				wchar_t *tmp = NULL;

				switch (t.LogSetting.PacketLogConfig[i])
				{
				case PACKET_LOG_NONE:
					tmp = _UU("D_SM_LOG@B_PACKET_0_0");
					break;

				case PACKET_LOG_HEADER:
					tmp = _UU("D_SM_LOG@B_PACKET_0_1");
					break;

				case PACKET_LOG_ALL:
					tmp = _UU("D_SM_LOG@B_PACKET_0_2");
					break;
				}

				CtInsert(ct, GetPacketLogNameStr(i),
					tmp);
			}
		}

		CtFree(ct, c);
	}

	FreeParamValueList(o);

	return 0;
}