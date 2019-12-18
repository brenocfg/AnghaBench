#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int MaxConnection; int UseEncrypt; int UseCompress; int HalfConnection; int Timeout; int IsAzureSession; int SessionKey32; int VLanId; int UdpAccelFastDisconnectDetect; int EnableHMacOnBulkOfRUDP; int EnableUdpRecovery; TYPE_5__* Connection; scalar_t__ EnableBulkOnRUDP; TYPE_2__* UdpAccel; TYPE_1__* Hub; int /*<<< orphan*/  IpcMacAddress; scalar_t__ InProcMode; scalar_t__ NoSendSignature; int /*<<< orphan*/  UdpSendKey; int /*<<< orphan*/  UdpRecvKey; int /*<<< orphan*/  Policy; int /*<<< orphan*/  SessionKey; scalar_t__ QoS; int /*<<< orphan*/  Name; } ;
struct TYPE_14__ {int /*<<< orphan*/  Reverse_MyServerGlobalIp; TYPE_4__* BulkSendKey; TYPE_3__* BulkRecvKey; } ;
struct TYPE_13__ {scalar_t__ Protocol; TYPE_6__* FirstSock; int /*<<< orphan*/  Name; } ;
struct TYPE_12__ {int /*<<< orphan*/  Data; } ;
struct TYPE_11__ {int /*<<< orphan*/  Data; } ;
struct TYPE_10__ {int MyPort; int MyCookie; int YourCookie; int UseHMac; int /*<<< orphan*/  PlainTextMode; int /*<<< orphan*/  MyKey; int /*<<< orphan*/  MyIp; } ;
struct TYPE_9__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_6__ SOCK ;
typedef  TYPE_7__ SESSION ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 scalar_t__ CONNECTION_UDP ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackAddIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ ,int) ; 
 int SHA1_SIZE ; 
 int UDP_ACCELERATION_COMMON_KEY_SIZE ; 

PACK *PackWelcome(SESSION *s)
{
	PACK *p;
	// Validate arguments
	if (s == NULL)
	{
		return NULL;
	}

	p = NewPack();

	// Session name
	PackAddStr(p, "session_name", s->Name);

	// Connection name
	PackAddStr(p, "connection_name", s->Connection->Name);

	// Parameters
	PackAddInt(p, "max_connection", s->MaxConnection);
	PackAddInt(p, "use_encrypt", s->UseEncrypt == false ? 0 : 1);
	PackAddInt(p, "use_compress", s->UseCompress == false ? 0 : 1);
	PackAddInt(p, "half_connection", s->HalfConnection == false ? 0 : 1);
	PackAddInt(p, "timeout", s->Timeout);
	PackAddInt(p, "qos", s->QoS ? 1 : 0);
	PackAddInt(p, "is_azure_session", s->IsAzureSession);

	// Session key
	PackAddData(p, "session_key", s->SessionKey, SHA1_SIZE);
	PackAddInt(p, "session_key_32", s->SessionKey32);

	// Policy
	PackAddPolicy(p, s->Policy);

	// VLAN ID
	PackAddInt(p, "vlan_id", s->VLanId);

	if (s->Connection->Protocol == CONNECTION_UDP)
	{
		// In the case of UDP protocol, generate 2 pairs of key
		Rand(s->UdpSendKey, sizeof(s->UdpSendKey));
		Rand(s->UdpRecvKey, sizeof(s->UdpRecvKey));

		// Send to client by exchanging 2 keys
		PackAddData(p, "udp_send_key", s->UdpRecvKey, sizeof(s->UdpRecvKey));
		PackAddData(p, "udp_recv_key", s->UdpSendKey, sizeof(s->UdpSendKey));
	}

	// no_send_signature
	if (s->NoSendSignature)
	{
		PackAddBool(p, "no_send_signature", true);
	}

	if (s->InProcMode)
	{
		// MAC address for IPC
		PackAddData(p, "IpcMacAddress", s->IpcMacAddress, 6);

		// Virtual HUB name
		PackAddStr(p, "IpcHubName", s->Hub->Name);
	}

	if (s->UdpAccel != NULL)
	{
		// UDP acceleration function
		PackAddBool(p, "use_udp_acceleration", true);
		PackAddIp(p, "udp_acceleration_server_ip", &s->UdpAccel->MyIp);
		PackAddInt(p, "udp_acceleration_server_port", s->UdpAccel->MyPort);
		PackAddData(p, "udp_acceleration_server_key", s->UdpAccel->MyKey, UDP_ACCELERATION_COMMON_KEY_SIZE);
		PackAddInt(p, "udp_acceleration_server_cookie", s->UdpAccel->MyCookie);
		PackAddInt(p, "udp_acceleration_client_cookie", s->UdpAccel->YourCookie);
		PackAddBool(p, "udp_acceleration_use_encryption", !s->UdpAccel->PlainTextMode);
		PackAddBool(p, "use_hmac_on_udp_acceleration", s->UdpAccel->UseHMac);
		PackAddBool(p, "udp_accel_fast_disconnect_detect", s->UdpAccelFastDisconnectDetect);
	}

	if (s->EnableBulkOnRUDP)
	{
		// Allow bulk transfer on R-UDP
		PackAddBool(p, "enable_bulk_on_rudp", true);
		PackAddBool(p, "enable_hmac_on_bulk_of_rudp", s->EnableHMacOnBulkOfRUDP);

		PackAddData(p, "bulk_on_rudp_send_key", s->Connection->FirstSock->BulkRecvKey->Data, SHA1_SIZE);
		PackAddData(p, "bulk_on_rudp_recv_key", s->Connection->FirstSock->BulkSendKey->Data, SHA1_SIZE);
	}

	if (s->IsAzureSession)
	{
		if (s->Connection != NULL && s->Connection->FirstSock != NULL)
		{
			SOCK *sock = s->Connection->FirstSock;

			PackAddIp(p, "azure_real_server_global_ip", &sock->Reverse_MyServerGlobalIp);
		}
	}

	PackAddBool(p, "enable_udp_recovery", s->EnableUdpRecovery);

	return p;
}