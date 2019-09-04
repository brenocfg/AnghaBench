#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_21__ {int /*<<< orphan*/  Size; scalar_t__ Buf; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* Write ) (TYPE_3__*,char*) ;} ;
struct TYPE_19__ {char* member_0; char* member_2; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_1; } ;
struct TYPE_18__ {int /*<<< orphan*/  Rpc; } ;
typedef  TYPE_1__ PS ;
typedef  TYPE_2__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ CONSOLE ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_4__ BUF ;

/* Variables and functions */
 scalar_t__ CalcUtf8ToUni (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CmdEvalNotEmpty ; 
 int /*<<< orphan*/ * CmdPrompt ; 
 TYPE_4__* DownloadFileFromServer (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DumpBuf (TYPE_4__*,char*) ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_4__*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_3__*,char*,char*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Utf8ToUni (char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* ZeroMalloc (scalar_t__) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__*,char*) ; 

UINT PsLogFileGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	BUF *buf;
	char *filename = NULL;
	char *server_name;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[name]", CmdPrompt, _UU("CMD_LogFileGet_PROMPT_NAME"), CmdEvalNotEmpty, NULL},
		{"SERVER", NULL, NULL, NULL, NULL},
		{"SAVEPATH", NULL, NULL, NULL, NULL},
	};

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	filename = GetParamStr(o, "SAVE");
	if (IsEmptyStr(filename))
	{
		filename = GetParamStr(o, "SAVEPATH");
	}

	c->Write(c, _UU("CMD_LogFileGet_START"));

	server_name = GetParamStr(o, "SERVER");

	buf = DownloadFileFromServer(ps->Rpc, server_name,
		GetParamStr(o, "[name]"), 0, NULL, NULL);

	if (buf == NULL)
	{
		c->Write(c, _UU("CMD_LogFileGet_FAILED"));

		ret = ERR_INTERNAL_ERROR;
	}
	else
	{
		if (IsEmptyStr(filename) == false)
		{
			// Save to the file
			if (DumpBuf(buf, filename) == false)
			{
				ret = ERR_INTERNAL_ERROR;
				c->Write(c, _UU("CMD_LogFileGet_SAVE_FAILED"));
			}
		}
		else
		{
			// Display on the screen
			wchar_t tmp[MAX_SIZE];
			UINT buf_size;
			wchar_t *uni_buf;

			UniFormat(tmp, sizeof(tmp), _UU("CMD_LogFileGet_FILESIZE"),
				buf->Size);
			c->Write(c, tmp);
			c->Write(c, L"");

			buf_size = CalcUtf8ToUni((BYTE *)buf->Buf, buf->Size);
			uni_buf = ZeroMalloc(buf_size + 32);

			Utf8ToUni(uni_buf, buf_size, (BYTE *)buf->Buf, buf->Size);

			c->Write(c, uni_buf);
			c->Write(c, L"");

			Free(uni_buf);
		}

		FreeBuf(buf);
	}

	FreeParamValueList(o);

	return ret;
}