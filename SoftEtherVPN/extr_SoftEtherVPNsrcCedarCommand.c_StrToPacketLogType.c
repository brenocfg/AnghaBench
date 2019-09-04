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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int /*<<< orphan*/  PACKET_LOG_ARP ; 
 int /*<<< orphan*/  PACKET_LOG_DHCP ; 
 int /*<<< orphan*/  PACKET_LOG_ETHERNET ; 
 int /*<<< orphan*/  PACKET_LOG_ICMP ; 
 int /*<<< orphan*/  PACKET_LOG_IP ; 
 int /*<<< orphan*/  PACKET_LOG_TCP ; 
 int /*<<< orphan*/  PACKET_LOG_TCP_CONN ; 
 int /*<<< orphan*/  PACKET_LOG_UDP ; 
 scalar_t__ StartWith (char*,char*) ; 

UINT StrToPacketLogType(char *str)
{
	UINT ret = INFINITE;
	if (str == NULL || IsEmptyStr(str))
	{
		return INFINITE;
	}

	if (StartWith("tcpconn", str))
	{
		ret = PACKET_LOG_TCP_CONN;
	}
	else if (StartWith("tcpdata", str))
	{
		ret = PACKET_LOG_TCP;
	}
	else if (StartWith("dhcp", str))
	{
		ret = PACKET_LOG_DHCP;
	}
	else if (StartWith("udp", str))
	{
		ret = PACKET_LOG_UDP;
	}
	else if (StartWith("icmp", str))
	{
		ret = PACKET_LOG_ICMP;
	}
	else if (StartWith("ip", str))
	{
		ret = PACKET_LOG_IP;
	}
	else if (StartWith("arp", str))
	{
		ret = PACKET_LOG_ARP;
	}
	else if (StartWith("ethernet", str))
	{
		ret = PACKET_LOG_ETHERNET;
	}

	return ret;
}