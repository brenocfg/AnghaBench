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
typedef  int /*<<< orphan*/  tmp4 ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_8__ {scalar_t__ NumItem; TYPE_1__** Items; } ;
struct TYPE_7__ {scalar_t__ Type; int /*<<< orphan*/  Manufacturer; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  DeviceId; } ;
typedef  TYPE_1__ RPC_CLIENT_ENUM_SECURE_ITEM ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_SECURE ;
typedef  TYPE_3__ PC ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 scalar_t__ CcEnumSecure (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CiFreeClientEnumSecure (TYPE_2__*) ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFreeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SECURE_IC_CARD ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PcSecureList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_ENUM_SECURE t;

	// Get the parameter list
	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// RPC call
	Zero(&t, sizeof(t));

	ret = CcEnumSecure(pc->RemoteClient, &t);

	if (ret == ERR_NO_ERROR)
	{
		CT *ct;
		UINT i;
		wchar_t tmp1[MAX_SIZE];
		wchar_t tmp2[MAX_SIZE];
		wchar_t tmp4[MAX_SIZE];
		wchar_t *tmp3;

		// Success
		ct = CtNew();
		CtInsertColumn(ct, _UU("SEC_COLUMN1"), false);
		CtInsertColumn(ct, _UU("SEC_COLUMN2"), false);
		CtInsertColumn(ct, _UU("SEC_COLUMN3"), false);
		CtInsertColumn(ct, _UU("SEC_COLUMN4"), false);

		for (i = 0;i < t.NumItem;i++)
		{
			RPC_CLIENT_ENUM_SECURE_ITEM *e = t.Items[i];

			// ID
			UniToStru(tmp1, e->DeviceId);

			// Device name
			StrToUni(tmp2, sizeof(tmp2), e->DeviceName);

			// Type
			tmp3 = (e->Type == SECURE_IC_CARD) ? _UU("SEC_SMART_CARD") : _UU("SEC_USB_TOKEN");

			// Manufacturer
			StrToUni(tmp4, sizeof(tmp4), e->Manufacturer);

			CtInsert(ct, tmp1, tmp2, tmp3, tmp4);
		}

		CtFreeEx(ct, c, true);

		CiFreeClientEnumSecure(&t);
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