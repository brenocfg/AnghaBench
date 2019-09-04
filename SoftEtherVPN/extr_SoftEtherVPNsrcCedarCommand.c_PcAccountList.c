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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  ip_str ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_8__ {scalar_t__ NumItem; TYPE_1__** Items; } ;
struct TYPE_7__ {scalar_t__ Port; int Active; scalar_t__ Connected; int /*<<< orphan*/  AccountName; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  HubName; int /*<<< orphan*/  ProxyType; int /*<<< orphan*/  ServerName; } ;
typedef  TYPE_1__ RPC_CLIENT_ENUM_ACCOUNT_ITEM ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_ACCOUNT ;
typedef  TYPE_3__ PC ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 scalar_t__ CcEnumAccount (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CiFreeClientEnumAccount (TYPE_2__*) ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFreeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProtocolName (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int StartWith (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ StrToIP6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PcAccountList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_ENUM_ACCOUNT t;

	// Get the parameter list
	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// RPC call
	Zero(&t, sizeof(t));

	ret = CcEnumAccount(pc->RemoteClient, &t);

	if (ret == ERR_NO_ERROR)
	{
		UINT i;
		CT *ct;

		// Success
		ct = CtNew();
		CtInsertColumn(ct, _UU("CM_ACCOUNT_COLUMN_1"), false);
		CtInsertColumn(ct, _UU("CM_ACCOUNT_COLUMN_2"), false);
		CtInsertColumn(ct, _UU("CM_ACCOUNT_COLUMN_3"), false);
		CtInsertColumn(ct, _UU("CM_ACCOUNT_COLUMN_3_2"), false);
		CtInsertColumn(ct, _UU("CM_ACCOUNT_COLUMN_4"), false);

		for (i = 0;i < t.NumItem;i++)
		{
			RPC_CLIENT_ENUM_ACCOUNT_ITEM *e = t.Items[i];
			wchar_t tmp[MAX_SIZE];
			wchar_t tmp2[MAX_SIZE];
			wchar_t tmp4[MAX_SIZE];
			IP ip;
			char ip_str[MAX_SIZE];

			// Special treatment for IPv6 addresses
			if (StrToIP6(&ip, e->ServerName) && StartWith(e->ServerName, "[") == false)
			{
				Format(ip_str, sizeof(ip_str),
					"[%s]", e->ServerName);
			}
			else
			{
				StrCpy(ip_str, sizeof(ip_str), e->ServerName);
			}

			if (e->Port == 0)
			{
				// Port number unknown
				UniFormat(tmp2, sizeof(tmp2), L"%S (%s)", ip_str, GetProtocolName(e->ProxyType));
			}
			else
			{
				// Port number are also shown
				UniFormat(tmp2, sizeof(tmp2), L"%S:%u (%s)", ip_str, e->Port, GetProtocolName(e->ProxyType));
			}

			// Virtual HUB name
			StrToUni(tmp4, sizeof(tmp4), e->HubName);

			// Add
			StrToUni(tmp, sizeof(tmp), e->DeviceName);

			CtInsert(ct,
				e->AccountName,
				e->Active == false ? _UU("CM_ACCOUNT_OFFLINE") :
				(e->Connected ? _UU("CM_ACCOUNT_ONLINE") : _UU("CM_ACCOUNT_CONNECTING")),
				tmp2, tmp4,
				tmp);
		}

		CtFreeEx(ct, c, true);
	}

	CiFreeClientEnumAccount(&t);

	if (ret != ERR_NO_ERROR)
	{
		// Error has occurred
		CmdPrintError(c, ret);
	}

	// Release of the parameter list
	FreeParamValueList(o);

	return ret;
}