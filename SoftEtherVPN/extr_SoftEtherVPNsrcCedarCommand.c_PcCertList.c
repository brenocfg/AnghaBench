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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_8__ {scalar_t__ NumItem; TYPE_1__** Items; } ;
struct TYPE_7__ {char* SubjectName; char* IssuerName; int /*<<< orphan*/  Key; int /*<<< orphan*/  Expires; } ;
typedef  TYPE_1__ RPC_CLIENT_ENUM_CA_ITEM ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_CA ;
typedef  TYPE_3__ PC ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 scalar_t__ CcEnumCa (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CiFreeClientEnumCa (TYPE_2__*) ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDateStrEx64 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 char* _UU (char*) ; 

UINT PcCertList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_ENUM_CA t;

	// Get the parameter list
	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// RPC call
	Zero(&t, sizeof(t));

	ret = CcEnumCa(pc->RemoteClient, &t);

	if (ret == ERR_NO_ERROR)
	{
		// Success
		UINT i;
		CT *ct = CtNewStandard();

		for (i = 0;i < t.NumItem;i++)
		{
			wchar_t tmp[MAX_SIZE];
			wchar_t tmp2[64];
			RPC_CLIENT_ENUM_CA_ITEM *e = t.Items[i];

			GetDateStrEx64(tmp, sizeof(tmp), SystemToLocal64(e->Expires), NULL);

			UniToStru(tmp2, e->Key);

			CtInsert(ct, _UU("CMD_CAList_COLUMN_ID"), tmp2);
			CtInsert(ct, _UU("CM_CERT_COLUMN_1"), e->SubjectName);
			CtInsert(ct, _UU("CM_CERT_COLUMN_2"), e->IssuerName);
			CtInsert(ct, _UU("CM_CERT_COLUMN_3"), tmp);

			if (i != (t.NumItem - 1))
			{
				CtInsert(ct, L"---", L"---");
			}
		}

		CtFree(ct, c);

		CiFreeClientEnumCa(&t);
	}

	if (ret != ERR_NO_ERROR)
	{
		// Error has occurred
		CmdPrintError(c, ret);
	}


	// Release of the parameter list
	FreeParamValueList(o);

	return ret;
}