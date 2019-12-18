#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  arp ;
struct TYPE_6__ {int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  HostIP; } ;
typedef  TYPE_1__ VH ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int HardwareSize; int ProtocolSize; int /*<<< orphan*/  TargetIP; int /*<<< orphan*/  TargetAddress; int /*<<< orphan*/  SrcIP; int /*<<< orphan*/  SrcAddress; void* Operation; void* ProtocolType; void* HardwareType; } ;
typedef  TYPE_2__ ARPV4_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ARP_HARDWARE_TYPE_ETHERNET ; 
 int /*<<< orphan*/  ARP_OPERATION_REQUEST ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_PROTO_ARPV4 ; 
 int /*<<< orphan*/  MAC_PROTO_IPV4 ; 
 int /*<<< orphan*/  VirtualLayer2Send (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  broadcast ; 

void VirtualArpSendRequest(VH *v, UINT dest_ip)
{
	ARPV4_HEADER arp;
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	// Build the ARP header
	arp.HardwareType = Endian16(ARP_HARDWARE_TYPE_ETHERNET);
	arp.ProtocolType = Endian16(MAC_PROTO_IPV4);
	arp.HardwareSize = 6;
	arp.ProtocolSize = 4;
	arp.Operation = Endian16(ARP_OPERATION_REQUEST);
	Copy(arp.SrcAddress, v->MacAddress, 6);
	arp.SrcIP = v->HostIP;
	Zero(&arp.TargetAddress, 6);
	arp.TargetIP = dest_ip;

	// Transmission
	VirtualLayer2Send(v, broadcast, v->MacAddress, MAC_PROTO_ARPV4, &arp, sizeof(arp));
}