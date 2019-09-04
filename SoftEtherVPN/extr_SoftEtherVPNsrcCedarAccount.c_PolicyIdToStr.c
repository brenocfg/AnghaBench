#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UINT ;

/* Variables and functions */

char *PolicyIdToStr(UINT i)
{
	switch (i)
	{
	// Ver 2.0
	case 0:		return "Access";
	case 1:		return "DHCPFilter";
	case 2:		return "DHCPNoServer";
	case 3:		return "DHCPForce";
	case 4:		return "NoBridge";
	case 5:		return "NoRouting";
	case 6:		return "CheckMac";
	case 7:		return "CheckIP";
	case 8:		return "ArpDhcpOnly";
	case 9:		return "PrivacyFilter";
	case 10:	return "NoServer";
	case 11:	return "NoBroadcastLimiter";
	case 12:	return "MonitorPort";
	case 13:	return "MaxConnection";
	case 14:	return "TimeOut";
	case 15:	return "MaxMac";
	case 16:	return "MaxIP";
	case 17:	return "MaxUpload";
	case 18:	return "MaxDownload";
	case 19:	return "FixPassword";
	case 20:	return "MultiLogins";
	case 21:	return "NoQoS";

	// Ver 3.0
	case 22:	return "RSandRAFilter";
	case 23:	return "RAFilter";
	case 24:	return "DHCPv6Filter";
	case 25:	return "DHCPv6NoServer";
	case 26:	return "NoRoutingV6";
	case 27:	return "CheckIPv6";
	case 28:	return "NoServerV6";
	case 29:	return "MaxIPv6";
	case 30:	return "NoSavePassword";
	case 31:	return "AutoDisconnect";
	case 32:	return "FilterIPv4";
	case 33:	return "FilterIPv6";
	case 34:	return "FilterNonIP";
	case 35:	return "NoIPv6DefaultRouterInRA";
	case 36:	return "NoIPv6DefaultRouterInRAWhenIPv6";
	case 37:	return "VLanId";
	}

	return NULL;
}