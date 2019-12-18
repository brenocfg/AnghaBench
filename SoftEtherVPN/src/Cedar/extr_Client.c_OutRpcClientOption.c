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
struct TYPE_3__ {int /*<<< orphan*/  HostUniqueKey; int /*<<< orphan*/  NoUdpAcceleration; int /*<<< orphan*/  FromAdminPack; int /*<<< orphan*/  DisableQoS; int /*<<< orphan*/  RequireBridgeRoutingMode; int /*<<< orphan*/  RequireMonitorMode; int /*<<< orphan*/  HideNicInfoWindow; int /*<<< orphan*/  HideStatusWindow; int /*<<< orphan*/  ConnectionDisconnectSpan; int /*<<< orphan*/  AdditionalConnectionInterval; int /*<<< orphan*/  NoRoutingTracking; int /*<<< orphan*/  HalfConnection; int /*<<< orphan*/  UseCompress; int /*<<< orphan*/  UseEncrypt; int /*<<< orphan*/  MaxConnection; int /*<<< orphan*/  RetryInterval; int /*<<< orphan*/  NumRetry; int /*<<< orphan*/  ProxyPort; int /*<<< orphan*/  ProxyType; int /*<<< orphan*/  PortUDP; int /*<<< orphan*/  Port; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  HubName; int /*<<< orphan*/  CustomHttpHeader; int /*<<< orphan*/  ProxyPassword; int /*<<< orphan*/  ProxyUsername; int /*<<< orphan*/  ProxyName; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  AccountName; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ CLIENT_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 

void OutRpcClientOption(PACK *p, CLIENT_OPTION *c)
{
	// Validate arguments
	if (c == NULL || p == NULL)
	{
		return;
	}

	PackAddUniStr(p, "AccountName", c->AccountName);
	PackAddStr(p, "Hostname", c->Hostname);
	PackAddStr(p, "ProxyName", c->ProxyName);
	PackAddStr(p, "ProxyUsername", c->ProxyUsername);
	PackAddStr(p, "ProxyPassword", c->ProxyPassword);
	PackAddStr(p, "CustomHttpHeader", c->CustomHttpHeader);
	PackAddStr(p, "HubName", c->HubName);
	PackAddStr(p, "DeviceName", c->DeviceName);
	PackAddInt(p, "Port", c->Port);
	PackAddInt(p, "PortUDP", c->PortUDP);
	PackAddInt(p, "ProxyType", c->ProxyType);
	PackAddInt(p, "ProxyPort", c->ProxyPort);
	PackAddInt(p, "NumRetry", c->NumRetry);
	PackAddInt(p, "RetryInterval", c->RetryInterval);
	PackAddInt(p, "MaxConnection", c->MaxConnection);
	PackAddBool(p, "UseEncrypt", c->UseEncrypt);
	PackAddBool(p, "UseCompress", c->UseCompress);
	PackAddBool(p, "HalfConnection", c->HalfConnection);
	PackAddBool(p, "NoRoutingTracking", c->NoRoutingTracking);
	PackAddInt(p, "AdditionalConnectionInterval", c->AdditionalConnectionInterval);
	PackAddInt(p, "ConnectionDisconnectSpan", c->ConnectionDisconnectSpan);
	PackAddBool(p, "HideStatusWindow", c->HideStatusWindow);
	PackAddBool(p, "HideNicInfoWindow", c->HideNicInfoWindow);
	PackAddBool(p, "RequireMonitorMode", c->RequireMonitorMode);
	PackAddBool(p, "RequireBridgeRoutingMode", c->RequireBridgeRoutingMode);
	PackAddBool(p, "DisableQoS", c->DisableQoS);
	PackAddBool(p, "FromAdminPack", c->FromAdminPack);
	PackAddBool(p, "NoUdpAcceleration", c->NoUdpAcceleration);
	PackAddData(p, "HostUniqueKey", c->HostUniqueKey, SHA1_SIZE);
}