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
struct TYPE_9__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  HostUniqueKey; scalar_t__ FromAdminPack; scalar_t__ NoUdpAcceleration; scalar_t__ DisableQoS; scalar_t__ RequireBridgeRoutingMode; scalar_t__ RequireMonitorMode; int /*<<< orphan*/  ConnectionDisconnectSpan; scalar_t__ HideNicInfoWindow; scalar_t__ HideStatusWindow; int /*<<< orphan*/  AdditionalConnectionInterval; int /*<<< orphan*/  DeviceName; scalar_t__ NoRoutingTracking; scalar_t__ HalfConnection; scalar_t__ UseCompress; scalar_t__ UseEncrypt; int /*<<< orphan*/  MaxConnection; int /*<<< orphan*/  HubName; int /*<<< orphan*/  RetryInterval; int /*<<< orphan*/  NumRetry; int /*<<< orphan*/  CustomHttpHeader; int /*<<< orphan*/  ProxyPassword; int /*<<< orphan*/  ProxyUsername; int /*<<< orphan*/  ProxyPort; int /*<<< orphan*/  ProxyName; int /*<<< orphan*/  ProxyType; int /*<<< orphan*/  PortUDP; int /*<<< orphan*/  Port; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  AccountName; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CLIENT_OPTION ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  CfgAddBuf (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  CfgAddByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* EncryptPassword (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int IsZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* MemToBuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 

void CiWriteClientOption(FOLDER *f, CLIENT_OPTION *o)
{
	BUF *b;
	// Validate arguments
	if (f == NULL || o == NULL)
	{
		return;
	}

	CfgAddUniStr(f, "AccountName", o->AccountName);
	CfgAddStr(f, "Hostname", o->Hostname);
	CfgAddInt(f, "Port", o->Port);
	CfgAddInt(f, "PortUDP", o->PortUDP);
	CfgAddInt(f, "ProxyType", o->ProxyType);
	CfgAddStr(f, "ProxyName", o->ProxyName);
	CfgAddInt(f, "ProxyPort", o->ProxyPort);
	CfgAddStr(f, "ProxyUsername", o->ProxyUsername);
	b = EncryptPassword(o->ProxyPassword);
	CfgAddByte(f, "ProxyPassword", b->Buf, b->Size);
	FreeBuf(b);
	CfgAddStr(f, "CustomHttpHeader", o->CustomHttpHeader);
	CfgAddInt(f, "NumRetry", o->NumRetry);
	CfgAddInt(f, "RetryInterval", o->RetryInterval);
	CfgAddStr(f, "HubName", o->HubName);
	CfgAddInt(f, "MaxConnection", o->MaxConnection);
	CfgAddBool(f, "UseEncrypt", o->UseEncrypt);
	CfgAddBool(f, "UseCompress", o->UseCompress);
	CfgAddBool(f, "HalfConnection", o->HalfConnection);
	CfgAddBool(f, "NoRoutingTracking", o->NoRoutingTracking);
	CfgAddStr(f, "DeviceName", o->DeviceName);
	CfgAddInt(f, "AdditionalConnectionInterval", o->AdditionalConnectionInterval);
	CfgAddBool(f, "HideStatusWindow", o->HideStatusWindow);
	CfgAddBool(f, "HideNicInfoWindow", o->HideNicInfoWindow);
	CfgAddInt(f, "ConnectionDisconnectSpan", o->ConnectionDisconnectSpan);
	CfgAddBool(f, "RequireMonitorMode", o->RequireMonitorMode);
	CfgAddBool(f, "RequireBridgeRoutingMode", o->RequireBridgeRoutingMode);
	CfgAddBool(f, "DisableQoS", o->DisableQoS);
	CfgAddBool(f, "NoUdpAcceleration", o->NoUdpAcceleration);

	if (o->FromAdminPack)
	{
		CfgAddBool(f, "FromAdminPack", o->FromAdminPack);
	}

	if (IsZero(o->HostUniqueKey, SHA1_SIZE) == false)
	{
		BUF *b = MemToBuf(o->HostUniqueKey, SHA1_SIZE);
		CfgAddBuf(f, "HostUniqueKey", b);
		FreeBuf(b);
	}
}