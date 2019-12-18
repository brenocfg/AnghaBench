#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_16__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,char*) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_14__ {scalar_t__ NumCa; TYPE_1__* Ca; int /*<<< orphan*/  HubName; } ;
struct TYPE_13__ {char* SubjectName; char* IssuerName; int /*<<< orphan*/  Key; int /*<<< orphan*/  Expires; } ;
typedef  TYPE_1__ RPC_HUB_ENUM_CA_ITEM ;
typedef  TYPE_2__ RPC_HUB_ENUM_CA ;
typedef  TYPE_3__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcHubEnumCa (TYPE_2__*) ; 
 int /*<<< orphan*/  GetDateStrEx64 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScEnumCa (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,char*) ; 

UINT PsCAList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_HUB_ENUM_CA t;
	
	// If virtual HUB is not selected, it's an error
	if (ps->HubName == NULL)
	{
		c->Write(c, _UU("CMD_Hub_Not_Selected"));
		return ERR_INVALID_PARAMETER;
	}

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);

	// RPC call
	ret = ScEnumCa(ps->Rpc, &t);

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
		CT *ct = CtNewStandard();

		for (i = 0;i < t.NumCa;i++)
		{
			wchar_t tmp[MAX_SIZE];
			wchar_t tmp2[64];
			RPC_HUB_ENUM_CA_ITEM *e = &t.Ca[i];

			GetDateStrEx64(tmp, sizeof(tmp), SystemToLocal64(e->Expires), NULL);

			UniToStru(tmp2, e->Key);

			CtInsert(ct, _UU("CMD_CAList_COLUMN_ID"), tmp2);
			CtInsert(ct, _UU("CM_CERT_COLUMN_1"), e->SubjectName);
			CtInsert(ct, _UU("CM_CERT_COLUMN_2"), e->IssuerName);
			CtInsert(ct, _UU("CM_CERT_COLUMN_3"), tmp);

			if (i != (t.NumCa - 1))
			{
				CtInsert(ct, L"---", L"---");
			}
		}

		CtFree(ct, c);
	}

	FreeRpcHubEnumCa(&t);

	FreeParamValueList(o);

	return 0;
}