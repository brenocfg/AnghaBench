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
struct TYPE_4__ {int /*<<< orphan*/  OpenVPNObfuscationMask; void* OpenVPNObfuscation; int /*<<< orphan*/  OpenVPNPortList; void* EnableSSTP; void* EnableOpenVPN; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ OPENVPN_SSTP_CONFIG ;

/* Variables and functions */
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InOpenVpnSstpConfig(OPENVPN_SSTP_CONFIG *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(OPENVPN_SSTP_CONFIG));

	t->EnableOpenVPN = PackGetBool(p, "EnableOpenVPN");
	t->EnableSSTP = PackGetBool(p, "EnableSSTP");
	PackGetStr(p, "OpenVPNPortList", t->OpenVPNPortList, sizeof(t->OpenVPNPortList));
	t->OpenVPNObfuscation= PackGetBool(p, "OpenVPNObfuscation");
	PackGetStr(p, "OpenVPNObfuscationMask", t->OpenVPNObfuscationMask, sizeof(t->OpenVPNObfuscationMask));
}