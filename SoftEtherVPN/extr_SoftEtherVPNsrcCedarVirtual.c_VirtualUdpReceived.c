#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ HostIP; TYPE_1__* HubOption; int /*<<< orphan*/  HostMask; } ;
typedef  TYPE_2__ VH ;
typedef  scalar_t__ UINT ;
struct TYPE_14__ {int /*<<< orphan*/  DstPort; int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  PacketLength; } ;
typedef  TYPE_3__ UDP_HEADER ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_12__ {scalar_t__ DisableUserModeSecureNAT; } ;

/* Variables and functions */
 scalar_t__ Endian16 (int /*<<< orphan*/ ) ; 
 scalar_t__ Endian32 (int) ; 
 scalar_t__ GetBroadcastAddress (scalar_t__,int /*<<< orphan*/ ) ; 
 int IsInNetwork (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int NnIsActive (TYPE_2__*) ; 
 int /*<<< orphan*/  NnUdpRecvForInternet (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,void*,scalar_t__,scalar_t__) ; 
 scalar_t__ SPECIAL_UDP_PORT_LLMNR ; 
 scalar_t__ SPECIAL_UDP_PORT_NBTDGM ; 
 scalar_t__ SPECIAL_UDP_PORT_NBTNS ; 
 scalar_t__ SPECIAL_UDP_PORT_SSDP ; 
 scalar_t__ SPECIAL_UDP_PORT_WSD ; 
 scalar_t__ UDP_HEADER_SIZE ; 
 int /*<<< orphan*/  UdpRecvForBroadcast (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,void*,scalar_t__) ; 
 int /*<<< orphan*/  UdpRecvForInternet (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,void*,scalar_t__,int) ; 
 int /*<<< orphan*/  UdpRecvForMe (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,void*,scalar_t__) ; 
 int /*<<< orphan*/  UdpRecvForNetBiosBroadcast (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,void*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  UdpRecvLlmnr (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,void*,scalar_t__) ; 

void VirtualUdpReceived(VH *v, UINT src_ip, UINT dest_ip, void *data, UINT size, bool mac_broadcast, bool is_localmac, UINT max_l3_size)
{
	UDP_HEADER *udp;
	UINT packet_length;
	void *buf;
	UINT buf_size;
	UINT src_port, dest_port;
	// Validate arguments
	if (v == NULL || data == NULL)
	{
		return;
	}

	// Check the header
	udp = (UDP_HEADER *)data;
	if (size < UDP_HEADER_SIZE)
	{
		return;
	}
	packet_length = Endian16(udp->PacketLength);
	if (packet_length != size)
	{
		return;
	}
	buf = ((UCHAR *)data) + UDP_HEADER_SIZE;
	buf_size = size - UDP_HEADER_SIZE;
	src_port = Endian16(udp->SrcPort);
	dest_port = Endian16(udp->DstPort);
	// Check the port number
	if (dest_port == 0)
	{
		// Port number is invalid
		return;
	}

	// Determine whether it's broadcast packet or packet addressed to myself
	if (dest_ip == v->HostIP)
	{
		// IP packet addressed to myself has arrived
		UdpRecvForMe(v, src_ip, src_port, dest_ip, dest_port, buf, buf_size);
	}
	else if ((mac_broadcast || dest_ip == Endian32(0xE00000FC)) && dest_port == SPECIAL_UDP_PORT_LLMNR)
	{
		if (is_localmac == false)
		{
			// Packet addressed to 224.0.0.252 (LLMNR) arrives
			UdpRecvLlmnr(v, src_ip, src_port, dest_ip, dest_port, buf, buf_size);
		}
	}
	else if (mac_broadcast && (dest_port == SPECIAL_UDP_PORT_WSD || dest_port == SPECIAL_UDP_PORT_SSDP))
	{
		if (is_localmac == false)
		{
			// WS-Discovery packet arrives
			UdpRecvForInternet(v, src_ip, src_port, 0xFFFFFFFF, dest_port, buf, buf_size, false);
		}
	}
	else if (mac_broadcast && (dest_port == SPECIAL_UDP_PORT_NBTDGM || dest_port == SPECIAL_UDP_PORT_NBTNS))
	{
		if (is_localmac == false)
		{
			// NetBIOS Broadcast packet arrived
			UdpRecvForNetBiosBroadcast(v, src_ip, src_port, dest_ip, dest_port, buf, buf_size, false, false);
		}
	}
	else if (mac_broadcast || dest_ip == 0xffffffff || dest_ip == GetBroadcastAddress(v->HostIP, v->HostMask))
	{
		if (is_localmac == false)
		{
			// Broadcast packet arrived
			UdpRecvForBroadcast(v, src_ip, src_port, dest_ip, dest_port, buf, buf_size);
		}
	}
	else if (IsInNetwork(dest_ip, v->HostIP, v->HostMask) == false)
	{
		// Packets to other than local address (that is on the Internet) has been received
		if (NnIsActive(v) == false)
		{
			if (v->HubOption != NULL && v->HubOption->DisableUserModeSecureNAT)
			{
				// User-mode NAT is disabled
				return;
			}

			// User-mode NAT
			UdpRecvForInternet(v, src_ip, src_port, dest_ip, dest_port, buf, buf_size, false);
		}
		else
		{
			// Kernel-mode NAT
			NnUdpRecvForInternet(v, src_ip, src_port, dest_ip, dest_port, buf, buf_size, max_l3_size);
		}
	}
	else
	{
		// Local address has arrived. Ignore it
	}
}