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
 int /*<<< orphan*/  CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GP_FIFO_BUDGET ; 
 int /*<<< orphan*/  GP_HUB_ARP_SEND_INTERVAL ; 
 int /*<<< orphan*/  GP_IP_TABLE_EXPIRE_TIME ; 
 int /*<<< orphan*/  GP_IP_TABLE_EXPIRE_TIME_DHCP ; 
 int /*<<< orphan*/  GP_MAC_TABLE_EXPIRE_TIME ; 
 int /*<<< orphan*/  GP_MAX_BUFFERING_PACKET_SIZE ; 
 int /*<<< orphan*/  GP_MAX_HUB_LINKS ; 
 int /*<<< orphan*/  GP_MAX_IP_TABLES ; 
 int /*<<< orphan*/  GP_MAX_MAC_TABLES ; 
 int /*<<< orphan*/  GP_MAX_SEND_SOCKET_QUEUE_NUM ; 
 int /*<<< orphan*/  GP_MAX_SEND_SOCKET_QUEUE_SIZE ; 
 int /*<<< orphan*/  GP_MAX_STORED_QUEUE_NUM ; 
 int /*<<< orphan*/  GP_MEM_FIFO_REALLOC_MEM_SIZE ; 
 int /*<<< orphan*/  GP_MIN_SEND_SOCKET_QUEUE_SIZE ; 
 int /*<<< orphan*/  GP_QUEUE_BUDGET ; 
 int /*<<< orphan*/  GP_SELECT_TIME ; 
 int /*<<< orphan*/  GP_SELECT_TIME_FOR_NAT ; 
 int /*<<< orphan*/  GP_STORM_CHECK_SPAN ; 
 int /*<<< orphan*/  GP_STORM_DISCARD_VALUE_END ; 
 int /*<<< orphan*/  GP_STORM_DISCARD_VALUE_START ; 
 int /*<<< orphan*/  MEM_FIFO_REALLOC_MEM_SIZE ; 
 int /*<<< orphan*/  SetFifoCurrentReallocMemSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiLoadGlobalParamItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SiLoadGlobalParamsCfg(FOLDER *f)
{
	SiLoadGlobalParamItem(GP_MAX_SEND_SOCKET_QUEUE_SIZE, CfgGetInt(f, "MAX_SEND_SOCKET_QUEUE_SIZE"));
	SiLoadGlobalParamItem(GP_MIN_SEND_SOCKET_QUEUE_SIZE, CfgGetInt(f, "MIN_SEND_SOCKET_QUEUE_SIZE"));
	SiLoadGlobalParamItem(GP_MAX_SEND_SOCKET_QUEUE_NUM, CfgGetInt(f, "MAX_SEND_SOCKET_QUEUE_NUM"));
	SiLoadGlobalParamItem(GP_SELECT_TIME, CfgGetInt(f, "SELECT_TIME"));
	SiLoadGlobalParamItem(GP_SELECT_TIME_FOR_NAT, CfgGetInt(f, "SELECT_TIME_FOR_NAT"));
	SiLoadGlobalParamItem(GP_MAX_STORED_QUEUE_NUM, CfgGetInt(f, "MAX_STORED_QUEUE_NUM"));
	SiLoadGlobalParamItem(GP_MAX_BUFFERING_PACKET_SIZE, CfgGetInt(f, "MAX_BUFFERING_PACKET_SIZE"));
	SiLoadGlobalParamItem(GP_HUB_ARP_SEND_INTERVAL, CfgGetInt(f, "HUB_ARP_SEND_INTERVAL"));
	SiLoadGlobalParamItem(GP_MAC_TABLE_EXPIRE_TIME, CfgGetInt(f, "MAC_TABLE_EXPIRE_TIME"));
	SiLoadGlobalParamItem(GP_IP_TABLE_EXPIRE_TIME, CfgGetInt(f, "IP_TABLE_EXPIRE_TIME"));
	SiLoadGlobalParamItem(GP_IP_TABLE_EXPIRE_TIME_DHCP, CfgGetInt(f, "IP_TABLE_EXPIRE_TIME_DHCP"));
	SiLoadGlobalParamItem(GP_STORM_CHECK_SPAN, CfgGetInt(f, "STORM_CHECK_SPAN"));
	SiLoadGlobalParamItem(GP_STORM_DISCARD_VALUE_START, CfgGetInt(f, "STORM_DISCARD_VALUE_START"));
	SiLoadGlobalParamItem(GP_STORM_DISCARD_VALUE_END, CfgGetInt(f, "STORM_DISCARD_VALUE_END"));
	SiLoadGlobalParamItem(GP_MAX_MAC_TABLES, CfgGetInt(f, "MAX_MAC_TABLES"));
	SiLoadGlobalParamItem(GP_MAX_IP_TABLES, CfgGetInt(f, "MAX_IP_TABLES"));
	SiLoadGlobalParamItem(GP_MAX_HUB_LINKS, CfgGetInt(f, "MAX_HUB_LINKS"));
	SiLoadGlobalParamItem(GP_MEM_FIFO_REALLOC_MEM_SIZE, CfgGetInt(f, "MEM_FIFO_REALLOC_MEM_SIZE"));
	SiLoadGlobalParamItem(GP_QUEUE_BUDGET, CfgGetInt(f, "QUEUE_BUDGET"));
	SiLoadGlobalParamItem(GP_FIFO_BUDGET, CfgGetInt(f, "FIFO_BUDGET"));

	SetFifoCurrentReallocMemSize(MEM_FIFO_REALLOC_MEM_SIZE);
}