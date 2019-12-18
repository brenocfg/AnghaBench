#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp8 ;
typedef  int /*<<< orphan*/  tmp7 ;
typedef  int /*<<< orphan*/  tmp6 ;
typedef  int /*<<< orphan*/  tmp5 ;
typedef  int /*<<< orphan*/  tmp4 ;
typedef  int /*<<< orphan*/  tmp3 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_19__ {int /*<<< orphan*/  (* Write ) (TYPE_5__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_17__ {scalar_t__ VLanId; int /*<<< orphan*/  PacketNum; int /*<<< orphan*/  PacketSize; scalar_t__ BridgeMode; scalar_t__ SecureNATMode; scalar_t__ LinkMode; int /*<<< orphan*/  MaxNumTcp; int /*<<< orphan*/  CurrentNumTcp; int /*<<< orphan*/  Username; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  RemoteHostname; scalar_t__ RemoteSession; int /*<<< orphan*/  Name; } ;
struct TYPE_16__ {scalar_t__ ServerType; scalar_t__ NumSession; TYPE_2__* Sessions; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_SERVER_INFO ;
typedef  TYPE_2__ RPC_ENUM_SESSION_ITEM ;
typedef  TYPE_1__ RPC_ENUM_SESSION ;
typedef  TYPE_4__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_5__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  CtFreeEx (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumSession (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeRpcServerInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  L3_USERNAME ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_5__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 scalar_t__ ScEnumSession (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ScGetServerInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ StartWith (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ StrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToStr3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ *) ; 

UINT PsSessionList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ENUM_SESSION t;
	UINT server_type = 0;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// If virtual HUB is not selected, it's an error
	if (ps->HubName == NULL)
	{
		c->Write(c, _UU("CMD_Hub_Not_Selected"));
		return ERR_INVALID_PARAMETER;
	}

	{
		// Get the server type
		RPC_SERVER_INFO t;

		Zero(&t, sizeof(t));

		if (ScGetServerInfo(ps->Rpc, &t) == ERR_NO_ERROR)
		{
			server_type = t.ServerType;

			FreeRpcServerInfo(&t);
		}
	}

	Zero(&t, sizeof(t));
	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);

	// RPC call
	ret = ScEnumSession(ps->Rpc, &t);

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

		CtInsertColumn(ct, _UU("SM_SESS_COLUMN_1"), false);
		CtInsertColumn(ct, _UU("SM_SESS_COLUMN_8"), false);
		CtInsertColumn(ct, _UU("SM_SESS_COLUMN_2"), false);
		CtInsertColumn(ct, _UU("SM_SESS_COLUMN_3"), false);
		CtInsertColumn(ct, _UU("SM_SESS_COLUMN_4"), false);
		CtInsertColumn(ct, _UU("SM_SESS_COLUMN_5"), true);
		CtInsertColumn(ct, _UU("SM_SESS_COLUMN_6"), true);
		CtInsertColumn(ct, _UU("SM_SESS_COLUMN_7"), true);

		for (i = 0;i < t.NumSession;i++)
		{
			RPC_ENUM_SESSION_ITEM *e = &t.Sessions[i];
			wchar_t tmp1[MAX_SIZE];
			wchar_t *tmp2;
			wchar_t tmp3[MAX_SIZE];
			wchar_t tmp4[MAX_SIZE];
			wchar_t tmp5[MAX_SIZE];
			wchar_t tmp6[MAX_SIZE];
			wchar_t tmp7[MAX_SIZE];
			wchar_t tmp8[MAX_SIZE];
			bool free_tmp2 = false;

			StrToUni(tmp1, sizeof(tmp1), e->Name);

			tmp2 = _UU("SM_SESS_NORMAL");
			if (server_type != SERVER_TYPE_STANDALONE)
			{
				if (e->RemoteSession)
				{
					tmp2 = ZeroMalloc(MAX_SIZE);
					UniFormat(tmp2, MAX_SIZE, _UU("SM_SESS_REMOTE"), e->RemoteHostname);
					free_tmp2 = true;
				}
				else
				{
					if (StrLen(e->RemoteHostname) == 0)
					{
						tmp2 = _UU("SM_SESS_LOCAL");
					}
					else
					{
						tmp2 = ZeroMalloc(MAX_SIZE);
						UniFormat(tmp2, MAX_SIZE, _UU("SM_SESS_LOCAL_2"), e->RemoteHostname);
						free_tmp2 = true;
					}
				}
			}
			if (e->LinkMode)
			{
				if (free_tmp2)
				{
					Free(tmp2);
					free_tmp2 = false;
				}
				tmp2 = _UU("SM_SESS_LINK");
			}
			else if (e->SecureNATMode)
			{
				/*if (free_tmp2)
				{
					Free(tmp2);
					free_tmp2 = false;
				}*/
				tmp2 = _UU("SM_SESS_SNAT");
			}

			StrToUni(tmp3, sizeof(tmp3), e->Username);

			StrToUni(tmp4, sizeof(tmp4), e->Hostname);
			if (e->LinkMode)
			{
				UniStrCpy(tmp4, sizeof(tmp4), _UU("SM_SESS_LINK_HOSTNAME"));
			}
			else if (e->SecureNATMode)
			{
				UniStrCpy(tmp4, sizeof(tmp4), _UU("SM_SESS_SNAT_HOSTNAME"));
			}
			else if (e->BridgeMode)
			{
				UniStrCpy(tmp4, sizeof(tmp4), _UU("SM_SESS_BRIDGE_HOSTNAME"));
			}
			else if (StartWith(e->Username, L3_USERNAME))
			{
				UniStrCpy(tmp4, sizeof(tmp4), _UU("SM_SESS_LAYER3_HOSTNAME"));
			}

			UniFormat(tmp5, sizeof(tmp5), L"%u / %u", e->CurrentNumTcp, e->MaxNumTcp);
			if (e->LinkMode)
			{
				UniStrCpy(tmp5, sizeof(tmp5), _UU("SM_SESS_LINK_TCP"));
			}
			else if (e->SecureNATMode)
			{
				UniStrCpy(tmp5, sizeof(tmp5), _UU("SM_SESS_SNAT_TCP"));
			}
			else if (e->BridgeMode)
			{
				UniStrCpy(tmp5, sizeof(tmp5), _UU("SM_SESS_BRIDGE_TCP"));
			}

			UniToStr3(tmp6, sizeof(tmp6), e->PacketSize);
			UniToStr3(tmp7, sizeof(tmp7), e->PacketNum);

			if (e->VLanId == 0)
			{
				UniStrCpy(tmp8, sizeof(tmp8), _UU("CM_ST_NO_VLAN"));
			}
			else
			{
				UniToStru(tmp8, e->VLanId);
			}

			CtInsert(ct, tmp1, tmp8, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7);

			if (free_tmp2)
			{
				Free(tmp2);
			}
		}


		CtFreeEx(ct, c, true);
	}

	FreeRpcEnumSession(&t);

	FreeParamValueList(o);

	return 0;
}