#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_14__ {int IcmpRawSocketOk; } ;
typedef  TYPE_1__ VH ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_17__ {int Size; scalar_t__ Buf; } ;
struct TYPE_16__ {scalar_t__ Type; scalar_t__ TimeToLive; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  SrcIP; void* Checksum; int /*<<< orphan*/  TotalLength; } ;
struct TYPE_15__ {int DisconnectNow; int /*<<< orphan*/  SrcIp; TYPE_11__* UdpRecvQueue; } ;
struct TYPE_13__ {scalar_t__ num_item; } ;
typedef  TYPE_2__ NAT_ENTRY ;
typedef  TYPE_3__ IPV4_HEADER ;
typedef  TYPE_3__ ICMP_HEADER ;
typedef  int /*<<< orphan*/  ICMP_ECHO ;
typedef  TYPE_5__ BLOCK ;

/* Variables and functions */
 int Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBlock (TYPE_5__*) ; 
 int GetIpHeaderSize (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* GetNext (TYPE_11__*) ; 
 scalar_t__ ICMP_TYPE_DESTINATION_UNREACHABLE ; 
 scalar_t__ ICMP_TYPE_TIME_EXCEEDED ; 
 void* IpChecksum (TYPE_3__*,int) ; 
 int /*<<< orphan*/  MAX (scalar_t__,int) ; 
 int /*<<< orphan*/  SendIpEx (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void PollingNatIcmp(VH *v, NAT_ENTRY *n)
{
	// Validate arguments
	if (v == NULL || n == NULL)
	{
		return;
	}

	// Process if there are any packets in the receive queue
	if (n->UdpRecvQueue->num_item != 0)
	{
		BLOCK *block;

		// Send all ICMP packets to the virtual network
		while (block = GetNext(n->UdpRecvQueue))
		{
			// Rewrite the destination IP address of the returned packet to the IP address of the client
			UCHAR *data;
			UINT size;

			data = (UCHAR *)block->Buf;
			size = block->Size;

			if (size >= sizeof(IPV4_HEADER))
			{
				IPV4_HEADER *ipv4 = (IPV4_HEADER *)data;
				UINT ipv4_header_size = GetIpHeaderSize((UCHAR *)ipv4, size);

				if (ipv4_header_size >= sizeof(IPV4_HEADER) && (Endian16(ipv4->TotalLength) >= ipv4_header_size))
				{
					UCHAR *ipv4_payload = data + ipv4_header_size;
					UINT ipv4_payload_size = Endian16(ipv4->TotalLength) - ipv4_header_size;

					if (ipv4_payload_size >= sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO))
					{
						ICMP_HEADER *icmp = (ICMP_HEADER *)(data + ipv4_header_size);
						UINT icmp_size = ipv4_payload_size;

						if (icmp->Type == ICMP_TYPE_DESTINATION_UNREACHABLE || icmp->Type == ICMP_TYPE_TIME_EXCEEDED)
						{
							// Rewrite the Src IP of the IPv4 header of the ICMP response packet
							if (icmp_size >= (sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO) + sizeof(IPV4_HEADER)))
							{
								IPV4_HEADER *orig_ipv4 = (IPV4_HEADER *)(data + ipv4_header_size + sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO));
								UINT orig_ipv4_size = icmp_size - (sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO));

								UINT orig_ipv4_header_size = GetIpHeaderSize((UCHAR *)orig_ipv4, orig_ipv4_size);

								if (orig_ipv4_header_size >= sizeof(IPV4_HEADER))
								{
									orig_ipv4->SrcIP = n->SrcIp;
									orig_ipv4->Checksum = 0;
									orig_ipv4->Checksum = IpChecksum(orig_ipv4, orig_ipv4_header_size);
								}
							}
						}

						// Recalculate the checksum of ICMP
						icmp->Checksum = IpChecksum(icmp, icmp_size);

						SendIpEx(v, n->SrcIp, ipv4->SrcIP, ipv4->Protocol, ipv4_payload, ipv4_payload_size,
							MAX(ipv4->TimeToLive - 1, 1));
					}
				}
			}

			FreeBlock(block);
		}

		if (v->IcmpRawSocketOk == false)
		{
			// Release the NAT entry as soon as the results is received in the case of using ICMP API
			n->DisconnectNow = true;
		}
	}
}