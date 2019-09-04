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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  datetime ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_8__ {scalar_t__ NumConnection; TYPE_1__* Connections; } ;
struct TYPE_7__ {int /*<<< orphan*/  Type; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/  Port; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_ENUM_CONNECTION_ITEM ;
typedef  TYPE_2__ RPC_ENUM_CONNECTION ;
typedef  TYPE_3__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumConnection (TYPE_2__*) ; 
 int /*<<< orphan*/  GetConnectionTypeStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDateTimeStrEx64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScEnumConnection (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PsConnectionList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ENUM_CONNECTION t;
	UINT i;
	CT *ct;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScEnumConnection(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	ct = CtNew();
	CtInsertColumn(ct, _UU("SM_CONN_COLUMN_1"), false);
	CtInsertColumn(ct, _UU("SM_CONN_COLUMN_2"), false);
	CtInsertColumn(ct, _UU("SM_CONN_COLUMN_3"), false);
	CtInsertColumn(ct, _UU("SM_CONN_COLUMN_4"), false);

	for (i = 0;i < t.NumConnection;i++)
	{
		wchar_t tmp[MAX_SIZE];
		wchar_t name[MAX_SIZE];
		wchar_t datetime[MAX_SIZE];
		RPC_ENUM_CONNECTION_ITEM *e = &t.Connections[i];

		StrToUni(name, sizeof(name), e->Name);
		UniFormat(tmp, sizeof(tmp), _UU("SM_HOSTNAME_AND_PORT"), e->Hostname, e->Port);
		GetDateTimeStrEx64(datetime, sizeof(datetime), SystemToLocal64(e->ConnectedTime), NULL);

		CtInsert(ct, name, tmp, datetime,
			GetConnectionTypeStr(e->Type));
	}

	CtFree(ct, c);

	FreeRpcEnumConnection(&t);

	FreeParamValueList(o);

	return 0;
}