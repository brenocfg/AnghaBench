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
typedef  int /*<<< orphan*/  username ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  hubname ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  UserName; int /*<<< orphan*/  HubName; int /*<<< orphan*/  Id; } ;
struct TYPE_8__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_7__ {scalar_t__ NumItem; TYPE_3__* IdList; } ;
typedef  TYPE_1__ RPC_ENUM_ETHERIP_ID ;
typedef  TYPE_2__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ ETHERIP_ID ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumEtherIpId (TYPE_1__*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScEnumEtherIpId (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PsEtherIpClientList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ENUM_ETHERIP_ID t;
	UINT i;
	CT *b;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScEnumEtherIpId(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		b = CtNew();

		CtInsertColumn(b, _UU("SM_ETHERIP_COLUMN_0"), false);
		CtInsertColumn(b, _UU("SM_ETHERIP_COLUMN_1"), false);
		CtInsertColumn(b, _UU("SM_ETHERIP_COLUMN_2"), false);

		for (i = 0;i < t.NumItem;i++)
		{
			ETHERIP_ID *d = &t.IdList[i];
			wchar_t id[MAX_SIZE], hubname[MAX_SIZE], username[MAX_SIZE];

			StrToUni(id, sizeof(id), d->Id);
			StrToUni(hubname, sizeof(hubname), d->HubName);
			StrToUni(username, sizeof(username), d->UserName);

			CtInsert(b, id, hubname, username);
		}

		CtFree(b, c);

		FreeRpcEnumEtherIpId(&t);
	}

	FreeParamValueList(o);

	return 0;
}