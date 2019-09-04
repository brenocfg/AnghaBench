#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_20__ {scalar_t__ NumTokens; char** Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  scalar_t__ UINT ;
struct TYPE_24__ {int /*<<< orphan*/  (* Write ) (TYPE_5__*,char*) ;} ;
struct TYPE_23__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; } ;
struct TYPE_22__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_21__ {scalar_t__ FileData; int /*<<< orphan*/  FileName; } ;
typedef  TYPE_2__ RPC_CONFIG ;
typedef  TYPE_3__ PS ;
typedef  TYPE_4__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IO ;
typedef  TYPE_5__ CONSOLE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ CalcUtf8ToUni (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_5__*,scalar_t__) ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileCreateW (char*) ; 
 int /*<<< orphan*/  FileWrite (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcConfig (TYPE_2__*) ; 
 char* GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ IsEmptyUniStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_5__*,char*,char*,TYPE_4__*,int) ; 
 scalar_t__ ScGetConfig (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrLen (scalar_t__) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFreeToken (TYPE_1__*) ; 
 TYPE_1__* UniGetLines (char*) ; 
 int /*<<< orphan*/  Utf8ToUni (char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 char* ZeroMalloc (scalar_t__) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_5__*,char*) ; 

UINT PsConfigGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_CONFIG t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[path]", NULL, NULL, NULL, NULL},
	};

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScGetConfig(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		wchar_t *filename = GetParamUniStr(o, "[path]");

		if (IsEmptyUniStr(filename))
		{
			// Display on the screen
			wchar_t tmp[MAX_SIZE];
			UINT buf_size;
			wchar_t *buf;
			UNI_TOKEN_LIST *lines;

			UniFormat(tmp, sizeof(tmp), _UU("CMD_ConfigGet_FILENAME"), t.FileName,
				StrLen(t.FileData));
			c->Write(c, tmp);
			c->Write(c, L"");

			buf_size = CalcUtf8ToUni((BYTE *)t.FileData, StrLen(t.FileData));
			buf = ZeroMalloc(buf_size + 32);

			Utf8ToUni(buf, buf_size, (BYTE *)t.FileData, StrLen(t.FileData));

			lines = UniGetLines(buf);
			if (lines != NULL)
			{
				UINT i;

				for (i = 0;i < lines->NumTokens;i++)
				{
					c->Write(c, lines->Token[i]);
				}

				UniFreeToken(lines);
			}

			c->Write(c, L"");

			Free(buf);
		}
		else
		{
			// Save to the file
			IO *io = FileCreateW(filename);

			if (io == NULL)
			{
				c->Write(c, _UU("CMD_ConfigGet_FILE_SAVE_FAILED"));

				ret = ERR_INTERNAL_ERROR;
			}
			else
			{
				FileWrite(io, t.FileData, StrLen(t.FileData));
				FileClose(io);
			}
		}
	}

	FreeRpcConfig(&t);

	FreeParamValueList(o);

	return ret;
}