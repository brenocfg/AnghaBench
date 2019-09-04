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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_8__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_7__ {int /*<<< orphan*/  Guid; int /*<<< orphan*/  FileName; int /*<<< orphan*/  Version; int /*<<< orphan*/  MacAddress; scalar_t__ Enabled; int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_1__ RPC_CLIENT_GET_VLAN ;
typedef  TYPE_2__ PC ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 scalar_t__ CcGetVLan (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PcNicGetSetting(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_GET_VLAN t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		{"[name]", CmdPrompt, _UU("CMD_NicCreate_PROMPT_NAME"), CmdEvalNotEmpty, NULL},
	};

	// Get the parameter list
	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// RPC call
	Zero(&t, sizeof(t));
	StrCpy(t.DeviceName, sizeof(t.DeviceName), GetParamStr(o, "[name]"));

	ret = CcGetVLan(pc->RemoteClient, &t);

	if (ret == ERR_NO_ERROR)
	{
		// Success
		CT *ct = CtNewStandard();
		wchar_t tmp[MAX_SIZE];

		StrToUni(tmp, sizeof(tmp), t.DeviceName);
		CtInsert(ct, _UU("CMD_NicGetSetting_1"), tmp);

		CtInsert(ct, _UU("CMD_NicGetSetting_2"), t.Enabled ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));

		StrToUni(tmp, sizeof(tmp), t.MacAddress);
		CtInsert(ct, _UU("CMD_NicGetSetting_3"), tmp);

		StrToUni(tmp, sizeof(tmp), t.Version);
		CtInsert(ct, _UU("CMD_NicGetSetting_4"), tmp);

		StrToUni(tmp, sizeof(tmp), t.FileName);
		CtInsert(ct, _UU("CMD_NicGetSetting_5"), tmp);

		StrToUni(tmp, sizeof(tmp), t.Guid);
		CtInsert(ct, _UU("CMD_NicGetSetting_6"), tmp);

		CtFree(ct, c);
	}

	if (ret != ERR_NO_ERROR)
	{
		// Error has occurred
		CmdPrintError(c, ret);
	}

	// Release of the parameter list
	FreeParamValueList(o);

	return ret;
}