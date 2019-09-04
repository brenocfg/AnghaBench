#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sign ;
typedef  int /*<<< orphan*/  my_ip ;
struct TYPE_19__ {int bits; int /*<<< orphan*/  is_compatible_bit; } ;
typedef  TYPE_4__ X ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_22__ {int AuthType; char* Username; TYPE_4__* ClientX; int /*<<< orphan*/  ClientK; int /*<<< orphan*/  PlainPassword; int /*<<< orphan*/  HashedPassword; } ;
struct TYPE_21__ {char* HubName; int MaxConnection; int UseEncrypt; int UseCompress; int HalfConnection; int RequireBridgeRoutingMode; int RequireMonitorMode; int NoUdpAcceleration; scalar_t__ DisableQoS; } ;
struct TYPE_20__ {int UseTicket; scalar_t__ Err; int Protocol; char* ClientStr; int ClientVer; int ClientBuild; int /*<<< orphan*/  FirstSock; TYPE_3__* Session; TYPE_1__* Cedar; int /*<<< orphan*/ * Ticket; void* ClientX; int /*<<< orphan*/  Random; } ;
struct TYPE_18__ {int ForceStopFlag; TYPE_2__* UdpAccel; TYPE_6__* ClientOption; TYPE_7__* ClientAuth; } ;
struct TYPE_17__ {int MyPort; int /*<<< orphan*/ * MyKey; int /*<<< orphan*/  MyIp; } ;
struct TYPE_16__ {int ClientId; } ;
typedef  int /*<<< orphan*/  RPC_WINVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  NODE_INFO ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_5__ CONNECTION ;
typedef  TYPE_6__ CLIENT_OPTION ;
typedef  TYPE_7__ CLIENT_AUTH ;

/* Variables and functions */
 int AUTHTYPE_TICKET ; 
#define  CLIENT_AUTHTYPE_ANONYMOUS 132 
#define  CLIENT_AUTHTYPE_CERT 131 
#define  CLIENT_AUTHTYPE_PASSWORD 130 
#define  CLIENT_AUTHTYPE_PLAIN_PASSWORD 129 
#define  CLIENT_AUTHTYPE_SECURE 128 
 int /*<<< orphan*/  ClientSecureSign (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__**) ; 
 void* CloneX (TYPE_4__*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CreateNodeInfo (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ ERR_DISCONNECTED ; 
 scalar_t__ ERR_PROTOCOL_ERROR ; 
 scalar_t__ ERR_SECURE_DEVICE_OPEN_FAILED ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (TYPE_4__*) ; 
 int /*<<< orphan*/  GenerateMachineUniqueHash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetWinVer (int /*<<< orphan*/ *) ; 
 int HttpClientSend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsLocalHostIP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcNodeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcWinVer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackAddClientVersion (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackAddIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * PackLoginWithAnonymous (char*,char*) ; 
 int /*<<< orphan*/ * PackLoginWithCert (char*,char*,TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PackLoginWithPassword (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PackLoginWithPlainPassword (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RsaSignEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SecurePassword (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ StrLen (char*) ; 
 int UDP_ACCELERATION_COMMON_KEY_SIZE ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZeroIP4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroIP6 (int /*<<< orphan*/ *) ; 
 char* _SS (char*) ; 

bool ClientUploadAuth(CONNECTION *c)
{
	PACK *p = NULL;
	CLIENT_AUTH *a;
	CLIENT_OPTION *o;
	X *x;
	bool ret;
	NODE_INFO info;
	UCHAR secure_password[SHA1_SIZE];
	UCHAR sign[4096 / 8];
	UCHAR unique[SHA1_SIZE];
	RPC_WINVER v;
	// Validate arguments
	if (c == NULL)
	{
		return false;
	}

	Zero(sign, sizeof(sign));

	a = c->Session->ClientAuth;
	o = c->Session->ClientOption;

	if (c->UseTicket == false)
	{
		switch (a->AuthType)
		{
		case CLIENT_AUTHTYPE_ANONYMOUS:
			// Anonymous authentication
			p = PackLoginWithAnonymous(o->HubName, a->Username);
			break;

		case CLIENT_AUTHTYPE_PASSWORD:
			// Password authentication
			SecurePassword(secure_password, a->HashedPassword, c->Random);
			p = PackLoginWithPassword(o->HubName, a->Username, secure_password);
			break;

		case CLIENT_AUTHTYPE_PLAIN_PASSWORD:
			// Plaintext password authentication
			p = PackLoginWithPlainPassword(o->HubName, a->Username, a->PlainPassword);
			break;

		case CLIENT_AUTHTYPE_CERT:
			// Certificate authentication
			if (a->ClientX != NULL && a->ClientX->is_compatible_bit &&
				a->ClientX->bits != 0 && (a->ClientX->bits / 8) <= sizeof(sign))
			{
				if (RsaSignEx(sign, c->Random, SHA1_SIZE, a->ClientK, a->ClientX->bits))
				{
					p = PackLoginWithCert(o->HubName, a->Username, a->ClientX, sign, a->ClientX->bits / 8);
					c->ClientX = CloneX(a->ClientX);
				}
			}
			break;

		case CLIENT_AUTHTYPE_SECURE:
			// Authentication by secure device
			if (ClientSecureSign(c, sign, c->Random, &x))
			{
				p = PackLoginWithCert(o->HubName, a->Username, x, sign, x->bits / 8);
				c->ClientX = CloneX(x);
				FreeX(x);
			}
			else
			{
				c->Err = ERR_SECURE_DEVICE_OPEN_FAILED;
				c->Session->ForceStopFlag = true;
			}
			break;
		}
	}
	else
	{
		// Ticket
		p = NewPack();
		PackAddStr(p, "method", "login");
		PackAddStr(p, "hubname", o->HubName);
		PackAddStr(p, "username", a->Username);
		PackAddInt(p, "authtype", AUTHTYPE_TICKET);
		PackAddData(p, "ticket", c->Ticket, SHA1_SIZE);
	}

	if (p == NULL)
	{
		// Error
		if (c->Err != ERR_SECURE_DEVICE_OPEN_FAILED)
		{
			c->Err = ERR_PROTOCOL_ERROR;
		}
		return false;
	}

	PackAddClientVersion(p, c);

	// Protocol
	PackAddInt(p, "protocol", c->Protocol);

	// Version, etc.
	PackAddStr(p, "hello", c->ClientStr);
	PackAddInt(p, "version", c->ClientVer);
	PackAddInt(p, "build", c->ClientBuild);
	PackAddInt(p, "client_id", c->Cedar->ClientId);

	// The maximum number of connections
	PackAddInt(p, "max_connection", o->MaxConnection);
	// Flag to use of cryptography
	PackAddInt(p, "use_encrypt", o->UseEncrypt == false ? 0 : 1);
	// Data compression flag
	PackAddInt(p, "use_compress", o->UseCompress == false ? 0 : 1);
	// Half connection flag
	PackAddInt(p, "half_connection", o->HalfConnection == false ? 0 : 1);

	// Bridge / routing mode flag
	PackAddBool(p, "require_bridge_routing_mode", o->RequireBridgeRoutingMode);

	// Monitor mode flag
	PackAddBool(p, "require_monitor_mode", o->RequireMonitorMode);

	// VoIP / QoS flag
	PackAddBool(p, "qos", o->DisableQoS ? false : true);

	// Bulk transfer support
	PackAddBool(p, "support_bulk_on_rudp", true);
	PackAddBool(p, "support_hmac_on_bulk_of_rudp", true);

	// UDP recovery support
	PackAddBool(p, "support_udp_recovery", true);

	// Unique ID
	GenerateMachineUniqueHash(unique);
	PackAddData(p, "unique_id", unique, SHA1_SIZE);

	// UDP acceleration function using flag
	if (o->NoUdpAcceleration == false && c->Session->UdpAccel != NULL)
	{
		IP my_ip;

		Zero(&my_ip, sizeof(my_ip));

		PackAddBool(p, "use_udp_acceleration", true);

		Copy(&my_ip, &c->Session->UdpAccel->MyIp, sizeof(IP));
		if (IsLocalHostIP(&my_ip))
		{
			if (IsIP4(&my_ip))
			{
				ZeroIP4(&my_ip);
			}
			else
			{
				ZeroIP6(&my_ip);
			}
		}

		PackAddIp(p, "udp_acceleration_client_ip", &my_ip);
		PackAddInt(p, "udp_acceleration_client_port", c->Session->UdpAccel->MyPort);
		PackAddData(p, "udp_acceleration_client_key", c->Session->UdpAccel->MyKey, UDP_ACCELERATION_COMMON_KEY_SIZE);
		PackAddBool(p, "support_hmac_on_udp_acceleration", true);
		PackAddBool(p, "support_udp_accel_fast_disconnect_detect", true);
	}

	// Brand string for the connection limit
	{
		char *branded_ctos = _SS("BRANDED_C_TO_S");
		if(StrLen(branded_ctos) > 0)
		{
			PackAddStr(p, "branded_ctos", branded_ctos);
		}
	}

	// Node information
	CreateNodeInfo(&info, c);
	OutRpcNodeInfo(p, &info);

	// OS information
	GetWinVer(&v);
	OutRpcWinVer(p, &v);

	ret = HttpClientSend(c->FirstSock, p);
	if (ret == false)
	{
		c->Err = ERR_DISCONNECTED;
	}

	FreePack(p);

	return ret;
}