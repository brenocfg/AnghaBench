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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int NextRadiusPacketId; int /*<<< orphan*/  PEAP_CurrentReceivingMsg; scalar_t__ LastRecvEapId; int /*<<< orphan*/  Username; int /*<<< orphan*/  ClientIpStr; int /*<<< orphan*/  CalledStationStr; int /*<<< orphan*/  SharedSecret; scalar_t__ GiveupTimeout; scalar_t__ ResendTimeout; scalar_t__ ServerPort; int /*<<< orphan*/  ServerIp; int /*<<< orphan*/  UdpSock; int /*<<< orphan*/  Ref; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ EAP_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IsIP6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewBuf () ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/  NewUDPEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RADIUS_RETRY_INTERVAL ; 
 scalar_t__ RADIUS_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

EAP_CLIENT *NewEapClient(IP *server_ip, UINT server_port, char *shared_secret, UINT resend_timeout, UINT giveup_timeout, char *client_ip_str, char *username, char *hubname)
{
	EAP_CLIENT *e;
	if (server_ip == NULL)
	{
		return NULL;
	}
	if (resend_timeout == 0)
	{
		resend_timeout = RADIUS_RETRY_INTERVAL;
	}
	if (giveup_timeout == 0)
	{
		giveup_timeout = RADIUS_RETRY_TIMEOUT;
	}

	e = ZeroMalloc(sizeof(EAP_CLIENT));

	e->Ref = NewRef();

	e->NextRadiusPacketId = 1;

	e->UdpSock = NewUDPEx(0, IsIP6(server_ip));
	Copy(&e->ServerIp, server_ip, sizeof(IP));
	e->ServerPort = server_port;
	e->ResendTimeout = resend_timeout;
	e->GiveupTimeout = giveup_timeout;
	StrCpy(e->SharedSecret, sizeof(e->SharedSecret), shared_secret);

	StrCpy(e->CalledStationStr, sizeof(e->CalledStationStr), hubname);
	StrCpy(e->ClientIpStr, sizeof(e->ClientIpStr), client_ip_str);
	StrCpy(e->Username, sizeof(e->Username), username);
	e->LastRecvEapId = 0;

	e->PEAP_CurrentReceivingMsg = NewBuf();

	return e;
}