#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int UCHAR ;
struct TYPE_7__ {int Size; int* Data; } ;
struct TYPE_6__ {int Opcode; int /*<<< orphan*/  ClasslessRoute; int /*<<< orphan*/  WinsServer2; int /*<<< orphan*/  WinsServer; int /*<<< orphan*/  DnsServer2; int /*<<< orphan*/  DnsServer; int /*<<< orphan*/  Gateway; int /*<<< orphan*/ * DomainName; int /*<<< orphan*/  ServerAddress; int /*<<< orphan*/  LeaseTime; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/ * Hostname; int /*<<< orphan*/  RequestedIp; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ DHCP_OPTION_LIST ;
typedef  TYPE_2__ DHCP_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int*,int) ; 
#define  DHCP_ACK 131 
#define  DHCP_DISCOVER 130 
 int /*<<< orphan*/  DHCP_ID_CLASSLESS_ROUTE ; 
 int /*<<< orphan*/  DHCP_ID_DNS_ADDR ; 
 int /*<<< orphan*/  DHCP_ID_DOMAIN_NAME ; 
 int /*<<< orphan*/  DHCP_ID_GATEWAY_ADDR ; 
 int /*<<< orphan*/  DHCP_ID_HOST_NAME ; 
 int /*<<< orphan*/  DHCP_ID_LEASE_TIME ; 
 int /*<<< orphan*/  DHCP_ID_MESSAGE_TYPE ; 
 int /*<<< orphan*/  DHCP_ID_MS_CLASSLESS_ROUTE ; 
 int /*<<< orphan*/  DHCP_ID_REQUEST_IP_ADDRESS ; 
 int /*<<< orphan*/  DHCP_ID_SERVER_ADDRESS ; 
 int /*<<< orphan*/  DHCP_ID_SUBNET_MASK ; 
 int /*<<< orphan*/  DHCP_ID_WINS_ADDR ; 
#define  DHCP_OFFER 129 
#define  DHCP_REQUEST 128 
 int /*<<< orphan*/  DhcpParseClasslessRouteData (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  FreeDhcpOptions (int /*<<< orphan*/ *) ; 
 TYPE_2__* GetDhcpOption (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/ * ParseDhcpOptions (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_UINT (int*) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

DHCP_OPTION_LIST *ParseDhcpOptionList(void *data, UINT size)
{
	DHCP_OPTION_LIST *ret;
	LIST *o;
	DHCP_OPTION *a;
	// Validate arguments
	if (data == NULL)
	{
		return NULL;
	}

	// Parse the list
	o = ParseDhcpOptions(data, size);
	if (o == NULL)
	{
		return NULL;
	}

	ret = ZeroMalloc(sizeof(DHCP_OPTION_LIST));

	// Get the opcode
	a = GetDhcpOption(o, DHCP_ID_MESSAGE_TYPE);
	if (a != NULL)
	{
		if (a->Size == 1)
		{
			ret->Opcode = *((UCHAR *)a->Data);
		}
	}

	switch (ret->Opcode)
	{
	case DHCP_DISCOVER:
	case DHCP_REQUEST:
		// Parse this more finely because this is client requests
		// Requested IP address
		a = GetDhcpOption(o, DHCP_ID_REQUEST_IP_ADDRESS);
		if (a != NULL && a->Size == 4)
		{
			Copy(&ret->RequestedIp, a->Data, 4);
		}
		// Host name
		a = GetDhcpOption(o, DHCP_ID_HOST_NAME);
		if (a != NULL)
		{
			if (a->Size > 1)
			{
				Copy(ret->Hostname, a->Data, MIN(a->Size, sizeof(ret->Hostname) - 1));
			}
		}
		break;

	case DHCP_OFFER:
	case DHCP_ACK:
		// Subnet mask
		a = GetDhcpOption(o, DHCP_ID_SUBNET_MASK);
		if (a != NULL && a->Size >= 4)
		{
			Copy(&ret->SubnetMask, a->Data, 4);
		}

		// Lease time
		a = GetDhcpOption(o, DHCP_ID_LEASE_TIME);
		if (a != NULL && a->Size == 4)
		{
			ret->LeaseTime = READ_UINT(a->Data);
		}

		// Server IP address
		a = GetDhcpOption(o, DHCP_ID_SERVER_ADDRESS);
		if (a != NULL && a->Size >= 4)
		{
			Copy(&ret->ServerAddress, a->Data, 4);
		}

		// Domain name
		a = GetDhcpOption(o, DHCP_ID_DOMAIN_NAME);
		if (a != NULL && a->Size >= 1)
		{
			Zero(ret->DomainName, sizeof(ret->DomainName));
			Copy(ret->DomainName, a->Data, MIN(a->Size, sizeof(ret->DomainName) - 1));
		}

		// Gateway
		a = GetDhcpOption(o, DHCP_ID_GATEWAY_ADDR);
		if (a != NULL && a->Size >= 4)
		{
			Copy(&ret->Gateway, a->Data, 4);
		}

		// DNS server
		a = GetDhcpOption(o, DHCP_ID_DNS_ADDR);
		if (a != NULL && a->Size >= 4)
		{
			Copy(&ret->DnsServer, a->Data, 4);

			if (a->Size >= 8)
			{
				Copy(&ret->DnsServer2, ((UCHAR *)a->Data) + 4, 4);
			}
		}

		// WINS server
		a = GetDhcpOption(o, DHCP_ID_WINS_ADDR);
		if (a != NULL && a->Size >= 4)
		{
			Copy(&ret->WinsServer, a->Data, 4);

			if (a->Size >= 8)
			{
				Copy(&ret->WinsServer2, ((UCHAR *)a->Data) + 4, 4);
			}
		}

		// Classless static routing table entries
		// RFC 3442
		a = GetDhcpOption(o, DHCP_ID_CLASSLESS_ROUTE);
		if (a != NULL)
		{
			DhcpParseClasslessRouteData(&ret->ClasslessRoute, a->Data, a->Size);
		}
		// Microsoft Extension
		a = GetDhcpOption(o, DHCP_ID_MS_CLASSLESS_ROUTE);
		if (a != NULL)
		{
			DhcpParseClasslessRouteData(&ret->ClasslessRoute, a->Data, a->Size);
		}

		break;
	}

	// Release the list
	FreeDhcpOptions(o);

	return ret;
}