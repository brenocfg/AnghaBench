#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_16__ {int /*<<< orphan*/  Mask; int /*<<< orphan*/  Ip; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ VH_OPTION ;
typedef  scalar_t__ UINT ;
struct TYPE_20__ {int Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_18__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_17__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ CONSOLE ;
typedef  TYPE_5__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * CmdEvalIp ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeBuf (TYPE_5__*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int IsEmptyStr (char*) ; 
 int IsIpStr4 (char*) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ ScGetSecureNATOption (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ScSetSecureNATOption (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_5__* StrToBin (char*) ; 
 int /*<<< orphan*/  StrToIP (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ StrToIP32 (char*) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

UINT PsSecureNatHostSet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	VH_OPTION t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"MAC", CmdPrompt, _UU("CMD_SecureNatHostSet_Prompt_MAC"), NULL, NULL},
		{"IP", CmdPrompt, _UU("CMD_SecureNatHostSet_Prompt_IP"), CmdEvalIp, NULL},
		{"MASK", CmdPrompt, _UU("CMD_SecureNatHostSet_Prompt_MASK"), CmdEvalIp, NULL},
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
	ret = ScGetSecureNATOption(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		char *mac, *ip, *mask;
		bool ok = true;

		StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);

		mac = GetParamStr(o, "MAC");
		ip = GetParamStr(o, "IP");
		mask = GetParamStr(o, "MASK");

		if (IsEmptyStr(mac) == false)
		{
			BUF *b = StrToBin(mac);

			if (b == NULL || b->Size != 6)
			{
				ok = false;
			}
			else
			{
				Copy(t.MacAddress, b->Buf, 6);
			}

			FreeBuf(b);
		}

		if (IsEmptyStr(ip) == false)
		{
			if (IsIpStr4(ip) == false)
			{
				ok = false;
			}
			else
			{
				UINT u = StrToIP32(ip);

				if (u == 0 || u == 0xffffffff)
				{
					ok = false;
				}
				else
				{
					UINTToIP(&t.Ip, u);
				}
			}
		}

		if (IsEmptyStr(mask) == false)
		{
			if (IsIpStr4(mask) == false)
			{
				ok = false;
			}
			else
			{
				StrToIP(&t.Mask, mask);
			}
		}

		if (ok == false)
		{
			// Parameter is invalid
			ret = ERR_INVALID_PARAMETER;
			CmdPrintError(c, ret);
			FreeParamValueList(o);
			return ret;
		}
		else
		{
			ret = ScSetSecureNATOption(ps->Rpc, &t);

			if (ret != ERR_NO_ERROR)
			{
				// An error has occured
				CmdPrintError(c, ret);
				FreeParamValueList(o);
				return ret;
			}
		}
	}

	FreeParamValueList(o);

	return 0;
}