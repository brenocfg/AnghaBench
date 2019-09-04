#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  OpenVPNObfuscationMask; int /*<<< orphan*/  OpenVPNObfuscation; int /*<<< orphan*/  OpenVPNPortList; int /*<<< orphan*/  EnableOpenVPN; int /*<<< orphan*/  EnableSSTP; } ;
struct TYPE_7__ {scalar_t__ ServerType; int DisableSSTPServer; int DisableOpenVPNServer; char* OpenVpnServerUdpPorts; int /*<<< orphan*/  OpenVpnSstpConfigLock; int /*<<< orphan*/  ListenIP; int /*<<< orphan*/ * OpenVpnServerUdp; TYPE_1__* Cedar; } ;
struct TYPE_6__ {int /*<<< orphan*/  OpenVPNObfuscationMask; int /*<<< orphan*/  OpenVPNObfuscation; scalar_t__ Bridge; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ OPENVPN_SSTP_CONFIG ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NormalizeIntListStr (char*,int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  OvsApplyUdpPortList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void SiSetOpenVPNAndSSTPConfig(SERVER *s, OPENVPN_SSTP_CONFIG *c)
{
	// Validate arguments
	if (s == NULL || c == NULL)
	{
		return;
	}

	Lock(s->OpenVpnSstpConfigLock);
	{
		// Save the settings
		if (s->Cedar->Bridge || s->ServerType != SERVER_TYPE_STANDALONE)
		{
			s->DisableSSTPServer = true;
			s->DisableOpenVPNServer = true;
		}
		else
		{
			s->DisableSSTPServer = !c->EnableSSTP;
			s->DisableOpenVPNServer = !c->EnableOpenVPN;
		}

		NormalizeIntListStr(s->OpenVpnServerUdpPorts, sizeof(s->OpenVpnServerUdpPorts),
			c->OpenVPNPortList, true, ", ");

		s->Cedar->OpenVPNObfuscation = c->OpenVPNObfuscation;
		StrCpy(s->Cedar->OpenVPNObfuscationMask, sizeof(s->Cedar->OpenVPNObfuscationMask), c->OpenVPNObfuscationMask);

		// Apply the OpenVPN configuration
		if (s->OpenVpnServerUdp != NULL)
		{
			if (s->DisableOpenVPNServer)
			{
				OvsApplyUdpPortList(s->OpenVpnServerUdp, "", NULL);
			}
			else
			{
				OvsApplyUdpPortList(s->OpenVpnServerUdp, s->OpenVpnServerUdpPorts, &s->ListenIP);
			}
		}
	}
	Unlock(s->OpenVpnSstpConfigLock);
}