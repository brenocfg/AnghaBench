#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int Active; scalar_t__ SessionStatus; int Connected; scalar_t__ NumTcpConnections; int /*<<< orphan*/  NumConnectionsEstablished; void* FirstConnectionEstablisiedTime; void* StartTime; int /*<<< orphan*/  IsMonitorMode; int /*<<< orphan*/  IsBridgeMode; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  ConnectionName; int /*<<< orphan*/  SessionName; int /*<<< orphan*/  TotalSendSizeReal; int /*<<< orphan*/  TotalRecvSizeReal; int /*<<< orphan*/  TotalRecvSize; int /*<<< orphan*/  TotalSendSize; int /*<<< orphan*/  Policy; int /*<<< orphan*/ * SessionKey; int /*<<< orphan*/  IsUsingUdpAcceleration; int /*<<< orphan*/  IsUdpAccelerationEnabled; int /*<<< orphan*/  UnderlayProtocol; int /*<<< orphan*/  IsRUDPSession; int /*<<< orphan*/  UseCompress; int /*<<< orphan*/  CipherName; scalar_t__ UseEncrypt; int /*<<< orphan*/  NumTcpConnectionsUpload; int /*<<< orphan*/  NumTcpConnectionsDownload; scalar_t__ HalfConnection; int /*<<< orphan*/  QoS; int /*<<< orphan*/  VLanId; int /*<<< orphan*/  MaxTcpConnections; void* CurrentConnectionEstablishTime; void* ClientX; void* ServerX; int /*<<< orphan*/  ServerProductBuild; int /*<<< orphan*/  ServerProductVer; int /*<<< orphan*/  ServerProductName; int /*<<< orphan*/  AccountName; } ;
struct TYPE_14__ {scalar_t__ ClientStatus; int ServerMode; int /*<<< orphan*/  lock; int /*<<< orphan*/  NumConnectionsEstablished; int /*<<< orphan*/  FirstConnectionEstablisiedTime; int /*<<< orphan*/  CreatedTime; TYPE_3__* Connection; int /*<<< orphan*/  IsMonitorMode; int /*<<< orphan*/  IsBridgeMode; int /*<<< orphan*/  TrafficLock; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  Name; int /*<<< orphan*/  TotalRecvSizeReal; int /*<<< orphan*/  TotalSendSizeReal; int /*<<< orphan*/  TotalSendSize; int /*<<< orphan*/  TotalRecvSize; int /*<<< orphan*/  Policy; int /*<<< orphan*/  SessionKey; int /*<<< orphan*/  IsUsingUdpAcceleration; int /*<<< orphan*/  UseUdpAcceleration; int /*<<< orphan*/  UnderlayProtocol; int /*<<< orphan*/  IsRUDPSession; int /*<<< orphan*/  UseCompress; scalar_t__ UseEncrypt; int /*<<< orphan*/  QoS; int /*<<< orphan*/  VLanId; scalar_t__ HalfConnection; int /*<<< orphan*/  MaxConnection; int /*<<< orphan*/  CurrentConnectionEstablishTime; TYPE_1__* ClientOption; } ;
struct TYPE_13__ {int Direction; } ;
struct TYPE_12__ {scalar_t__ Protocol; int /*<<< orphan*/  lock; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  Name; int /*<<< orphan*/  CipherName; TYPE_2__* Tcp; int /*<<< orphan*/  ClientX; int /*<<< orphan*/  ServerX; int /*<<< orphan*/  ServerBuild; int /*<<< orphan*/  ServerVer; int /*<<< orphan*/  ServerStr; } ;
struct TYPE_11__ {int /*<<< orphan*/  TcpSockList; } ;
struct TYPE_10__ {int /*<<< orphan*/  AccountName; } ;
typedef  int /*<<< orphan*/  TRAFFIC ;
typedef  TYPE_4__ TCPSOCK ;
typedef  TYPE_5__ SESSION ;
typedef  TYPE_6__ RPC_CLIENT_GET_CONNECTION_STATUS ;
typedef  int /*<<< orphan*/  POLICY ;

/* Variables and functions */
 scalar_t__ CLIENT_STATUS_ESTABLISHED ; 
 scalar_t__ CONNECTION_TCP ; 
 void* CloneX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int TCP_SERVER_TO_CLIENT ; 
 void* TickToTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void CiGetSessionStatus(RPC_CLIENT_GET_CONNECTION_STATUS *st, SESSION *s)
{
	// Validate arguments
	if (st == NULL || s == NULL)
	{
		return;
	}

	Lock(s->lock);
	{
		// Operation flag
		st->Active = true;

		// Session status
		st->SessionStatus = s->ClientStatus;

		// Account name
		UniStrCpy(st->AccountName, sizeof(st->AccountName), s->ClientOption->AccountName);

		if (s->ClientStatus == CLIENT_STATUS_ESTABLISHED && s->Connection != NULL)
		{
			Lock(s->Connection->lock);
			{
				// Connected flag
				st->Connected = true;
				// Product name
				StrCpy(st->ServerProductName, sizeof(st->ServerProductName), s->Connection->ServerStr);
				// Version
				st->ServerProductVer = s->Connection->ServerVer;
				// Build Number
				st->ServerProductBuild = s->Connection->ServerBuild;
				// Server certificate
				st->ServerX = CloneX(s->Connection->ServerX);
				// Client certificate
				st->ClientX = CloneX(s->Connection->ClientX);
				// Connection completion time of this connection
				st->CurrentConnectionEstablishTime = TickToTime(s->CurrentConnectionEstablishTime);
				// Maximum number of the TCP connections
				st->MaxTcpConnections = s->MaxConnection;
				// Half-connection
				st->HalfConnection = s->HalfConnection;
				// VLAN
				st->VLanId = s->VLanId;
				// VoIP / QoS
				st->QoS = s->QoS;
				if (s->Connection->Protocol == CONNECTION_TCP)
				{
					UINT i;
					// Number of current TCP connections
					LockList(s->Connection->Tcp->TcpSockList);
					{
						st->NumTcpConnections = LIST_NUM(s->Connection->Tcp->TcpSockList);
						if (st->HalfConnection)
						{
							for (i = 0;i < st->NumTcpConnections;i++)
							{
								TCPSOCK *ts = LIST_DATA(s->Connection->Tcp->TcpSockList, i);
								if (ts->Direction & TCP_SERVER_TO_CLIENT)
								{
									st->NumTcpConnectionsDownload++;
								}
								else
								{
									st->NumTcpConnectionsUpload++;
								}
							}
						}
					}
					UnlockList(s->Connection->Tcp->TcpSockList);
				}
				// Use of encryption
				st->UseEncrypt = s->UseEncrypt;
				if (st->UseEncrypt)
				{
					StrCpy(st->CipherName, sizeof(st->CipherName), s->Connection->CipherName);
				}
				// Use of compression
				st->UseCompress = s->UseCompress;
				// R-UDP
				st->IsRUDPSession = s->IsRUDPSession;
				// Physical communication protocol
				StrCpy(st->UnderlayProtocol, sizeof(st->UnderlayProtocol), s->UnderlayProtocol);
				// UDP acceleration function
				st->IsUdpAccelerationEnabled = s->UseUdpAcceleration;
				st->IsUsingUdpAcceleration = s->IsUsingUdpAcceleration;
				// Session key
				Copy(st->SessionKey, s->SessionKey, SHA1_SIZE);
				// Policy
				Copy(&st->Policy, s->Policy, sizeof(POLICY));
				// Data size
				if (s->ServerMode == false)
				{
					st->TotalSendSize = s->TotalSendSize;
					st->TotalRecvSize = s->TotalRecvSize;
					st->TotalRecvSizeReal = s->TotalRecvSizeReal;
					st->TotalSendSizeReal = s->TotalSendSizeReal;
				}
				else
				{
					st->TotalSendSize = s->TotalRecvSize;
					st->TotalRecvSize = s->TotalSendSize;
					st->TotalRecvSizeReal = s->TotalSendSizeReal;
					st->TotalSendSizeReal = s->TotalRecvSizeReal;
				}
				// Session name
				StrCpy(st->SessionName, sizeof(st->SessionName), s->Name);
				// Connection name
				StrCpy(st->ConnectionName, sizeof(st->ConnectionName), s->Connection->Name);
				// Server name
				StrCpy(st->ServerName, sizeof(st->ServerName), s->Connection->ServerName);
				// Port number
				st->ServerPort = s->Connection->ServerPort;
				// Traffic data
				Lock(s->TrafficLock);
				{
					Copy(&st->Traffic, s->Traffic, sizeof(TRAFFIC));
				}
				Unlock(s->TrafficLock);

				st->IsBridgeMode = s->IsBridgeMode;
				st->IsMonitorMode = s->IsMonitorMode;
			}
			Unlock(s->Connection->lock);
		}
		// Connection start time
		st->StartTime = TickToTime(s->CreatedTime);
		// Connection completion time of the first connection
		/* !!! Do not correct the spelling to keep the backward protocol compatibility !!!  */
		st->FirstConnectionEstablisiedTime = TickToTime(s->FirstConnectionEstablisiedTime);
		// Number of connections have been established so far
		st->NumConnectionsEstablished = s->NumConnectionsEstablished;
	}
	Unlock(s->lock);
}