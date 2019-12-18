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
typedef  void* UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_7__ {int HardwareSize; int ProtocolSize; void* TargetIP; void* SrcIP; int /*<<< orphan*/  TargetAddress; int /*<<< orphan*/  SrcAddress; void* Operation; void* ProtocolType; void* HardwareType; } ;
struct TYPE_6__ {int /*<<< orphan*/ * MacAddress; } ;
typedef  TYPE_1__ L3IF ;
typedef  TYPE_2__ ARPV4_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ARP_HARDWARE_TYPE_ETHERNET ; 
 int /*<<< orphan*/  ARP_OPERATION_RESPONSE ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L3SendL2Now (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  MAC_PROTO_ARPV4 ; 
 int /*<<< orphan*/  MAC_PROTO_IPV4 ; 

void L3SendArpResponseNow(L3IF *f, UCHAR *dest_mac, UINT dest_ip, UINT src_ip)
{
	ARPV4_HEADER arp;
	// Validate arguments
	if (f == NULL || dest_mac == NULL)
	{
		return;
	}

	// Build a header
	arp.HardwareType = Endian16(ARP_HARDWARE_TYPE_ETHERNET);
	arp.ProtocolType = Endian16(MAC_PROTO_IPV4);
	arp.HardwareSize = 6;
	arp.ProtocolSize = 4;
	arp.Operation = Endian16(ARP_OPERATION_RESPONSE);
	Copy(arp.SrcAddress, f->MacAddress, 6);
	Copy(arp.TargetAddress, dest_mac, 6);
	arp.SrcIP = src_ip;
	arp.TargetIP = dest_ip;

	// Transmission
	L3SendL2Now(f, dest_mac, f->MacAddress, MAC_PROTO_ARPV4, &arp, sizeof(arp));
}