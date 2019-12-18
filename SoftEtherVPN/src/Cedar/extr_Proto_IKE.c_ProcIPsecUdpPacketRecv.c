#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_7__ {int /*<<< orphan*/  DstPort; int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  PacketLength; } ;
typedef  TYPE_1__ UDP_HEADER ;
struct TYPE_8__ {int DestPort; int Size; int SrcPort; int /*<<< orphan*/ * Data; int /*<<< orphan*/  SrcIP; int /*<<< orphan*/  DstIP; scalar_t__ Type; } ;
typedef  TYPE_2__ UDPPACKET ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {int L2TPClientPort; int /*<<< orphan*/  L2TP; int /*<<< orphan*/  L2TPClientIP; int /*<<< orphan*/  L2TPServerIP; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  TYPE_3__ IKE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int Endian16 (int /*<<< orphan*/ ) ; 
 int IPSEC_PORT_L2TP ; 
 int /*<<< orphan*/  IPsecIkeClientManageL2TPServer (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  IPsecIkeSendUdpForDebug (int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ProcL2TPPacketRecv (int /*<<< orphan*/ ,TYPE_2__*) ; 

void ProcIPsecUdpPacketRecv(IKE_SERVER *ike, IKE_CLIENT *c, UCHAR *data, UINT data_size)
{
	UDP_HEADER *u;
	UINT payload_size;
	UINT src_port, dst_port;
	UINT packet_length;
	// Validate arguments
	if (ike == NULL || c == NULL || data == NULL || data_size == 0)
	{
		return;
	}

	if (data_size <= sizeof(UDP_HEADER))
	{
		// There is no UDP header or the data is 0 bytes
		return;
	}

	// UDP header
	u = (UDP_HEADER *)data;

	packet_length = Endian16(u->PacketLength);

	if (packet_length <= sizeof(UDP_HEADER))
	{
		return;
	}

	payload_size = packet_length - sizeof(UDP_HEADER);

	if (payload_size == 0)
	{
		// No data
		return;
	}

	if (data_size < (sizeof(UDP_HEADER) + payload_size))
	{
		// Data is not followed
		return;
	}

	src_port = Endian16(u->SrcPort);
	dst_port = Endian16(u->DstPort);

	if (dst_port == IPSEC_PORT_L2TP)
	{
		UDPPACKET p;
		// A L2TP packet has been received
		IPsecIkeClientManageL2TPServer(ike, c);

		// Update Port number
		c->L2TPClientPort = src_port;

		// Pass the received packet to the L2TP server
		p.Type = 0;
		p.Data = data + sizeof(UDP_HEADER);
		p.DestPort = IPSEC_PORT_L2TP;
		Copy(&p.DstIP, &c->L2TPServerIP, sizeof(IP));
		p.Size = payload_size;
		Copy(&p.SrcIP, &c->L2TPClientIP, sizeof(IP));
		p.SrcPort = IPSEC_PORT_L2TP;

		ProcL2TPPacketRecv(c->L2TP, &p);

		//Debug("IPsec UDP Recv: %u <= %u %u\n", dst_port, src_port, p.Size);

#ifdef	RAW_DEBUG
		IPsecIkeSendUdpForDebug(IPSEC_PORT_L2TP, 1, p.Data, p.Size);
#endif	// RAW_DEBUG
	}
}