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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp5 ;
typedef  int /*<<< orphan*/  tmp4 ;
typedef  int /*<<< orphan*/  tmp3 ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  str ;
typedef  scalar_t__ UINT ;
struct TYPE_16__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_14__ {scalar_t__ NumItem; TYPE_1__* Items; int /*<<< orphan*/  HubName; } ;
struct TYPE_13__ {char* Hostname; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  ExpireTime; int /*<<< orphan*/  LeasedTime; int /*<<< orphan*/  Id; } ;
typedef  TYPE_1__ RPC_ENUM_DHCP_ITEM ;
typedef  TYPE_2__ RPC_ENUM_DHCP ;
typedef  TYPE_3__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CtFreeEx (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumDhcp (TYPE_2__*) ; 
 int /*<<< orphan*/  GetDateTimeStrEx64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToStr32 (char*,int,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MacToStr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScEnumDHCP (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

UINT PsDhcpTable(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ENUM_DHCP t;

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
	ret = ScEnumDHCP(ps->Rpc, &t);

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

		CtInsertColumn(ct, _UU("DHCP_DHCP_ID"), false);
		CtInsertColumn(ct, _UU("DHCP_LEASED_TIME"), false);
		CtInsertColumn(ct, _UU("DHCP_EXPIRE_TIME"), false);
		CtInsertColumn(ct, _UU("DHCP_MAC_ADDRESS"), false);
		CtInsertColumn(ct, _UU("DHCP_IP_ADDRESS"), false);
		CtInsertColumn(ct, _UU("DHCP_HOSTNAME"), false);

		for (i = 0;i < t.NumItem;i++)
		{
			RPC_ENUM_DHCP_ITEM *e = &t.Items[i];
			wchar_t tmp0[MAX_SIZE];
			wchar_t tmp1[MAX_SIZE];
			wchar_t tmp2[MAX_SIZE];
			wchar_t tmp3[MAX_SIZE];
			wchar_t tmp4[MAX_SIZE];
			wchar_t tmp5[MAX_SIZE];
			char str[MAX_SIZE];

			// ID
			UniToStru(tmp0, e->Id);

			// Time
			GetDateTimeStrEx64(tmp1, sizeof(tmp1), SystemToLocal64(e->LeasedTime), NULL);
			GetDateTimeStrEx64(tmp2, sizeof(tmp2), SystemToLocal64(e->ExpireTime), NULL);

			MacToStr(str, sizeof(str), e->MacAddress);
			StrToUni(tmp3, sizeof(tmp3), str);

			IPToStr32(str, sizeof(str), e->IpAddress);
			StrToUni(tmp4, sizeof(tmp4), str);

			StrToUni(tmp5, sizeof(tmp5), e->Hostname);

			CtInsert(ct,
				tmp0, tmp1, tmp2, tmp3, tmp4, tmp5);
		}

		CtFreeEx(ct, c, true);
	}

	FreeRpcEnumDhcp(&t);

	FreeParamValueList(o);

	return 0;
}