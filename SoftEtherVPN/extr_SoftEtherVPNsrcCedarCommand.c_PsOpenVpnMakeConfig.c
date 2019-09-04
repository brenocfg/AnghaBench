#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_16__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_15__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_14__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_13__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ RPC_READ_LOG_FILE ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int DumpBufW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcReadLogFile (TYPE_1__*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ ScMakeOpenVpnConfigFile (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int UniEndWith (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCat (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *) ; 

UINT PsOpenVpnMakeConfig(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_READ_LOG_FILE t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[ZIP_FileName]", CmdPrompt, _UU("CMD_OpenVpnMakeConfig_Prompt_ZIP"), CmdEvalNotEmpty, NULL},
	};

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScMakeOpenVpnConfigFile(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		// Determine the file name to save
		wchar_t filename[MAX_SIZE];
		wchar_t tmp[MAX_SIZE];

		UniStrCpy(filename, sizeof(filename), GetParamUniStr(o, "[ZIP_FileName]"));

		if (UniEndWith(filename, L".zip") == false)
		{
			UniStrCat(filename, sizeof(filename), L".zip");
		}

		if (DumpBufW(t.Buffer, filename) == false)
		{
			ret = ERR_INTERNAL_ERROR;

			UniFormat(tmp, sizeof(tmp), _UU("CMD_OpenVpnMakeConfig_ERROR"), filename);
		}
		else
		{
			UniFormat(tmp, sizeof(tmp), _UU("CMD_OpenVpnMakeConfig_OK"), filename);
		}

		c->Write(c, tmp);

		FreeRpcReadLogFile(&t);
	}

	FreeParamValueList(o);

	return ret;
}