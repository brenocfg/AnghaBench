#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_24__ {int Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_23__ {int /*<<< orphan*/  (* Write ) (TYPE_6__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_22__ {int /*<<< orphan*/  DigestSHA1; int /*<<< orphan*/  DigestMD5; int /*<<< orphan*/  Serial; TYPE_4__* Name; } ;
struct TYPE_21__ {void* CommonName; } ;
struct TYPE_20__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; } ;
struct TYPE_19__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_18__ {TYPE_5__* Crl; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_CRL ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  TYPE_4__ NAME ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_5__ CRL ;
typedef  TYPE_6__ CONSOLE ;
typedef  TYPE_7__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 void* CopyUniStr (int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeBuf (TYPE_7__*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcCrl (TYPE_1__*) ; 
 int /*<<< orphan*/  GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int IsEmptyStr (int /*<<< orphan*/ ) ; 
 scalar_t__ MD5_SIZE ; 
 int /*<<< orphan*/  NewXSerial (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_6__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ SHA1_SIZE ; 
 scalar_t__ ScAddCrl (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_7__* StrToBin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 void* ZeroMalloc (int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ) ; 

UINT PsCrlAdd(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_CRL t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		{"SERIAL", NULL, NULL, NULL, NULL},
		{"MD5", NULL, NULL, NULL, NULL},
		{"SHA1", NULL, NULL, NULL, NULL},
		{"CN", NULL, NULL, NULL, NULL},
		{"O", NULL, NULL, NULL, NULL},
		{"OU", NULL, NULL, NULL, NULL},
		{"C", NULL, NULL, NULL, NULL},
		{"ST", NULL, NULL, NULL, NULL},
		{"L", NULL, NULL, NULL, NULL},
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

	{
		bool param_exists = false;
		CRL *crl = ZeroMalloc(sizeof(CRL));
		NAME *n;
		n = crl->Name = ZeroMalloc(sizeof(NAME));

		if (IsEmptyStr(GetParamStr(o, "CN")) == false)
		{
			n->CommonName = CopyUniStr(GetParamUniStr(o, "CN"));
			param_exists = true;
		}

		if (IsEmptyStr(GetParamStr(o, "O")) == false)
		{
			n->CommonName = CopyUniStr(GetParamUniStr(o, "O"));
			param_exists = true;
		}

		if (IsEmptyStr(GetParamStr(o, "OU")) == false)
		{
			n->CommonName = CopyUniStr(GetParamUniStr(o, "OU"));
			param_exists = true;
		}

		if (IsEmptyStr(GetParamStr(o, "C")) == false)
		{
			n->CommonName = CopyUniStr(GetParamUniStr(o, "C"));
			param_exists = true;
		}

		if (IsEmptyStr(GetParamStr(o, "ST")) == false)
		{
			n->CommonName = CopyUniStr(GetParamUniStr(o, "ST"));
			param_exists = true;
		}

		if (IsEmptyStr(GetParamStr(o, "L")) == false)
		{
			n->CommonName = CopyUniStr(GetParamUniStr(o, "L"));
			param_exists = true;
		}

		if (IsEmptyStr(GetParamStr(o, "SERIAL")) == false)
		{
			BUF *b;

			b = StrToBin(GetParamStr(o, "SERIAL"));

			if (b != NULL && b->Size >= 1)
			{
				crl->Serial = NewXSerial(b->Buf, b->Size);
				param_exists = true;
			}

			FreeBuf(b);
		}

		if (IsEmptyStr(GetParamStr(o, "MD5")) == false)
		{
			BUF *b;

			b = StrToBin(GetParamStr(o, "MD5"));

			if (b != NULL && b->Size == MD5_SIZE)
			{
				Copy(crl->DigestMD5, b->Buf, MD5_SIZE);
				param_exists = true;
			}

			FreeBuf(b);
		}

		if (IsEmptyStr(GetParamStr(o, "SHA1")) == false)
		{
			BUF *b;

			b = StrToBin(GetParamStr(o, "SHA1"));

			if (b != NULL && b->Size == SHA1_SIZE)
			{
				Copy(crl->DigestSHA1, b->Buf, SHA1_SIZE);
				param_exists = true;
			}

			FreeBuf(b);
		}

		t.Crl = crl;

		if (param_exists == false)
		{
			FreeRpcCrl(&t);
			ret = ERR_INVALID_PARAMETER;
			CmdPrintError(c, ret);
			FreeParamValueList(o);
			return ret;
		}
	}

	// RPC call
	ret = ScAddCrl(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	FreeRpcCrl(&t);

	FreeParamValueList(o);

	return 0;
}