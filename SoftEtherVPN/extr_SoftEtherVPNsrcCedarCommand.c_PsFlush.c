#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  sizestr ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_13__ {int /*<<< orphan*/  (* Write ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_11__ {scalar_t__ IntValue; } ;
typedef  TYPE_1__ RPC_TEST ;
typedef  TYPE_2__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_3__*,scalar_t__) ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_3__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScFlush (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ToStr3 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ *) ; 

UINT PsFlush(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	if (true)
	{
		RPC_TEST t;
		UINT ret;
		wchar_t tmp[MAX_SIZE];
		char sizestr[MAX_SIZE];

		c->Write(c, _UU("CMD_Flush_Msg1"));

		Zero(&t, sizeof(t));

		ret = ScFlush(ps->Rpc, &t);

		if (ret != ERR_NO_ERROR)
		{
			// An error has occured
			CmdPrintError(c, ret);
			FreeParamValueList(o);
			return ret;
		}

		ToStr3(sizestr, sizeof(sizestr), (UINT64)t.IntValue);
		UniFormat(tmp, sizeof(tmp), _UU("CMD_Flush_Msg2"), sizestr);
		c->Write(c, tmp);
	}

	FreeParamValueList(o);

	return 0;
}