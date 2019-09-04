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
typedef  int /*<<< orphan*/  v2 ;
typedef  int /*<<< orphan*/  v1 ;
typedef  int /*<<< orphan*/  tmp8 ;
typedef  int /*<<< orphan*/  tmp7 ;
typedef  int /*<<< orphan*/  tmp6 ;
typedef  int /*<<< orphan*/  tmp4 ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_16__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,char*) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_14__ {scalar_t__ NumItem; TYPE_1__* Items; int /*<<< orphan*/  HubName; } ;
struct TYPE_13__ {int Protocol; int TcpStatus; int /*<<< orphan*/  SendSize; int /*<<< orphan*/  RecvSize; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  DestPort; int /*<<< orphan*/  DestHost; int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  SrcHost; int /*<<< orphan*/  Id; } ;
typedef  TYPE_1__ RPC_ENUM_NAT_ITEM ;
typedef  TYPE_2__ RPC_ENUM_NAT ;
typedef  TYPE_3__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CtFreeEx (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumNat (TYPE_2__*) ; 
 int /*<<< orphan*/  GetDateTimeStrEx64 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
#define  NAT_DNS 136 
#define  NAT_ICMP 135 
#define  NAT_TCP 134 
#define  NAT_TCP_CONNECTED 133 
#define  NAT_TCP_CONNECTING 132 
#define  NAT_TCP_ESTABLISHED 131 
#define  NAT_TCP_SEND_RESET 130 
#define  NAT_TCP_WAIT_DISCONNECT 129 
#define  NAT_UDP 128 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScEnumNAT (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrToUni (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ToStr3 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  UniToStru (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,char*) ; 

UINT PsNatTable(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ENUM_NAT t;

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
	ret = ScEnumNAT(ps->Rpc, &t);

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

		CtInsertColumn(ct, _UU("NM_NAT_ID"), false);
		CtInsertColumn(ct, _UU("NM_NAT_PROTOCOL"), false);
		CtInsertColumn(ct, _UU("NM_NAT_SRC_HOST"), false);
		CtInsertColumn(ct, _UU("NM_NAT_SRC_PORT"), false);
		CtInsertColumn(ct, _UU("NM_NAT_DST_HOST"), false);
		CtInsertColumn(ct, _UU("NM_NAT_DST_PORT"), false);
		CtInsertColumn(ct, _UU("NM_NAT_CREATED"), false);
		CtInsertColumn(ct, _UU("NM_NAT_LAST_COMM"), false);
		CtInsertColumn(ct, _UU("NM_NAT_SIZE"), false);
		CtInsertColumn(ct, _UU("NM_NAT_TCP_STATUS"), false);

		for (i = 0;i < t.NumItem;i++)
		{
			RPC_ENUM_NAT_ITEM *e = &t.Items[i];
			wchar_t tmp0[MAX_SIZE];
			wchar_t *tmp1 = L"";
			wchar_t tmp2[MAX_SIZE];
			wchar_t tmp3[MAX_SIZE];
			wchar_t tmp4[MAX_SIZE];
			wchar_t tmp5[MAX_SIZE];
			wchar_t tmp6[MAX_SIZE];
			wchar_t tmp7[MAX_SIZE];
			wchar_t tmp8[MAX_SIZE];
			wchar_t *tmp9 = L"";
			char v1[128], v2[128];

			// ID
			UniToStru(tmp0, e->Id);

			// Protocol
			switch (e->Protocol)
			{
			case NAT_TCP:
				tmp1 = _UU("NM_NAT_PROTO_TCP");
				break;
			case NAT_UDP:
				tmp1 = _UU("NM_NAT_PROTO_UDP");
				break;
			case NAT_DNS:
				tmp1 = _UU("NM_NAT_PROTO_DNS");
				break;
			case NAT_ICMP:
				tmp1 = _UU("NM_NAT_PROTO_ICMP");
				break;
			}

			// Source host
			StrToUni(tmp2, sizeof(tmp2), e->SrcHost);

			// Source port
			UniToStru(tmp3, e->SrcPort);

			// Destination host
			StrToUni(tmp4, sizeof(tmp4), e->DestHost);

			// Destination port
			UniToStru(tmp5, e->DestPort);

			// Creation date and time of the session
			GetDateTimeStrEx64(tmp6, sizeof(tmp6), SystemToLocal64(e->CreatedTime), NULL);

			// Last communication date and time
			GetDateTimeStrEx64(tmp7, sizeof(tmp7), SystemToLocal64(e->LastCommTime), NULL);

			// Communication amount
			ToStr3(v1, sizeof(v1), e->RecvSize);
			ToStr3(v2, sizeof(v2), e->SendSize);
			UniFormat(tmp8, sizeof(tmp8), L"%S / %S", v1, v2);

			// TCP state
			if (e->Protocol == NAT_TCP)
			{
				switch (e->TcpStatus)
				{
				case NAT_TCP_CONNECTING:
					tmp9 = _UU("NAT_TCP_CONNECTING");
					break;
				case NAT_TCP_SEND_RESET:
					tmp9 = _UU("NAT_TCP_SEND_RESET");
					break;
				case NAT_TCP_CONNECTED:
					tmp9 = _UU("NAT_TCP_CONNECTED");
					break;
				case NAT_TCP_ESTABLISHED:
					tmp9 = _UU("NAT_TCP_ESTABLISHED");
					break;
				case NAT_TCP_WAIT_DISCONNECT:
					tmp9 = _UU("NAT_TCP_WAIT_DISCONNECT");
					break;
				}
			}

			CtInsert(ct,
				tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9);
		}

		CtFreeEx(ct, c, true);
	}

	FreeRpcEnumNat(&t);

	FreeParamValueList(o);

	return 0;
}