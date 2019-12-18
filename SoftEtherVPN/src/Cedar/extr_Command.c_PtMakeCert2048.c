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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  args ;
typedef  int /*<<< orphan*/  X_SERIAL ;
typedef  int /*<<< orphan*/  X ;
typedef  scalar_t__ UINT ;
struct TYPE_18__ {int Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_17__ {char* member_0; int member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* Write ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_15__ {char* member_0; TYPE_3__* member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ PARAM ;
typedef  int /*<<< orphan*/  NAME ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  K ;
typedef  TYPE_2__ CONSOLE ;
typedef  TYPE_3__ CMD_EVAL_MIN_MAX ;
typedef  TYPE_4__ BUF ;

/* Variables and functions */
 int CheckXandK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CmdEvalIsFile ; 
 int /*<<< orphan*/ * CmdEvalMinMax ; 
 int /*<<< orphan*/ * CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/ * CmdPrompt ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/ * FileToKW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileToXW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_4__*) ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeXSerial (int /*<<< orphan*/ *) ; 
 scalar_t__ GetParamInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int IsEmptyStr (int /*<<< orphan*/ ) ; 
 int KToFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewRootX (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewX (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewXSerial (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_2__*,char*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  RsaGen (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 TYPE_4__* StrToBin (int /*<<< orphan*/ ) ; 
 int XToFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ *) ; 

UINT PtMakeCert2048(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	UINT ret = ERR_NO_ERROR;
	X *x = NULL;
	K *pub = NULL;
	K *pri = NULL;
	NAME *n;
	X_SERIAL *x_serial = NULL;
	BUF *buf;
	UINT days;
	X *root_x = NULL;
	K *root_k = NULL;
	// Parameter list that can be specified
	CMD_EVAL_MIN_MAX minmax =
	{
		"CMD_MakeCert_EVAL_EXPIRES",
		0,
		10950,
	};
	PARAM args[] =
	{
		{"CN", CmdPrompt, _UU("CMD_MakeCert_PROMPT_CN"), NULL, NULL},
		{"O", CmdPrompt, _UU("CMD_MakeCert_PROMPT_O"), NULL, NULL},
		{"OU", CmdPrompt, _UU("CMD_MakeCert_PROMPT_OU"), NULL, NULL},
		{"C", CmdPrompt, _UU("CMD_MakeCert_PROMPT_C"), NULL, NULL},
		{"ST", CmdPrompt, _UU("CMD_MakeCert_PROMPT_ST"), NULL, NULL},
		{"L", CmdPrompt, _UU("CMD_MakeCert_PROMPT_L"), NULL, NULL},
		{"SERIAL", CmdPrompt, _UU("CMD_MakeCert_PROMPT_SERIAL"), NULL, NULL},
		{"EXPIRES", CmdPrompt, _UU("CMD_MakeCert_PROMPT_EXPIRES"), CmdEvalMinMax, &minmax},
		{"SIGNCERT", NULL, NULL, CmdEvalIsFile, NULL},
		{"SIGNKEY", NULL, NULL, CmdEvalIsFile, NULL},
		{"SAVECERT", CmdPrompt, _UU("CMD_MakeCert_PROMPT_SAVECERT"), CmdEvalNotEmpty, NULL},
		{"SAVEKEY", CmdPrompt, _UU("CMD_MakeCert_PROMPT_SAVEKEY"), CmdEvalNotEmpty, NULL},
	};

	// Get the parameter list
	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	if (IsEmptyStr(GetParamStr(o, "SIGNCERT")) == false && IsEmptyStr(GetParamStr(o, "SIGNKEY")) == false)
	{
		root_x = FileToXW(GetParamUniStr(o, "SIGNCERT"));
		root_k = FileToKW(GetParamUniStr(o, "SIGNKEY"), true, NULL);

		if (root_x == NULL || root_k == NULL || CheckXandK(root_x, root_k) == false)
		{
			ret = ERR_INTERNAL_ERROR;

			c->Write(c, _UU("CMD_MakeCert_ERROR_SIGNKEY"));
		}
	}

	if (ret == ERR_NO_ERROR)
	{
		buf = StrToBin(GetParamStr(o, "SERIAL"));
		if (buf != NULL && buf->Size >= 1)
		{
			x_serial = NewXSerial(buf->Buf, buf->Size);
		}
		FreeBuf(buf);

		n = NewName(GetParamUniStr(o, "CN"), GetParamUniStr(o, "O"), GetParamUniStr(o, "OU"), 
			GetParamUniStr(o, "C"), GetParamUniStr(o, "ST"), GetParamUniStr(o, "L"));

		days = GetParamInt(o, "EXPIRES");
		if (days == 0)
		{
			days = 3650;
		}

		RsaGen(&pri, &pub, 2048);

		if (root_x == NULL)
		{
			x = NewRootX(pub, pri, n, days, x_serial);
		}
		else
		{
			x = NewX(pub, root_k, root_x, n, days, x_serial);
		}

		FreeXSerial(x_serial);
		FreeName(n);

		if (x == NULL)
		{
			ret = ERR_INTERNAL_ERROR;
			c->Write(c, _UU("CMD_MakeCert_ERROR_GEN_FAILED"));
		}
		else
		{
			if (XToFileW(x, GetParamUniStr(o, "SAVECERT"), true) == false)
			{
				c->Write(c, _UU("CMD_SAVECERT_FAILED"));
			}
			else if (KToFileW(pri, GetParamUniStr(o, "SAVEKEY"), true, NULL) == false)
			{
				c->Write(c, _UU("CMD_SAVEKEY_FAILED"));
			}
		}
	}

	if (ret != ERR_NO_ERROR)
	{
		// Error has occurred
		CmdPrintError(c, ret);
	}

	// Release of the parameter list
	FreeParamValueList(o);

	FreeX(root_x);
	FreeK(root_k);

	FreeX(x);
	FreeK(pri);
	FreeK(pub);

	return ret;
}