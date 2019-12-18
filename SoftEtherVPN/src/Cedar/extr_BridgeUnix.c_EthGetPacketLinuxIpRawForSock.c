#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_18__ {scalar_t__ Checksum; } ;
typedef  TYPE_3__ UDP_HEADER ;
typedef  int UCHAR ;
struct TYPE_22__ {int* RawIP_TmpBuffer; int* RawIpYourMacAddr; int* RawIpMyMacAddr; int MyPhysicalIPForce; int MyPhysicalIP; int /*<<< orphan*/  YourIP; int /*<<< orphan*/  RawIP_TmpBufferSize; } ;
struct TYPE_21__ {scalar_t__ Type; scalar_t__ Protocol; void* Checksum; void* SrcIP; void* DstIP; } ;
struct TYPE_17__ {TYPE_6__* ICMPHeader; TYPE_3__* UDPHeader; int /*<<< orphan*/ * TCPHeader; } ;
struct TYPE_16__ {TYPE_6__* IPv4Header; } ;
struct TYPE_20__ {scalar_t__ TypeL3; scalar_t__ TypeL4; int PacketSize; int PayloadSize; scalar_t__ PacketData; TYPE_2__ L4; TYPE_1__ L3; } ;
struct TYPE_19__ {scalar_t__ IgnoreRecvErr; } ;
typedef  int /*<<< orphan*/  TCP_HEADER ;
typedef  TYPE_4__ SOCK ;
typedef  TYPE_5__ PKT ;
typedef  TYPE_6__ IPV4_HEADER ;
typedef  int IP ;
typedef  TYPE_6__ ICMP_HEADER ;
typedef  int /*<<< orphan*/  ICMP_ECHO ;
typedef  TYPE_8__ ETH ;

/* Variables and functions */
 scalar_t__ CmpIpAddr (int*,int*) ; 
 int /*<<< orphan*/  Copy (int*,int*,int) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  FreePacket (TYPE_5__*) ; 
 int GetIpHeaderSize (int*,int) ; 
 scalar_t__ ICMP_TYPE_DESTINATION_UNREACHABLE ; 
 scalar_t__ ICMP_TYPE_ECHO_REQUEST ; 
 scalar_t__ ICMP_TYPE_TIME_EXCEEDED ; 
 int INFINITE ; 
 void* IPToUINT (int /*<<< orphan*/ *) ; 
 int IPV4_GET_HEADER_LEN (TYPE_6__*) ; 
 scalar_t__ IP_PROTO_ICMPV4 ; 
 void* IpChecksum (TYPE_6__*,int) ; 
 scalar_t__ IsHostIPAddress4 (int*) ; 
 scalar_t__ IsIPMyHost (int*) ; 
 int IsLocalHostIP (int*) ; 
 int IsZeroIP (int*) ; 
 scalar_t__ L3_IPV4 ; 
 scalar_t__ L4_FRAGMENT ; 
 scalar_t__ L4_ICMPV4 ; 
 scalar_t__ L4_TCP ; 
 scalar_t__ L4_UDP ; 
 int* Malloc (int) ; 
 TYPE_5__* ParsePacket (int*,int) ; 
 int RecvFrom (TYPE_4__*,int*,int*,int*,int /*<<< orphan*/ ) ; 
 int SOCK_LATER ; 
 int /*<<< orphan*/  UINTToIP (int*,void*) ; 

UINT EthGetPacketLinuxIpRawForSock(ETH *e, void **data, SOCK *s, UINT proto)
{
	UCHAR *tmp;
	UINT r;
	IP src_addr;
	UINT src_port;
	UINT ret = INFINITE;
	UCHAR *retbuf;
	PKT *p;
	bool ok = false;
	// Validate arguments
	if (e == NULL || data == NULL)
	{
		return INFINITE;
	}

	tmp = e->RawIP_TmpBuffer;

LABEL_RETRY:
	*data = NULL;

	r = RecvFrom(s, &src_addr, &src_port, tmp, e->RawIP_TmpBufferSize);
	if (r == SOCK_LATER)
	{
		return 0;
	}

	if (r == 0)
	{
		if (s->IgnoreRecvErr)
		{
			return 0;
		}
		else
		{
			return INFINITE;
		}
	}

	ret = 14 + r;
	retbuf = Malloc(ret);
	*data = retbuf;

	Copy(retbuf, e->RawIpYourMacAddr, 6);
	Copy(retbuf + 6, e->RawIpMyMacAddr, 6);
	retbuf[12] = 0x08;
	retbuf[13] = 0x00;
	Copy(retbuf + 14, tmp, r);

	// Mangle packet
	p = ParsePacket(retbuf, ret);
	if (p != NULL)
	{
		if (p->TypeL3 == L3_IPV4)
		{
			IPV4_HEADER *ip;
			IP original_dest_ip;

			ip = p->L3.IPv4Header;

			UINTToIP(&original_dest_ip, ip->DstIP);

			if (IsZeroIP(&e->MyPhysicalIPForce) == false && CmpIpAddr(&e->MyPhysicalIPForce, &original_dest_ip) == 0 ||
				(IsIPMyHost(&original_dest_ip) && IsLocalHostIP(&original_dest_ip) == false && IsHostIPAddress4(&original_dest_ip)))
			{
				if (IsZeroIP(&e->MyPhysicalIPForce) && CmpIpAddr(&e->MyPhysicalIP, &original_dest_ip) != 0)
				{
					// Update MyPhysicalIP
					Copy(&e->MyPhysicalIP, &original_dest_ip, sizeof(IP));
//					Debug("e->MyPhysicalIP = %r\n", &e->MyPhysicalIP);
				}

				if (IsZeroIP(&e->MyPhysicalIPForce) == false)
				{
					Copy(&e->MyPhysicalIP, &e->MyPhysicalIPForce, sizeof(IP));
				}

				ip->DstIP = IPToUINT(&e->YourIP);
				ip->Checksum = 0;
				ip->Checksum = IpChecksum(ip, IPV4_GET_HEADER_LEN(ip) * 5);

				if (p->TypeL4 == L4_TCP)
				{
					TCP_HEADER *tcp = p->L4.TCPHeader;
/*
					if (Endian16(tcp->SrcPort) == 80)
					{
						IP a, b;
						UINTToIP(&a, ip->SrcIP);
						UINTToIP(&b, ip->DstIP);
						Debug("%r %r %u %u\n", &a, &b, Endian16(tcp->SrcPort), Endian16(tcp->DstPort));
					}*/

					ok = true;
				}
				else if (p->TypeL4 == L4_UDP)
				{
					UDP_HEADER *udp = p->L4.UDPHeader;

					udp->Checksum = 0;

					ok = true;
				}
				else if (p->TypeL4 == L4_ICMPV4)
				{
					ICMP_HEADER *icmp = p->L4.ICMPHeader;

					if (icmp->Type == ICMP_TYPE_DESTINATION_UNREACHABLE || icmp->Type == ICMP_TYPE_TIME_EXCEEDED)
					{
						// Rewrite the Src IP of the IPv4 header of the ICMP response packet
						UINT size = p->PacketSize - ((UCHAR *)icmp - (UCHAR *)p->PacketData);
						UCHAR *data = (UCHAR *)icmp;
						IPV4_HEADER *orig_ipv4 = (IPV4_HEADER *)(((UCHAR *)data) + sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO));
						UINT orig_ipv4_size = size - (sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO));

						UINT orig_ipv4_header_size = GetIpHeaderSize((UCHAR *)orig_ipv4, orig_ipv4_size);

						if (orig_ipv4_header_size >= sizeof(IPV4_HEADER) && orig_ipv4_size >= orig_ipv4_header_size)
						{
							if (orig_ipv4->Protocol == IP_PROTO_ICMPV4)
							{
								// Search the inner ICMP header
								UINT inner_icmp_size = orig_ipv4_size - orig_ipv4_header_size;

								if (inner_icmp_size >= (sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO)))
								{
									ICMP_HEADER *inner_icmp = (ICMP_HEADER *)(((UCHAR *)data) +
										sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO) + orig_ipv4_header_size);

									if (inner_icmp->Type == ICMP_TYPE_ECHO_REQUEST)
									{
										ICMP_ECHO *inner_echo = (ICMP_ECHO *)(((UCHAR *)inner_icmp) + sizeof(ICMP_HEADER));

										inner_icmp->Checksum = 0;
										orig_ipv4->SrcIP = IPToUINT(&e->YourIP);
										orig_ipv4->Checksum = 0;
										orig_ipv4->Checksum = IpChecksum(orig_ipv4, orig_ipv4_header_size);

										// Rewrite the outer ICMP header
										if (true)
										{
											UCHAR *payload;
											UINT payload_size;
											ICMP_ECHO *echo;

											// Echo Response
											echo = (ICMP_ECHO *)(((UCHAR *)data) + sizeof(ICMP_HEADER));

											if (size >= (sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO)))
											{
												payload = ((UCHAR *)data) + sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO);
												payload_size = size - (sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO));

												// Rewrite the header
												icmp->Checksum = 0;
												icmp->Checksum = IpChecksum(icmp, size);
											}
										}
									}
								}
							}
						}
					}

					icmp->Checksum = 0;
					icmp->Checksum = IpChecksum(icmp, p->PayloadSize);

					ok = true;
				}
				else if (p->TypeL4 == L4_FRAGMENT)
				{
					ok = true;
				}
			}
		}

		FreePacket(p);
	}

	if (ok == false)
	{
		Free(*data);
		*data = NULL;

		goto LABEL_RETRY;
	}

	return ret;
}