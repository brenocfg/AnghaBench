#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  mac_address ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_13__ {int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_1__ UCHAR ;
struct TYPE_16__ {int Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_15__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_14__ {int /*<<< orphan*/  RemoteClient; } ;
typedef  TYPE_1__ RPC_CLIENT_SET_VLAN ;
typedef  TYPE_3__ PC ;
typedef  TYPE_4__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CONSOLE ;
typedef  TYPE_5__ BUF ;

/* Variables and functions */
 scalar_t__ CcSetVLan (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  Copy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeBuf (TYPE_5__*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamStr (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ IsZero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  NormalizeMacAddress (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_5__* StrToBin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PcNicSetSetting(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_SET_VLAN t;
	UCHAR mac_address[6];
	BUF *b;
	// Parameter list that can be specified
	PARAM args[] =
	{
		{"[name]", CmdPrompt, _UU("CMD_NicCreate_PROMPT_NAME"), CmdEvalNotEmpty, NULL},
		{"MAC", CmdPrompt, _UU("CMD_NicSetSetting_PROMPT_MAC"), CmdEvalNotEmpty, NULL},
	};

	// Get the parameter list
	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// Inspect the MAC address
	Zero(mac_address, sizeof(mac_address));
	b = StrToBin(GetParamStr(o, "MAC"));
	if (b != NULL && b->Size == 6)
	{
		Copy(mac_address, b->Buf, 6);
	}
	FreeBuf(b);

	if (IsZero(mac_address, 6))
	{
		// MAC address is invalid
		FreeParamValueList(o);

		CmdPrintError(c, ERR_INVALID_PARAMETER);
		return ERR_INVALID_PARAMETER;
	}

	// RPC call
	Zero(&t, sizeof(t));
	StrCpy(t.DeviceName, sizeof(t.DeviceName), GetParamStr(o, "[name]"));
	NormalizeMacAddress(t.MacAddress, sizeof(t.MacAddress), GetParamStr(o, "MAC"));

	ret = CcSetVLan(pc->RemoteClient, &t);

	if (ret == ERR_NO_ERROR)
	{
		// Success
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