#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_21__ {int /*<<< orphan*/  (* Write ) (TYPE_5__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_20__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_19__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_18__ {TYPE_1__* ClientOption; } ;
struct TYPE_17__ {int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_2__ RPC_CLIENT_CREATE_ACCOUNT ;
typedef  TYPE_3__ PC ;
typedef  TYPE_4__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_5__ CONSOLE ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 scalar_t__ CcCreateAccount (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* CiCfgToAccount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiFreeClientCreateAccount (TYPE_2__*) ; 
 int /*<<< orphan*/  CmdEvalIsFile ; 
 int /*<<< orphan*/  CmdGenerateImportName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_5__*,char*,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/ * ReadDumpW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,int /*<<< orphan*/ *) ; 

UINT PcAccountImport(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	BUF *b;
	wchar_t name[MAX_SIZE];
	// Parameter list that can be specified
	PARAM args[] =
	{
		{"[path]", CmdPrompt, _UU("CMD_AccountImport_PROMPT_PATH"), CmdEvalIsFile, NULL},
	};

	// Get the parameter list
	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// Read the file
	b = ReadDumpW(GetParamUniStr(o, "[path]"));

	if (b == NULL)
	{
		// Read failure
		c->Write(c, _UU("CMD_LOADFILE_FAILED"));
		ret = ERR_INTERNAL_ERROR;
	}
	else
	{
		RPC_CLIENT_CREATE_ACCOUNT *t;

		t = CiCfgToAccount(b);

		if (t == NULL)
		{
			// Failed to parse
			c->Write(c, _UU("CMD_AccountImport_FAILED_PARSE"));
			ret = ERR_INTERNAL_ERROR;
		}
		else
		{
			CmdGenerateImportName(pc->RemoteClient, name, sizeof(name), t->ClientOption->AccountName);
			UniStrCpy(t->ClientOption->AccountName, sizeof(t->ClientOption->AccountName), name);

			ret = CcCreateAccount(pc->RemoteClient, t);

			if (ret == ERR_NO_ERROR)
			{
				wchar_t tmp[MAX_SIZE];

				UniFormat(tmp, sizeof(tmp), _UU("CMD_AccountImport_OK"), name);
				c->Write(c, tmp);
			}

			CiFreeClientCreateAccount(t);
			Free(t);
		}

		FreeBuf(b);
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