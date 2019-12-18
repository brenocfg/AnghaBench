#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ClientX; int /*<<< orphan*/ * ServerX; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  Policy; int /*<<< orphan*/  VLanId; int /*<<< orphan*/  TotalRecvSizeReal; int /*<<< orphan*/  TotalSendSizeReal; int /*<<< orphan*/  TotalRecvSize; int /*<<< orphan*/  TotalSendSize; int /*<<< orphan*/  CurrentConnectionEstablishTime; int /*<<< orphan*/  FirstConnectionEstablisiedTime; int /*<<< orphan*/  StartTime; int /*<<< orphan*/  IsMonitorMode; int /*<<< orphan*/  IsBridgeMode; int /*<<< orphan*/  IsUsingUdpAcceleration; int /*<<< orphan*/  IsUdpAccelerationEnabled; int /*<<< orphan*/  UnderlayProtocol; int /*<<< orphan*/  IsRUDPSession; int /*<<< orphan*/  UseCompress; int /*<<< orphan*/  UseEncrypt; int /*<<< orphan*/  NumTcpConnectionsDownload; int /*<<< orphan*/  NumTcpConnectionsUpload; int /*<<< orphan*/  NumTcpConnections; int /*<<< orphan*/  MaxTcpConnections; int /*<<< orphan*/  QoS; int /*<<< orphan*/  HalfConnection; int /*<<< orphan*/  NumConnectionsEstablished; int /*<<< orphan*/  ServerProductBuild; int /*<<< orphan*/  ServerProductVer; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  SessionStatus; int /*<<< orphan*/  Connected; int /*<<< orphan*/  Active; int /*<<< orphan*/  SessionKey; int /*<<< orphan*/  ConnectionName; int /*<<< orphan*/  SessionName; int /*<<< orphan*/  CipherName; int /*<<< orphan*/  ServerProductName; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ RPC_CLIENT_GET_CONNECTION_STATUS ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcTraffic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddTime64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/ * XToBuf (int /*<<< orphan*/ *,int) ; 

void OutRpcClientGetConnectionStatus(PACK *p, RPC_CLIENT_GET_CONNECTION_STATUS *c)
{
	BUF *b;
	// Validate arguments
	if (p == NULL || c == NULL)
	{
		return;
	}

	PackAddUniStr(p, "AccountName", c->AccountName);

	PackAddStr(p, "ServerName", c->ServerName);
	PackAddStr(p, "ServerProductName", c->ServerProductName);
	PackAddStr(p, "CipherName", c->CipherName);
	PackAddStr(p, "SessionName", c->SessionName);
	PackAddStr(p, "ConnectionName", c->ConnectionName);

	PackAddData(p, "SessionKey", c->SessionKey, SHA1_SIZE);

	PackAddBool(p, "Active", c->Active);
	PackAddBool(p, "Connected", c->Connected);
	PackAddInt(p, "SessionStatus", c->SessionStatus);
	PackAddInt(p, "ServerPort", c->ServerPort);
	PackAddInt(p, "ServerProductVer", c->ServerProductVer);
	PackAddInt(p, "ServerProductBuild", c->ServerProductBuild);
	PackAddInt(p, "NumConnectionsEstablished", c->NumConnectionsEstablished);
	PackAddBool(p, "HalfConnection", c->HalfConnection);
	PackAddBool(p, "QoS", c->QoS);
	PackAddInt(p, "MaxTcpConnections", c->MaxTcpConnections);
	PackAddInt(p, "NumTcpConnections", c->NumTcpConnections);
	PackAddInt(p, "NumTcpConnectionsUpload", c->NumTcpConnectionsUpload);
	PackAddInt(p, "NumTcpConnectionsDownload", c->NumTcpConnectionsDownload);
	PackAddBool(p, "UseEncrypt", c->UseEncrypt);
	PackAddBool(p, "UseCompress", c->UseCompress);
	PackAddBool(p, "IsRUDPSession", c->IsRUDPSession);
	PackAddStr(p, "UnderlayProtocol", c->UnderlayProtocol);
	PackAddBool(p, "IsUdpAccelerationEnabled", c->IsUdpAccelerationEnabled);
	PackAddBool(p, "IsUsingUdpAcceleration", c->IsUsingUdpAcceleration);

	PackAddBool(p, "IsBridgeMode", c->IsBridgeMode);
	PackAddBool(p, "IsMonitorMode", c->IsMonitorMode);

	PackAddTime64(p, "StartTime", c->StartTime);
	PackAddTime64(p, "FirstConnectionEstablisiedTime", c->FirstConnectionEstablisiedTime);
	PackAddTime64(p, "CurrentConnectionEstablishTime", c->CurrentConnectionEstablishTime);
	PackAddInt64(p, "TotalSendSize", c->TotalSendSize);
	PackAddInt64(p, "TotalRecvSize", c->TotalRecvSize);
	PackAddInt64(p, "TotalSendSizeReal", c->TotalSendSizeReal);
	PackAddInt64(p, "TotalRecvSizeReal", c->TotalRecvSizeReal);

	PackAddInt(p, "VLanId", c->VLanId);

	OutRpcPolicy(p, &c->Policy);

	OutRpcTraffic(p, &c->Traffic);

	if (c->ServerX != NULL)
	{
		b = XToBuf(c->ServerX, false);
		PackAddBuf(p, "ServerX", b);
		FreeBuf(b);
	}

	if (c->ClientX != NULL)
	{
		b = XToBuf(c->ClientX, false);
		PackAddBuf(p, "ClientX", b);
		FreeBuf(b);
	}
}