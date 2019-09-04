#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_8__ {scalar_t__ NumItem; TYPE_1__* Items; } ;
struct TYPE_7__ {int Active; int Online; int /*<<< orphan*/  NumTables; int /*<<< orphan*/  NumInterfaces; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_ENUM_L3SW_ITEM ;
typedef  TYPE_2__ RPC_ENUM_L3SW ;
typedef  TYPE_3__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumL3Sw (TYPE_2__*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScEnumL3Switch (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PsRouterList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ENUM_L3SW t;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScEnumL3Switch(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		CT *ct = CtNew();
		UINT i;

		CtInsertColumn(ct, _UU("SM_L3_SW_COLUMN1"), false);
		CtInsertColumn(ct, _UU("SM_L3_SW_COLUMN2"), false);
		CtInsertColumn(ct, _UU("SM_L3_SW_COLUMN3"), true);
		CtInsertColumn(ct, _UU("SM_L3_SW_COLUMN4"), true);

		for (i = 0;i < t.NumItem;i++)
		{
			RPC_ENUM_L3SW_ITEM *e = &t.Items[i];
			wchar_t tmp1[MAX_SIZE], *tmp2, tmp3[64], tmp4[64];

			StrToUni(tmp1, sizeof(tmp1), e->Name);
			if (e->Active == false)
			{
				tmp2 = _UU("SM_L3_SW_ST_F_F");
			}
			else if (e->Online == false)
			{
				tmp2 = _UU("SM_L3_SW_ST_T_F");
			}
			else
			{
				tmp2 = _UU("SM_L3_SW_ST_T_T");
			}
			UniToStru(tmp3, e->NumInterfaces);
			UniToStru(tmp4, e->NumTables);

			CtInsert(ct,
				tmp1, tmp2, tmp3, tmp4);
		}

		CtFree(ct, c);
	}

	FreeRpcEnumL3Sw(&t);

	FreeParamValueList(o);

	return 0;
}