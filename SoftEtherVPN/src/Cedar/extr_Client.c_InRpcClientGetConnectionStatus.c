#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Active; int Connected; int HalfConnection; int QoS; int UseEncrypt; int UseCompress; int IsRUDPSession; int IsUdpAccelerationEnabled; int IsUsingUdpAcceleration; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  Policy; void* ClientX; void* ServerX; void* VLanId; void* IsMonitorMode; void* IsBridgeMode; int /*<<< orphan*/  UnderlayProtocol; void* TotalRecvSizeReal; void* TotalSendSizeReal; void* TotalRecvSize; void* TotalSendSize; void* CurrentConnectionEstablishTime; void* FirstConnectionEstablisiedTime; void* StartTime; void* NumTcpConnectionsDownload; void* NumTcpConnectionsUpload; void* NumTcpConnections; void* MaxTcpConnections; void* NumConnectionsEstablished; void* ServerProductBuild; void* ServerProductVer; void* ServerPort; void* SessionStatus; int /*<<< orphan*/  SessionKey; int /*<<< orphan*/  ConnectionName; int /*<<< orphan*/  SessionName; int /*<<< orphan*/  CipherName; int /*<<< orphan*/  ServerProductName; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ RPC_CLIENT_GET_CONNECTION_STATUS ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 void* BufToX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcTraffic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PackGetBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ PackGetDataSize (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SHA1_SIZE ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcClientGetConnectionStatus(RPC_CLIENT_GET_CONNECTION_STATUS *s, PACK *p)
{
	BUF *b;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return;
	}

	Zero(s, sizeof(RPC_CLIENT_GET_CONNECTION_STATUS));

	PackGetUniStr(p, "AccountName", s->AccountName, sizeof(s->AccountName));

	PackGetStr(p, "ServerName", s->ServerName, sizeof(s->ServerName));
	PackGetStr(p, "ServerProductName", s->ServerProductName, sizeof(s->ServerProductName));
	PackGetStr(p, "CipherName", s->CipherName, sizeof(s->CipherName));
	PackGetStr(p, "SessionName", s->SessionName, sizeof(s->SessionName));
	PackGetStr(p, "ConnectionName", s->ConnectionName, sizeof(s->ConnectionName));

	if (PackGetDataSize(p, "SessionKey") == SHA1_SIZE)
	{
		PackGetData(p, "SessionKey", s->SessionKey);
	}

	s->SessionStatus = PackGetInt(p, "SessionStatus");
	s->ServerPort = PackGetInt(p, "ServerPort");
	s->ServerProductVer = PackGetInt(p, "ServerProductVer");
	s->ServerProductBuild = PackGetInt(p, "ServerProductBuild");
	s->NumConnectionsEstablished = PackGetInt(p, "NumConnectionsEstablished");
	s->MaxTcpConnections = PackGetInt(p, "MaxTcpConnections");
	s->NumTcpConnections = PackGetInt(p, "NumTcpConnections");
	s->NumTcpConnectionsUpload = PackGetInt(p, "NumTcpConnectionsUpload");
	s->NumTcpConnectionsDownload = PackGetInt(p, "NumTcpConnectionsDownload");

	s->StartTime = PackGetInt64(p, "StartTime");
	/* !!! Do not correct the spelling to keep the backward protocol compatibility !!!  */
	s->FirstConnectionEstablisiedTime = PackGetInt64(p, "FirstConnectionEstablisiedTime");
	s->CurrentConnectionEstablishTime = PackGetInt64(p, "CurrentConnectionEstablishTime");
	s->TotalSendSize = PackGetInt64(p, "TotalSendSize");
	s->TotalRecvSize = PackGetInt64(p, "TotalRecvSize");
	s->TotalSendSizeReal = PackGetInt64(p, "TotalSendSizeReal");
	s->TotalRecvSizeReal = PackGetInt64(p, "TotalRecvSizeReal");

	s->Active = PackGetInt(p, "Active") ? true : false;
	s->Connected = PackGetInt(p, "Connected") ? true : false;
	s->HalfConnection = PackGetInt(p, "HalfConnection") ? true : false;
	s->QoS = PackGetInt(p, "QoS") ? true : false;
	s->UseEncrypt = PackGetInt(p, "UseEncrypt") ? true : false;
	s->UseCompress = PackGetInt(p, "UseCompress") ? true : false;
	s->IsRUDPSession = PackGetInt(p, "IsRUDPSession") ? true : false;
	PackGetStr(p, "UnderlayProtocol", s->UnderlayProtocol, sizeof(s->UnderlayProtocol));
	s->IsUdpAccelerationEnabled = PackGetInt(p, "IsUdpAccelerationEnabled") ? true : false;
	s->IsUsingUdpAcceleration = PackGetInt(p, "IsUsingUdpAcceleration") ? true : false;

	s->IsBridgeMode = PackGetBool(p, "IsBridgeMode");
	s->IsMonitorMode = PackGetBool(p, "IsMonitorMode");

	s->VLanId = PackGetInt(p, "VLanId");

	b = PackGetBuf(p, "ServerX");
	if (b != NULL)
	{
		s->ServerX = BufToX(b, false);
		FreeBuf(b);
	}

	b = PackGetBuf(p, "ClientX");
	if (b != NULL)
	{
		s->ClientX = BufToX(b, false);
		FreeBuf(b);
	}

	InRpcPolicy(&s->Policy, p);

	InRpcTraffic(&s->Traffic, p);
}