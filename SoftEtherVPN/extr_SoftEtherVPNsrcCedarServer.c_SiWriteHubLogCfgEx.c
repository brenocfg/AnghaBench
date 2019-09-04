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
struct TYPE_3__ {int /*<<< orphan*/ * PacketLogConfig; int /*<<< orphan*/  PacketLogSwitchType; int /*<<< orphan*/  SavePacketLog; int /*<<< orphan*/  SecurityLogSwitchType; int /*<<< orphan*/  SaveSecurityLog; } ;
typedef  TYPE_1__ HUB_LOG ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 size_t PACKET_LOG_ARP ; 
 size_t PACKET_LOG_DHCP ; 
 size_t PACKET_LOG_ETHERNET ; 
 size_t PACKET_LOG_ICMP ; 
 size_t PACKET_LOG_IP ; 
 size_t PACKET_LOG_TCP ; 
 size_t PACKET_LOG_TCP_CONN ; 
 size_t PACKET_LOG_UDP ; 

void SiWriteHubLogCfgEx(FOLDER *f, HUB_LOG *g, bool el_mode)
{
	// Validate arguments
	if (f == NULL || g == NULL)
	{
		return;
	}

	if (el_mode == false)
	{
		CfgAddBool(f, "SaveSecurityLog", g->SaveSecurityLog);
		CfgAddInt(f, "SecurityLogSwitchType", g->SecurityLogSwitchType);
		CfgAddBool(f, "SavePacketLog", g->SavePacketLog);
	}

	CfgAddInt(f, "PacketLogSwitchType", g->PacketLogSwitchType);

	CfgAddInt(f, "PACKET_LOG_TCP_CONN", g->PacketLogConfig[PACKET_LOG_TCP_CONN]);
	CfgAddInt(f, "PACKET_LOG_TCP", g->PacketLogConfig[PACKET_LOG_TCP]);
	CfgAddInt(f, "PACKET_LOG_DHCP", g->PacketLogConfig[PACKET_LOG_DHCP]);
	CfgAddInt(f, "PACKET_LOG_UDP", g->PacketLogConfig[PACKET_LOG_UDP]);
	CfgAddInt(f, "PACKET_LOG_ICMP", g->PacketLogConfig[PACKET_LOG_ICMP]);
	CfgAddInt(f, "PACKET_LOG_IP", g->PacketLogConfig[PACKET_LOG_IP]);
	CfgAddInt(f, "PACKET_LOG_ARP", g->PacketLogConfig[PACKET_LOG_ARP]);
	CfgAddInt(f, "PACKET_LOG_ETHERNET", g->PacketLogConfig[PACKET_LOG_ETHERNET]);
}