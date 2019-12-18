#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  vv ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  str ;
typedef  int UINT64 ;
typedef  char* UINT ;
struct TYPE_7__ {int UnicastCount; int UnicastBytes; int BroadcastCount; int BroadcastBytes; } ;
struct TYPE_6__ {int UnicastCount; int UnicastBytes; int BroadcastCount; int BroadcastBytes; } ;
struct TYPE_8__ {TYPE_2__ Recv; TYPE_1__ Send; } ;
struct TYPE_9__ {char* AccountName; int Connected; int SessionStatus; char* ServerName; char* ServerPort; char* ServerProductName; int ServerProductVer; char* ServerProductBuild; scalar_t__ StartTime; scalar_t__ FirstConnectionEstablisiedTime; scalar_t__ CurrentConnectionEstablishTime; char* NumConnectionsEstablished; char* NumTcpConnections; char* NumTcpConnectionsUpload; char* NumTcpConnectionsDownload; char* MaxTcpConnections; int UseEncrypt; char* CipherName; int TotalRecvSize; int TotalSendSize; char* UnderlayProtocol; char* SessionName; char* ConnectionName; TYPE_3__ Traffic; scalar_t__ IsMonitorMode; scalar_t__ IsBridgeMode; int /*<<< orphan*/  SessionKey; scalar_t__ IsUsingUdpAcceleration; scalar_t__ IsUdpAccelerationEnabled; scalar_t__ TotalSendSizeReal; scalar_t__ TotalRecvSizeReal; scalar_t__ UseCompress; scalar_t__ HalfConnection; scalar_t__ QoS; int /*<<< orphan*/  VLanId; } ;
typedef  TYPE_4__ RPC_CLIENT_GET_CONNECTION_STATUS ;
typedef  int /*<<< orphan*/  CT ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ ,int) ; 
#define  CLIENT_STATUS_AUTH 133 
#define  CLIENT_STATUS_CONNECTING 132 
#define  CLIENT_STATUS_ESTABLISHED 131 
#define  CLIENT_STATUS_IDLE 130 
#define  CLIENT_STATUS_NEGOTIATION 129 
#define  CLIENT_STATUS_RETRY 128 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  GetDateTimeStrEx64 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IsEmptyStr (char*) ; 
 char* MAKESURE (char*,int /*<<< orphan*/ ,int) ; 
 int MAX_SIZE ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  StrToUni (char*,int,char*) ; 
 int /*<<< orphan*/  SystemToLocal64 (scalar_t__) ; 
 int /*<<< orphan*/  ToStr3 (char*,int,int) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,...) ; 
 scalar_t__ UniStrCmpi (char*,char*) ; 
 int /*<<< orphan*/  UniStrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UniToStru (char*,int /*<<< orphan*/ ) ; 
 char* _UU (char*) ; 

void CmdPrintStatusToListViewEx(CT *ct, RPC_CLIENT_GET_CONNECTION_STATUS *s, bool server_mode)
{
	wchar_t tmp[MAX_SIZE];
	char str[MAX_SIZE];
	char vv[128];
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	if (server_mode == false)
	{
		CtInsert(ct, _UU("CM_ST_ACCOUNT_NAME"), s->AccountName);

		if (s->Connected == false)
		{
			wchar_t *st = _UU("CM_ST_CONNECTED_FALSE");
			switch (s->SessionStatus)
			{
			case CLIENT_STATUS_CONNECTING:
				st = _UU("CM_ST_CONNECTING");
				break;
			case CLIENT_STATUS_NEGOTIATION:
				st = _UU("CM_ST_NEGOTIATION");
				break;
			case CLIENT_STATUS_AUTH:
				st = _UU("CM_ST_AUTH");
				break;
			case CLIENT_STATUS_ESTABLISHED:
				st = _UU("CM_ST_ESTABLISHED");
				break;
			case CLIENT_STATUS_RETRY:
				st = _UU("CM_ST_RETRY");
				break;
			case CLIENT_STATUS_IDLE:
				st = _UU("CM_ST_IDLE");
				break;
			}
			CtInsert(ct, _UU("CM_ST_CONNECTED"), st);
		}
		else
		{
			CtInsert(ct, _UU("CM_ST_CONNECTED"), _UU("CM_ST_CONNECTED_TRUE"));
		}
	}

	if (s->Connected)
	{
		if (s->VLanId == 0)
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("CM_ST_NO_VLAN"));
		}
		else
		{
			UniToStru(tmp, s->VLanId);
		}

		CtInsert(ct, _UU("CM_ST_VLAN_ID"), tmp);

		if (server_mode == false)
		{
			StrToUni(tmp, sizeof(tmp), s->ServerName);
			CtInsert(ct, _UU("CM_ST_SERVER_NAME"), tmp);

			UniFormat(tmp, sizeof(tmp), _UU("CM_ST_PORT_TCP"), s->ServerPort);
			CtInsert(ct, _UU("CM_ST_SERVER_PORT"), tmp);
		}

		StrToUni(tmp, sizeof(tmp), s->ServerProductName);
		CtInsert(ct, _UU("CM_ST_SERVER_P_NAME"), tmp);

		UniFormat(tmp, sizeof(tmp), L"%u.%02u", s->ServerProductVer / 100, s->ServerProductVer % 100);
		CtInsert(ct, _UU("CM_ST_SERVER_P_VER"), tmp);
		UniFormat(tmp, sizeof(tmp), L"Build %u", s->ServerProductBuild);
		CtInsert(ct, _UU("CM_ST_SERVER_P_BUILD"), tmp);
	}

	GetDateTimeStrEx64(tmp, sizeof(tmp), SystemToLocal64(s->StartTime), NULL);
	CtInsert(ct, _UU("CM_ST_START_TIME"), tmp);
	/* !!! Do not correct the spelling to keep the backward protocol compatibility !!!  */
	GetDateTimeStrEx64(tmp, sizeof(tmp), SystemToLocal64(s->FirstConnectionEstablisiedTime), NULL);
	/* !!! Do not correct the spelling to keep the backward protocol compatibility !!!  */
	CtInsert(ct, _UU("CM_ST_FIRST_ESTAB_TIME"), s->FirstConnectionEstablisiedTime == 0 ? _UU("CM_ST_NONE") : tmp);

	if (s->Connected)
	{
		GetDateTimeStrEx64(tmp, sizeof(tmp), SystemToLocal64(s->CurrentConnectionEstablishTime), NULL);
		CtInsert(ct, _UU("CM_ST_CURR_ESTAB_TIME"), tmp);
	}

	if (server_mode == false)
	{
		UniFormat(tmp, sizeof(tmp), _UU("CM_ST_NUM_STR"), s->NumConnectionsEstablished);
		CtInsert(ct, _UU("CM_ST_NUM_ESTABLISHED"), tmp);
	}

	if (s->Connected)
	{
		CtInsert(ct, _UU("CM_ST_HALF_CONNECTION"), s->HalfConnection ? _UU("CM_ST_HALF_TRUE") : _UU("CM_ST_HALF_FALSE"));

		CtInsert(ct, _UU("CM_ST_QOS"), s->QoS ? _UU("CM_ST_QOS_TRUE") : _UU("CM_ST_QOS_FALSE"));

		UniFormat(tmp, sizeof(tmp), L"%u", s->NumTcpConnections);
		CtInsert(ct, _UU("CM_ST_NUM_TCP"), tmp);

		if (s->HalfConnection)
		{
			UniFormat(tmp, sizeof(tmp), L"%u", s->NumTcpConnectionsUpload);
			CtInsert(ct, _UU("CM_ST_NUM_TCP_UPLOAD"), tmp);
			UniFormat(tmp, sizeof(tmp), L"%u", s->NumTcpConnectionsDownload);
			CtInsert(ct, _UU("CM_ST_NUM_TCP_DOWNLOAD"), tmp);
		}

		UniFormat(tmp, sizeof(tmp), L"%u", s->MaxTcpConnections);
		CtInsert(ct, _UU("CM_ST_MAX_TCP"), tmp);

		if (s->UseEncrypt == false)
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("CM_ST_USE_ENCRYPT_FALSE"));
		}
		else
		{
			if (StrLen(s->CipherName) != 0)
			{
				UniFormat(tmp, sizeof(tmp), _UU("CM_ST_USE_ENCRYPT_TRUE"), s->CipherName);
			}
			else
			{
				UniFormat(tmp, sizeof(tmp), _UU("CM_ST_USE_ENCRYPT_TRUE2"));
			}
		}
		CtInsert(ct, _UU("CM_ST_USE_ENCRYPT"), tmp);

		if (s->UseCompress)
		{
			UINT percent = 0;
			if ((s->TotalRecvSize + s->TotalSendSize) > 0)
			{
				percent = (UINT)((UINT64)100 - (UINT64)(s->TotalRecvSizeReal + s->TotalSendSizeReal) * (UINT64)100 /
					(s->TotalRecvSize + s->TotalSendSize));
				percent = MAKESURE(percent, 0, 100);
			}

			UniFormat(tmp, sizeof(tmp), _UU("CM_ST_COMPRESS_TRUE"), percent);
		}
		else
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("CM_ST_COMPRESS_FALSE"));
		}
		CtInsert(ct, _UU("CM_ST_USE_COMPRESS"), tmp);

		if (IsEmptyStr(s->UnderlayProtocol) == false)
		{
			StrToUni(tmp, sizeof(tmp), s->UnderlayProtocol);
			CtInsert(ct, _UU("CM_ST_UNDERLAY_PROTOCOL"), tmp);
		}

		CtInsert(ct, _UU("CM_ST_UDP_ACCEL_ENABLED"), (s->IsUdpAccelerationEnabled ? _UU("CM_ST_YES") : _UU("CM_ST_NO")));
		CtInsert(ct, _UU("CM_ST_UDP_ACCEL_USING"), (s->IsUsingUdpAcceleration ? _UU("CM_ST_YES") : _UU("CM_ST_NO")));

		StrToUni(tmp, sizeof(tmp), s->SessionName);
		CtInsert(ct, _UU("CM_ST_SESSION_NAME"), tmp);

		StrToUni(tmp, sizeof(tmp), s->ConnectionName);
		if (UniStrCmpi(tmp, L"INITING") != 0)
		{
			CtInsert(ct, _UU("CM_ST_CONNECTION_NAME"), tmp);
		}

		BinToStr(str, sizeof(str), s->SessionKey, sizeof(s->SessionKey));
		StrToUni(tmp, sizeof(tmp), str);
		CtInsert(ct, _UU("CM_ST_SESSION_KEY"), tmp);

		CtInsert(ct, _UU("CM_ST_BRIDGE_MODE"), s->IsBridgeMode ? _UU("CM_ST_YES") : _UU("CM_ST_NO"));

		CtInsert(ct, _UU("CM_ST_MONITOR_MODE"), s->IsMonitorMode ? _UU("CM_ST_YES") : _UU("CM_ST_NO"));

		ToStr3(vv, sizeof(vv), s->TotalSendSize);
		UniFormat(tmp, sizeof(tmp), _UU("CM_ST_SIZE_BYTE_STR"), vv);
		CtInsert(ct, _UU("CM_ST_SEND_SIZE"), tmp);

		ToStr3(vv, sizeof(vv), s->TotalRecvSize);
		UniFormat(tmp, sizeof(tmp), _UU("CM_ST_SIZE_BYTE_STR"), vv);
		CtInsert(ct, _UU("CM_ST_RECV_SIZE"), tmp);

		ToStr3(vv, sizeof(vv), s->Traffic.Send.UnicastCount);
		UniFormat(tmp, sizeof(tmp), _UU("CM_ST_NUM_PACKET_STR"), vv);
		CtInsert(ct, _UU("CM_ST_SEND_UCAST_NUM"), tmp);

		ToStr3(vv, sizeof(vv), s->Traffic.Send.UnicastBytes);
		UniFormat(tmp, sizeof(tmp), _UU("CM_ST_SIZE_BYTE_STR"), vv);
		CtInsert(ct, _UU("CM_ST_SEND_UCAST_SIZE"), tmp);

		ToStr3(vv, sizeof(vv), s->Traffic.Send.BroadcastCount);
		UniFormat(tmp, sizeof(tmp), _UU("CM_ST_NUM_PACKET_STR"), vv);
		CtInsert(ct, _UU("CM_ST_SEND_BCAST_NUM"), tmp);

		ToStr3(vv, sizeof(vv), s->Traffic.Send.BroadcastBytes);
		UniFormat(tmp, sizeof(tmp), _UU("CM_ST_SIZE_BYTE_STR"), vv);
		CtInsert(ct, _UU("CM_ST_SEND_BCAST_SIZE"), tmp);

		ToStr3(vv, sizeof(vv), s->Traffic.Recv.UnicastCount);
		UniFormat(tmp, sizeof(tmp), _UU("CM_ST_NUM_PACKET_STR"), vv);
		CtInsert(ct, _UU("CM_ST_RECV_UCAST_NUM"), tmp);

		ToStr3(vv, sizeof(vv), s->Traffic.Recv.UnicastBytes);
		UniFormat(tmp, sizeof(tmp), _UU("CM_ST_SIZE_BYTE_STR"), vv);
		CtInsert(ct, _UU("CM_ST_RECV_UCAST_SIZE"), tmp);

		ToStr3(vv, sizeof(vv), s->Traffic.Recv.BroadcastCount);
		UniFormat(tmp, sizeof(tmp), _UU("CM_ST_NUM_PACKET_STR"), vv);
		CtInsert(ct, _UU("CM_ST_RECV_BCAST_NUM"), tmp);

		ToStr3(vv, sizeof(vv), s->Traffic.Recv.BroadcastBytes);
		UniFormat(tmp, sizeof(tmp), _UU("CM_ST_SIZE_BYTE_STR"), vv);
		CtInsert(ct, _UU("CM_ST_RECV_BCAST_SIZE"), tmp);
	}
}