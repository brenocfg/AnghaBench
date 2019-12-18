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
typedef  int /*<<< orphan*/  ver ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  mac ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_8__ {scalar_t__ NumItem; TYPE_1__** Items; } ;
struct TYPE_7__ {int /*<<< orphan*/  Version; int /*<<< orphan*/  MacAddress; scalar_t__ Enabled; int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_1__ RPC_CLIENT_ENUM_VLAN_ITEM ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_VLAN ;
typedef  TYPE_3__ PC ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 scalar_t__ CcEnumVLan (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CiFreeClientEnumVLan (TYPE_2__*) ; 
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
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PcNicList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_ENUM_VLAN t;

	// Get the parameter list
	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// RPC call
	Zero(&t, sizeof(t));

	ret = CcEnumVLan(pc->RemoteClient, &t);

	if (ret == ERR_NO_ERROR)
	{
		CT *ct;
		UINT i;

		// Success
		ct = CtNew();
		CtInsertColumn(ct, _UU("CM_VLAN_COLUMN_1"), false);
		CtInsertColumn(ct, _UU("CM_VLAN_COLUMN_2"), false);
		CtInsertColumn(ct, _UU("CM_VLAN_COLUMN_3"), false);
		CtInsertColumn(ct, _UU("CM_VLAN_COLUMN_4"), false);

		for (i = 0;i < t.NumItem;i++)
		{
			wchar_t name[MAX_SIZE];
			wchar_t mac[MAX_SIZE];
			wchar_t ver[MAX_SIZE];
			wchar_t *status;
			RPC_CLIENT_ENUM_VLAN_ITEM *v = t.Items[i];

			// Device name
			StrToUni(name, sizeof(name), v->DeviceName);

			// State
			status = v->Enabled ? _UU("CM_VLAN_ENABLED") : _UU("CM_VLAN_DISABLED");

			// MAC address
			StrToUni(mac, sizeof(mac), v->MacAddress);

			// Version
			StrToUni(ver, sizeof(ver), v->Version);

			CtInsert(ct,
				name, status, mac, ver);
		}

		CtFreeEx(ct, c, true);
	}

	if (ret != ERR_NO_ERROR)
	{
		// Error has occurred
		CmdPrintError(c, ret);
	}

	CiFreeClientEnumVLan(&t);

	// Release of the parameter list
	FreeParamValueList(o);

	return ret;
}