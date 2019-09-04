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
struct TYPE_4__ {int UseEncrypt; int UseCompress; int HalfConnection; int NoRoutingTracking; int /*<<< orphan*/  HostUniqueKey; void* NoUdpAcceleration; void* FromAdminPack; void* RequireBridgeRoutingMode; void* RequireMonitorMode; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  HubName; int /*<<< orphan*/  CustomHttpHeader; int /*<<< orphan*/  ProxyPassword; int /*<<< orphan*/  ProxyUsername; int /*<<< orphan*/  ProxyName; void* DisableQoS; void* HideNicInfoWindow; void* HideStatusWindow; void* ConnectionDisconnectSpan; void* AdditionalConnectionInterval; void* MaxConnection; void* RetryInterval; void* NumRetry; void* ProxyPort; void* ProxyType; void* PortUDP; void* Port; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  AccountName; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ CLIENT_OPTION ;

/* Variables and functions */
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetData2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcClientOption(CLIENT_OPTION *c, PACK *p)
{
	// Validate arguments
	if (c == NULL || p == NULL)
	{
		return;
	}

	Zero(c, sizeof(CLIENT_OPTION));

	PackGetUniStr(p, "AccountName", c->AccountName, sizeof(c->AccountName));
	PackGetStr(p, "Hostname", c->Hostname, sizeof(c->Hostname));
	c->Port = PackGetInt(p, "Port");
	c->PortUDP = PackGetInt(p, "PortUDP");
	c->ProxyType = PackGetInt(p, "ProxyType");
	c->ProxyPort = PackGetInt(p, "ProxyPort");
	c->NumRetry = PackGetInt(p, "NumRetry");
	c->RetryInterval = PackGetInt(p, "RetryInterval");
	c->MaxConnection = PackGetInt(p, "MaxConnection");
	c->AdditionalConnectionInterval = PackGetInt(p, "AdditionalConnectionInterval");
	c->ConnectionDisconnectSpan = PackGetInt(p, "ConnectionDisconnectSpan");
	c->HideStatusWindow = PackGetBool(p, "HideStatusWindow");
	c->HideNicInfoWindow = PackGetBool(p, "HideNicInfoWindow");
	c->DisableQoS = PackGetBool(p, "DisableQoS");
	PackGetStr(p, "ProxyName", c->ProxyName, sizeof(c->ProxyName));
	PackGetStr(p, "ProxyUsername", c->ProxyUsername, sizeof(c->ProxyUsername));
	PackGetStr(p, "ProxyPassword", c->ProxyPassword, sizeof(c->ProxyPassword));
	PackGetStr(p, "CustomHttpHeader", c->CustomHttpHeader, sizeof(c->CustomHttpHeader));
	PackGetStr(p, "HubName", c->HubName, sizeof(c->HubName));
	PackGetStr(p, "DeviceName", c->DeviceName, sizeof(c->DeviceName));
	c->UseEncrypt = PackGetInt(p, "UseEncrypt") ? true : false;
	c->UseCompress = PackGetInt(p, "UseCompress") ? true : false;
	c->HalfConnection = PackGetInt(p, "HalfConnection") ? true : false;
	c->NoRoutingTracking = PackGetInt(p, "NoRoutingTracking") ? true : false;
	c->RequireMonitorMode = PackGetBool(p, "RequireMonitorMode");
	c->RequireBridgeRoutingMode = PackGetBool(p, "RequireBridgeRoutingMode");
	c->FromAdminPack = PackGetBool(p, "FromAdminPack");
	c->NoUdpAcceleration = PackGetBool(p, "NoUdpAcceleration");
	PackGetData2(p, "HostUniqueKey", c->HostUniqueKey, SHA1_SIZE);
}