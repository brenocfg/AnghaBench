#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp4 ;
typedef  int /*<<< orphan*/  tmp3 ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_18__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,char*) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_16__ {scalar_t__ NumItem; TYPE_1__* Items; } ;
struct TYPE_15__ {char* FilePath; char* ServerName; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  FileSize; } ;
typedef  TYPE_1__ RPC_ENUM_LOG_FILE_ITEM ;
typedef  TYPE_2__ RPC_ENUM_LOG_FILE ;
typedef  TYPE_3__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CtFreeEx (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumLogFile (TYPE_2__*) ; 
 int /*<<< orphan*/  GetDateTimeStr64Uni (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HOST_NAME_LEN ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScEnumLogFile (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrToUni (char*,int,char*) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ToStrByte (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,char*) ; 

UINT PsLogFileList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ENUM_LOG_FILE t;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	c->Write(c, _UU("CMD_LogFileList_START"));
	c->Write(c, L"");

	// RPC call
	ret = ScEnumLogFile(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		UINT i;
		wchar_t tmp[MAX_SIZE];
		CT *ct;

		UniFormat(tmp, sizeof(tmp), _UU("CMD_LogFileList_NUM_LOGS"), t.NumItem);
		c->Write(c, tmp);

		ct = CtNew();

		CtInsertColumn(ct, _UU("SM_LOG_FILE_COLUMN_1"), false);
		CtInsertColumn(ct, _UU("SM_LOG_FILE_COLUMN_2"), true);
		CtInsertColumn(ct, _UU("SM_LOG_FILE_COLUMN_3"), false);
		CtInsertColumn(ct, _UU("SM_LOG_FILE_COLUMN_4"), false);

		for (i = 0;i < t.NumItem;i++)
		{
			RPC_ENUM_LOG_FILE_ITEM *e = &t.Items[i];
			wchar_t tmp1[MAX_PATH], tmp2[128], tmp3[128], tmp4[MAX_HOST_NAME_LEN + 1];
			char tmp[MAX_SIZE];

			StrToUni(tmp1, sizeof(tmp1), e->FilePath);

			ToStrByte(tmp, sizeof(tmp), e->FileSize);
			StrToUni(tmp2, sizeof(tmp2), tmp);

			GetDateTimeStr64Uni(tmp3, sizeof(tmp3), SystemToLocal64(e->UpdatedTime));

			StrToUni(tmp4, sizeof(tmp4), e->ServerName);

			CtInsert(ct, tmp1, tmp2, tmp3, tmp4);
		}

		CtFreeEx(ct, c, true);
	}

	FreeRpcEnumLogFile(&t);

	FreeParamValueList(o);

	return 0;
}