#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  beacon_str ;
typedef  int /*<<< orphan*/  arp ;
struct TYPE_7__ {int HostIP; int HostMask; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ VH ;
typedef  int UINT ;
struct TYPE_8__ {int HardwareSize; int ProtocolSize; int SrcIP; int* TargetAddress; int TargetIP; int /*<<< orphan*/  SrcAddress; void* Operation; void* ProtocolType; void* HardwareType; } ;
typedef  TYPE_2__ ARPV4_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ARP_HARDWARE_TYPE_ETHERNET ; 
 int /*<<< orphan*/  ARP_OPERATION_RESPONSE ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_PROTO_ARPV4 ; 
 int /*<<< orphan*/  MAC_PROTO_IPV4 ; 
 int /*<<< orphan*/  SendUdp (TYPE_1__*,int,int,int,int,char*,int) ; 
 int /*<<< orphan*/  VirtualLayer2Send (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  broadcast ; 

void SendBeacon(VH *v)
{
	UINT dest_ip;
	ARPV4_HEADER arp;
	static char beacon_str[] =
		"SecureNAT Virtual TCP/IP Stack Beacon";
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	// Send an UDP
	dest_ip = (v->HostIP & v->HostMask) | (~v->HostMask);
	SendUdp(v, dest_ip, 7, v->HostIP, 7, beacon_str, sizeof(beacon_str));

	// Build the ARP header
	arp.HardwareType = Endian16(ARP_HARDWARE_TYPE_ETHERNET);
	arp.ProtocolType = Endian16(MAC_PROTO_IPV4);
	arp.HardwareSize = 6;
	arp.ProtocolSize = 4;
	arp.Operation = Endian16(ARP_OPERATION_RESPONSE);
	Copy(arp.SrcAddress, v->MacAddress, 6);
	arp.SrcIP = v->HostIP;
	arp.TargetAddress[0] =
		arp.TargetAddress[1] =
		arp.TargetAddress[2] =
		arp.TargetAddress[3] =
		arp.TargetAddress[4] =
		arp.TargetAddress[5] = 0xff;
	arp.TargetIP = dest_ip;

	// Transmission
	VirtualLayer2Send(v, broadcast, v->MacAddress, MAC_PROTO_ARPV4, &arp, sizeof(arp));
}