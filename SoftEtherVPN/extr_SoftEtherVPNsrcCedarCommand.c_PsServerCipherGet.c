#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_22__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,char*) ;} ;
struct TYPE_21__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_20__ {int /*<<< orphan*/  String; } ;
struct TYPE_19__ {scalar_t__ NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ RPC_STR ;
typedef  TYPE_3__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcStr (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ParseToken (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ScGetServerCipher (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ScGetServerCipherList (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_4__*,char*) ; 

UINT PsServerCipherGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_STR t;
	TOKEN_LIST *ciphers;
	UINT i;
	wchar_t tmp[4096];

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScGetServerCipher(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	UniFormat(tmp, sizeof(tmp), L" %S", t.String);
	FreeRpcStr(&t);
	Zero(&t, sizeof(RPC_STR));

	c->Write(c, _UU("CMD_ServerCipherGet_SERVER"));
	c->Write(c, tmp);

	ret = ScGetServerCipherList(ps->Rpc, &t);

	if (ret == ERR_NO_ERROR)
	{
		ciphers = ParseToken(t.String, ";");

		FreeRpcStr(&t);

		c->Write(c, L"");
		c->Write(c, _UU("CMD_ServerCipherGet_CIPHERS"));

		for (i = 0; i < ciphers->NumTokens; i++)
		{
			UniFormat(tmp, sizeof(tmp), L" %S", ciphers->Token[i]);
			c->Write(c, tmp);
		}

		FreeToken(ciphers);
	}

	FreeParamValueList(o);

	return 0;
}