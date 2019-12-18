#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  HostUniqueKey; void* NoUdpAcceleration; void* FromAdminPack; void* DisableQoS; void* RequireBridgeRoutingMode; void* RequireMonitorMode; void* ConnectionDisconnectSpan; void* HideNicInfoWindow; void* HideStatusWindow; void* AdditionalConnectionInterval; int /*<<< orphan*/  DeviceName; void* NoRoutingTracking; void* HalfConnection; void* UseCompress; void* UseEncrypt; void* MaxConnection; int /*<<< orphan*/  HubName; void* RetryInterval; void* NumRetry; int /*<<< orphan*/  CustomHttpHeader; int /*<<< orphan*/  ProxyPassword; int /*<<< orphan*/  ProxyUsername; void* ProxyPort; int /*<<< orphan*/  ProxyName; void* ProxyType; void* PortUDP; void* Port; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  AccountName; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CLIENT_OPTION ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* CfgGetBuf (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CfgGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 char* DecryptPassword (TYPE_2__*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 scalar_t__ SHA1_SIZE ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

CLIENT_OPTION *CiLoadClientOption(FOLDER *f)
{
	CLIENT_OPTION *o;
	char *s;
	BUF *b;
	// Validate arguments
	if (f == NULL)
	{
		return NULL;
	}

	o = ZeroMalloc(sizeof(CLIENT_OPTION));

	CfgGetUniStr(f, "AccountName", o->AccountName, sizeof(o->AccountName));
	CfgGetStr(f, "Hostname", o->Hostname, sizeof(o->Hostname));
	o->Port = CfgGetInt(f, "Port");
	o->PortUDP = CfgGetInt(f, "PortUDP");
	o->ProxyType = CfgGetInt(f, "ProxyType");
	CfgGetStr(f, "ProxyName", o->ProxyName, sizeof(o->ProxyName));
	o->ProxyPort = CfgGetInt(f, "ProxyPort");
	CfgGetStr(f, "ProxyUsername", o->ProxyUsername, sizeof(o->ProxyUsername));
	b = CfgGetBuf(f, "ProxyPassword");
	s = DecryptPassword(b);
	StrCpy(o->ProxyPassword, sizeof(o->ProxyPassword), s);
	Free(s);
	FreeBuf(b);
	CfgGetStr(f, "CustomHttpHeader", o->CustomHttpHeader, sizeof(o->CustomHttpHeader));
	o->NumRetry = CfgGetInt(f, "NumRetry");
	o->RetryInterval = CfgGetInt(f, "RetryInterval");
	CfgGetStr(f, "HubName", o->HubName, sizeof(o->HubName));
	o->MaxConnection = CfgGetInt(f, "MaxConnection");
	o->UseEncrypt = CfgGetBool(f, "UseEncrypt");
	o->UseCompress = CfgGetBool(f, "UseCompress");
	o->HalfConnection = CfgGetBool(f, "HalfConnection");
	o->NoRoutingTracking = CfgGetBool(f, "NoRoutingTracking");
	CfgGetStr(f, "DeviceName", o->DeviceName, sizeof(o->DeviceName));
	o->AdditionalConnectionInterval = CfgGetInt(f, "AdditionalConnectionInterval");
	o->HideStatusWindow = CfgGetBool(f, "HideStatusWindow");
	o->HideNicInfoWindow = CfgGetBool(f, "HideNicInfoWindow");
	o->ConnectionDisconnectSpan = CfgGetInt(f, "ConnectionDisconnectSpan");
	o->RequireMonitorMode = CfgGetBool(f, "RequireMonitorMode");
	o->RequireBridgeRoutingMode = CfgGetBool(f, "RequireBridgeRoutingMode");
	o->DisableQoS = CfgGetBool(f, "DisableQoS");
	o->FromAdminPack = CfgGetBool(f, "FromAdminPack");
	o->NoUdpAcceleration = CfgGetBool(f, "NoUdpAcceleration");
	
	b = CfgGetBuf(f, "HostUniqueKey");
	if (b != NULL)
	{
		if (b->Size == SHA1_SIZE)
		{
			Copy(o->HostUniqueKey, b->Buf, SHA1_SIZE);
		}

		FreeBuf(b);
	}

	return o;
}