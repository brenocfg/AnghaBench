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
struct TYPE_3__ {int /*<<< orphan*/  OpenVPNObfuscationMask; int /*<<< orphan*/  OpenVPNObfuscation; int /*<<< orphan*/  OpenVPNPortList; int /*<<< orphan*/  EnableSSTP; int /*<<< orphan*/  EnableOpenVPN; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ OPENVPN_SSTP_CONFIG ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutOpenVpnSstpConfig(PACK *p, OPENVPN_SSTP_CONFIG *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddBool(p, "EnableOpenVPN", t->EnableOpenVPN);
	PackAddBool(p, "EnableSSTP", t->EnableSSTP);
	PackAddStr(p, "OpenVPNPortList", t->OpenVPNPortList);
	PackAddBool(p, "OpenVPNObfuscation", t->OpenVPNObfuscation);
	PackAddStr(p, "OpenVPNObfuscationMask", t->OpenVPNObfuscationMask);
}