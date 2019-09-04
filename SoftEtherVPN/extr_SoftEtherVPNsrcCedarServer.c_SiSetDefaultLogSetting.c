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
struct TYPE_4__ {int SaveSecurityLog; int SavePacketLog; int /*<<< orphan*/ * PacketLogConfig; void* PacketLogSwitchType; void* SecurityLogSwitchType; } ;
typedef  TYPE_1__ HUB_LOG ;

/* Variables and functions */
 void* LOG_SWITCH_DAY ; 
 size_t PACKET_LOG_DHCP ; 
 int /*<<< orphan*/  PACKET_LOG_HEADER ; 
 size_t PACKET_LOG_TCP_CONN ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void SiSetDefaultLogSetting(HUB_LOG *g)
{
	// Validate arguments
	if (g == NULL)
	{
		return;
	}

	Zero(g, sizeof(HUB_LOG));
	g->SaveSecurityLog = true;
	g->SecurityLogSwitchType = LOG_SWITCH_DAY;
	g->SavePacketLog = true;
	g->PacketLogSwitchType = LOG_SWITCH_DAY;
	g->PacketLogConfig[PACKET_LOG_TCP_CONN] =
		g->PacketLogConfig[PACKET_LOG_DHCP] = PACKET_LOG_HEADER;
}