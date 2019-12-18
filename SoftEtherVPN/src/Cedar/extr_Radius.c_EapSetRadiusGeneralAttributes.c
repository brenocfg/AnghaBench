#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char UINT ;
struct TYPE_6__ {char* CalledStationStr; char* ClientIpStr; char* Username; char* In_VpnProtocolState; } ;
struct TYPE_5__ {int /*<<< orphan*/  AvpList; } ;
typedef  TYPE_1__ RADIUS_PACKET ;
typedef  TYPE_2__ EAP_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* CEDAR_SERVER_STR ; 
 char Endian32 (int) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  NewRadiusAvp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  RADIUS_ATTRIBUTE_CALLED_STATION_ID ; 
 int /*<<< orphan*/  RADIUS_ATTRIBUTE_CALLING_STATION_ID ; 
 int /*<<< orphan*/  RADIUS_ATTRIBUTE_FRAMED_PROTOCOL ; 
 int /*<<< orphan*/  RADIUS_ATTRIBUTE_NAS_ID ; 
 int /*<<< orphan*/  RADIUS_ATTRIBUTE_NAS_PORT_TYPE ; 
 int /*<<< orphan*/  RADIUS_ATTRIBUTE_PROXY_STATE ; 
 int /*<<< orphan*/  RADIUS_ATTRIBUTE_SERVICE_TYPE ; 
 int /*<<< orphan*/  RADIUS_ATTRIBUTE_TUNNEL_CLIENT_ENDPOINT ; 
 int /*<<< orphan*/  RADIUS_ATTRIBUTE_USER_NAME ; 
 int /*<<< orphan*/  RADIUS_ATTRIBUTE_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  RADIUS_MS_NETWORK_ACCESS_SERVER_TYPE ; 
 int /*<<< orphan*/  RADIUS_MS_RAS_CLIENT_NAME ; 
 int /*<<< orphan*/  RADIUS_MS_RAS_CLIENT_VERSION ; 
 int /*<<< orphan*/  RADIUS_MS_RAS_CORRELATION ; 
 int /*<<< orphan*/  RADIUS_MS_RAS_VENDOR ; 
 int /*<<< orphan*/  RADIUS_MS_VERSION ; 
 int RADIUS_VENDOR_MICROSOFT ; 
 int StrLen (char*) ; 

void EapSetRadiusGeneralAttributes(RADIUS_PACKET *r, EAP_CLIENT *e)
{
	UINT ui;
	char *str;
	if (r == NULL || e == NULL)
	{
		return;
	}

	ui = Endian32(2);
	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_SERVICE_TYPE, 0, 0, &ui, sizeof(UINT)));

	ui = Endian32(1);
	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_FRAMED_PROTOCOL, 0, 0, &ui, sizeof(UINT)));

	ui = Endian32(5);
	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_NAS_PORT_TYPE, 0, 0, &ui, sizeof(UINT)));

	if (IsEmptyStr(e->CalledStationStr) == false)
	{
		Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_CALLED_STATION_ID, 0, 0, e->CalledStationStr, StrLen(e->CalledStationStr)));
	}

	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_CALLING_STATION_ID, 0, 0, e->ClientIpStr, StrLen(e->ClientIpStr)));

	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_TUNNEL_CLIENT_ENDPOINT, 0, 0, e->ClientIpStr, StrLen(e->ClientIpStr)));

	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_USER_NAME, 0, 0, e->Username, StrLen(e->Username)));

	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_NAS_ID, 0, 0, CEDAR_SERVER_STR, StrLen(CEDAR_SERVER_STR)));

	if (IsEmptyStr(e->In_VpnProtocolState) == false)
	{
		Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_PROXY_STATE, 0, 0, e->In_VpnProtocolState, StrLen(e->In_VpnProtocolState)));
	}

	ui = Endian32(2);
	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_VENDOR_SPECIFIC, RADIUS_VENDOR_MICROSOFT,
		RADIUS_MS_NETWORK_ACCESS_SERVER_TYPE, &ui, sizeof(UINT)));

	ui = Endian32(RADIUS_VENDOR_MICROSOFT);
	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_VENDOR_SPECIFIC, RADIUS_VENDOR_MICROSOFT,
		RADIUS_MS_RAS_VENDOR, &ui, sizeof(UINT)));

	str = "MSRASV5.20";
	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_VENDOR_SPECIFIC, RADIUS_VENDOR_MICROSOFT,
		RADIUS_MS_VERSION, str, StrLen(str)));

	str = "{5DC53D72-9815-4E97-AC91-339BAFEA6C48}";
	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_VENDOR_SPECIFIC, RADIUS_VENDOR_MICROSOFT,
		RADIUS_MS_RAS_CORRELATION, str, StrLen(str)));

	str = "MSRASV5.20";
	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_VENDOR_SPECIFIC, RADIUS_VENDOR_MICROSOFT,
		RADIUS_MS_RAS_CLIENT_VERSION, str, StrLen(str)));

	str = "MSRASV5.20";
	Add(r->AvpList, NewRadiusAvp(RADIUS_ATTRIBUTE_VENDOR_SPECIFIC, RADIUS_VENDOR_MICROSOFT,
		RADIUS_MS_RAS_CLIENT_NAME, str, StrLen(str)));
}