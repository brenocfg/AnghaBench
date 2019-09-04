#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {char* ClientStr; char* ServerStr; char* ServerName; TYPE_3__* Cedar; TYPE_1__* FirstSock; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerBuild; int /*<<< orphan*/  ServerVer; int /*<<< orphan*/  ClientBuild; int /*<<< orphan*/  ClientVer; TYPE_4__* Session; } ;
struct TYPE_22__ {int /*<<< orphan*/  ipv6_addr; } ;
struct TYPE_21__ {int /*<<< orphan*/ * UniqueId; int /*<<< orphan*/  HubName; void* ProxyPort; int /*<<< orphan*/  ProxyIpAddress6; void* ProxyIpAddress; int /*<<< orphan*/  ProxyHostname; void* ServerPort; int /*<<< orphan*/ * ServerIpAddress6; void* ServerIpAddress; int /*<<< orphan*/  ServerHostname; void* ClientPort; int /*<<< orphan*/ * ClientIpAddress6; void* ClientIpAddress; int /*<<< orphan*/  ClientHostname; int /*<<< orphan*/  ClientOsProductId; int /*<<< orphan*/  ClientOsVer; int /*<<< orphan*/  ClientOsName; void* ServerProductBuild; void* ServerProductVer; int /*<<< orphan*/  ServerProductName; void* ClientProductBuild; void* ClientProductVer; int /*<<< orphan*/  ClientProductName; } ;
struct TYPE_20__ {char* OsProductName; char* OsVersion; } ;
struct TYPE_19__ {TYPE_2__* ClientOption; } ;
struct TYPE_18__ {int /*<<< orphan*/  UniqueId; } ;
struct TYPE_17__ {scalar_t__ ProxyType; char* ProxyName; char* HubName; } ;
struct TYPE_16__ {int /*<<< orphan*/  RemotePort; TYPE_7__ RemoteIP; int /*<<< orphan*/  LocalPort; TYPE_7__ LocalIP; } ;
typedef  TYPE_4__ SESSION ;
typedef  TYPE_5__ OS_INFO ;
typedef  TYPE_6__ NODE_INFO ;
typedef  TYPE_7__ IP ;
typedef  TYPE_8__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* Endian32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (char*) ; 
 scalar_t__ GetIP (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMachineName (int /*<<< orphan*/ ,int) ; 
 TYPE_5__* GetOsInfo () ; 
 void* IPToUINT (TYPE_7__*) ; 
 int IsIP6 (TYPE_7__*) ; 
 char* OSGetProductId () ; 
 scalar_t__ PROXY_HTTP ; 
 scalar_t__ PROXY_SOCKS ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_6__*,int) ; 

void CreateNodeInfo(NODE_INFO *info, CONNECTION *c)
{
	SESSION *s;
	OS_INFO *os;
	char *product_id;
	IP ip;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	s = c->Session;
	os = GetOsInfo();



	Zero(info, sizeof(NODE_INFO));

	// Client product name
	StrCpy(info->ClientProductName, sizeof(info->ClientProductName), c->ClientStr);
	// Client version
	info->ClientProductVer = Endian32(c->ClientVer);
	// Client build number
	info->ClientProductBuild = Endian32(c->ClientBuild);

	// Server product name
	StrCpy(info->ServerProductName, sizeof(info->ServerProductName), c->ServerStr);
	// Server version
	info->ServerProductVer = Endian32(c->ServerVer);
	// Server build number
	info->ServerProductBuild = Endian32(c->ServerBuild);

	// Client OS name
	StrCpy(info->ClientOsName, sizeof(info->ClientOsName), os->OsProductName);
	// Client OS version
	StrCpy(info->ClientOsVer, sizeof(info->ClientOsVer), os->OsVersion);
	// Client OS Product ID
	product_id = OSGetProductId();
	StrCpy(info->ClientOsProductId, sizeof(info->ClientOsProductId), product_id);
	Free(product_id);

	// Client host name
#ifndef	OS_WIN32
	GetMachineName(info->ClientHostname, sizeof(info->ClientHostname));
#else	// OS_WIN32
	if (true)
	{
		wchar_t namew[256];
		char namea[256];

		Zero(namew, sizeof(namew));
		MsGetComputerNameFullEx(namew, sizeof(namew), true);

		Zero(namea, sizeof(namea));
		UniToStr(namea, sizeof(namea), namew);

		if (IsEmptyStr(namea))
		{
			GetMachineName(namea, sizeof(namea));
		}

		StrCpy(info->ClientHostname, sizeof(info->ClientHostname), namea);

	}
#endif	// OS_WIN32
	// Client IP address
	if (IsIP6(&c->FirstSock->LocalIP) == false)
	{
		info->ClientIpAddress = IPToUINT(&c->FirstSock->LocalIP);
	}
	else
	{
		Copy(info->ClientIpAddress6, c->FirstSock->LocalIP.ipv6_addr, sizeof(info->ClientIpAddress6));
	}
	// Client port number
	info->ClientPort = Endian32(c->FirstSock->LocalPort);

	// Server host name
	StrCpy(info->ServerHostname, sizeof(info->ServerHostname), c->ServerName);
	// Server IP address
	if (GetIP(&ip, info->ServerHostname))
	{
		if (IsIP6(&ip) == false)
		{
			info->ServerIpAddress = IPToUINT(&ip);
		}
		else
		{
			Copy(info->ServerIpAddress6, ip.ipv6_addr, sizeof(info->ServerIpAddress6));
		}
	}
	// Server port number
	info->ServerPort = Endian32(c->ServerPort);

	if (s->ClientOption->ProxyType == PROXY_SOCKS || s->ClientOption->ProxyType == PROXY_HTTP)
	{
		// Proxy host name
		StrCpy(info->ProxyHostname, sizeof(info->ProxyHostname), s->ClientOption->ProxyName);

		// Proxy Server IP Address
		if (IsIP6(&c->FirstSock->RemoteIP) == false)
		{
			info->ProxyIpAddress = IPToUINT(&c->FirstSock->RemoteIP);
		}
		else
		{
			Copy(&info->ProxyIpAddress6, c->FirstSock->RemoteIP.ipv6_addr, sizeof(info->ProxyIpAddress6));
		}

		info->ProxyPort = Endian32(c->FirstSock->RemotePort);
	}

	// HUB name
	StrCpy(info->HubName, sizeof(info->HubName), s->ClientOption->HubName);

	// Unique ID
	Copy(info->UniqueId, c->Cedar->UniqueId, sizeof(info->UniqueId));
}