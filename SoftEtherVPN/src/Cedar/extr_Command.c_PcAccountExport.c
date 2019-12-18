#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  z ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  bom ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;
struct TYPE_26__ {int* Buf; int Size; } ;
struct TYPE_25__ {int /*<<< orphan*/  (* Write ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_24__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_23__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_22__ {int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  ClientOption; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ RPC_CLIENT_GET_ACCOUNT ;
typedef  TYPE_1__ RPC_CLIENT_CREATE_ACCOUNT ;
typedef  TYPE_3__ PC ;
typedef  TYPE_4__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_5__ CONSOLE ;
typedef  TYPE_6__ BUF ;

/* Variables and functions */
 scalar_t__ CalcUniToUtf8 (int /*<<< orphan*/ ) ; 
 scalar_t__ CcGetAccount (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_6__* CiAccountToCfg (TYPE_1__*) ; 
 int /*<<< orphan*/  CiFreeClientGetAccount (TYPE_1__*) ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int DumpBuf (TYPE_6__*,char*) ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (int*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_6__*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int MAX_SIZE ; 
 TYPE_6__* NewBuf () ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_5__*,char*,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ ) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToUtf8 (int*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_6__*,int*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int* ZeroMalloc (scalar_t__) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 

UINT PcAccountExport(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_GET_ACCOUNT t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		{"[name]", CmdPrompt, _UU("CMD_AccountCreate_Prompt_Name"), CmdEvalNotEmpty, NULL},
		{"SAVEPATH", CmdPrompt, _UU("CMD_AccountExport_PROMPT_SAVEPATH"), CmdEvalNotEmpty, NULL},
	};

	// Get the parameter list
	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// RPC call
	Zero(&t, sizeof(t));

	UniStrCpy(t.AccountName, sizeof(t.AccountName), GetParamUniStr(o, "[name]"));

	ret = CcGetAccount(pc->RemoteClient, &t);

	if (ret == ERR_NO_ERROR)
	{
		RPC_CLIENT_CREATE_ACCOUNT z;
		BUF *b;
		BUF *b2;
		char tmp[MAX_SIZE];
		UCHAR *buf;
		UINT buf_size;
		UCHAR bom[] = {0xef, 0xbb, 0xbf, };

		Zero(&z, sizeof(z));
		z.CheckServerCert = t.CheckServerCert;
		z.ClientAuth = t.ClientAuth;
		z.ClientOption = t.ClientOption;
		z.ServerCert = t.ServerCert;
		z.StartupAccount = t.StartupAccount;

		b = CiAccountToCfg(&z);

		StrCpy(tmp, sizeof(tmp), GetParamStr(o, "SAVEPATH"));
		b2 = NewBuf();

		WriteBuf(b2, bom, sizeof(bom));

		// Add the header part
		buf_size = CalcUniToUtf8(_UU("CM_ACCOUNT_FILE_BANNER"));
		buf = ZeroMalloc(buf_size + 32);
		UniToUtf8(buf, buf_size, _UU("CM_ACCOUNT_FILE_BANNER"));

		WriteBuf(b2, buf, StrLen((char *)buf));
		WriteBuf(b2, b->Buf, b->Size);
		SeekBuf(b2, 0, 0);

		FreeBuf(b);

		if (DumpBuf(b2, tmp) == false)
		{
			c->Write(c, _UU("CMD_SAVEFILE_FAILED"));
			ret = ERR_INTERNAL_ERROR;
		}

		FreeBuf(b2);
		Free(buf);
	}

	if (ret != ERR_NO_ERROR)
	{
		// Error has occurred
		CmdPrintError(c, ret);
	}

	CiFreeClientGetAccount(&t);

	// Release of the parameter list
	FreeParamValueList(o);

	return ret;
}