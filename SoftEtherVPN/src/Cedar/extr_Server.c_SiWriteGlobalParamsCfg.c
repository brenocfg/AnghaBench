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
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIFO_BUDGET ; 
 int /*<<< orphan*/  HUB_ARP_SEND_INTERVAL ; 
 int /*<<< orphan*/  IP_TABLE_EXPIRE_TIME ; 
 int /*<<< orphan*/  IP_TABLE_EXPIRE_TIME_DHCP ; 
 int /*<<< orphan*/  MAC_TABLE_EXPIRE_TIME ; 
 int /*<<< orphan*/  MAX_BUFFERING_PACKET_SIZE ; 
 int /*<<< orphan*/  MAX_HUB_LINKS ; 
 int /*<<< orphan*/  MAX_IP_TABLES ; 
 int /*<<< orphan*/  MAX_MAC_TABLES ; 
 int /*<<< orphan*/  MAX_SEND_SOCKET_QUEUE_NUM ; 
 int /*<<< orphan*/  MAX_SEND_SOCKET_QUEUE_SIZE ; 
 int /*<<< orphan*/  MAX_STORED_QUEUE_NUM ; 
 int /*<<< orphan*/  MEM_FIFO_REALLOC_MEM_SIZE ; 
 int /*<<< orphan*/  MIN_SEND_SOCKET_QUEUE_SIZE ; 
 int /*<<< orphan*/  QUEUE_BUDGET ; 
 int /*<<< orphan*/  SELECT_TIME ; 
 int /*<<< orphan*/  SELECT_TIME_FOR_NAT ; 
 int /*<<< orphan*/  STORM_CHECK_SPAN ; 
 int /*<<< orphan*/  STORM_DISCARD_VALUE_END ; 
 int /*<<< orphan*/  STORM_DISCARD_VALUE_START ; 

void SiWriteGlobalParamsCfg(FOLDER *f)
{
	// Validate arguments
	if (f == NULL)
	{
		return;
	}

	CfgAddInt(f, "MAX_SEND_SOCKET_QUEUE_SIZE", MAX_SEND_SOCKET_QUEUE_SIZE);
	CfgAddInt(f, "MIN_SEND_SOCKET_QUEUE_SIZE", MIN_SEND_SOCKET_QUEUE_SIZE);
	CfgAddInt(f, "MAX_SEND_SOCKET_QUEUE_NUM", MAX_SEND_SOCKET_QUEUE_NUM);
	CfgAddInt(f, "SELECT_TIME", SELECT_TIME);
	CfgAddInt(f, "SELECT_TIME_FOR_NAT", SELECT_TIME_FOR_NAT);
	CfgAddInt(f, "MAX_STORED_QUEUE_NUM", MAX_STORED_QUEUE_NUM);
	CfgAddInt(f, "MAX_BUFFERING_PACKET_SIZE", MAX_BUFFERING_PACKET_SIZE);
	CfgAddInt(f, "HUB_ARP_SEND_INTERVAL", HUB_ARP_SEND_INTERVAL);
	CfgAddInt(f, "MAC_TABLE_EXPIRE_TIME", MAC_TABLE_EXPIRE_TIME);
	CfgAddInt(f, "IP_TABLE_EXPIRE_TIME", IP_TABLE_EXPIRE_TIME);
	CfgAddInt(f, "IP_TABLE_EXPIRE_TIME_DHCP", IP_TABLE_EXPIRE_TIME_DHCP);
	CfgAddInt(f, "STORM_CHECK_SPAN", STORM_CHECK_SPAN);
	CfgAddInt(f, "STORM_DISCARD_VALUE_START", STORM_DISCARD_VALUE_START);
	CfgAddInt(f, "STORM_DISCARD_VALUE_END", STORM_DISCARD_VALUE_END);
	CfgAddInt(f, "MAX_MAC_TABLES", MAX_MAC_TABLES);
	CfgAddInt(f, "MAX_IP_TABLES", MAX_IP_TABLES);
	CfgAddInt(f, "MAX_HUB_LINKS", MAX_HUB_LINKS);
	CfgAddInt(f, "MEM_FIFO_REALLOC_MEM_SIZE", MEM_FIFO_REALLOC_MEM_SIZE);
	CfgAddInt(f, "QUEUE_BUDGET", QUEUE_BUDGET);
	CfgAddInt(f, "FIFO_BUDGET", FIFO_BUDGET);
}