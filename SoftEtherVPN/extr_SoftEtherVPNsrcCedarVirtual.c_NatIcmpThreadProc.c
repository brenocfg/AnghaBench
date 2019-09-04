#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ipv4 ;
typedef  int /*<<< orphan*/  icmp ;
typedef  int /*<<< orphan*/  echo ;
typedef  void* USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_25__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_24__ {int Timeout; int DataSize; scalar_t__ Type; scalar_t__ Code; int /*<<< orphan*/  Ttl; TYPE_4__* Data; scalar_t__ Ok; int /*<<< orphan*/  IpAddress; } ;
struct TYPE_23__ {scalar_t__ Type; scalar_t__ Code; int DstIP; void* TotalLength; void* SeqNo; void* Identifier; int /*<<< orphan*/  SrcIP; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  TimeToLive; } ;
struct TYPE_22__ {int IcmpOriginalCopySize; int IcmpTaskFinished; TYPE_2__* v; TYPE_13__* IcmpResponseBlock; TYPE_4__* IcmpOriginalCopy; TYPE_1__* IcmpQueryBlock; int /*<<< orphan*/  DestIp; } ;
struct TYPE_21__ {int /*<<< orphan*/  SockEvent; } ;
struct TYPE_20__ {int Size; int /*<<< orphan*/  Ttl; int /*<<< orphan*/ * Buf; } ;
struct TYPE_19__ {int /*<<< orphan*/  Ttl; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_3__ NAT_ENTRY ;
typedef  TYPE_4__ IPV4_HEADER ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_5__ ICMP_RESULT ;
typedef  TYPE_4__ ICMP_HEADER ;
typedef  TYPE_4__ ICMP_ECHO ;
typedef  TYPE_8__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Clone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* Endian16 (void*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_8__*) ; 
 scalar_t__ ICMP_TYPE_ECHO_REQUEST ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPV4_SET_HEADER_LEN (TYPE_4__*,int) ; 
 int /*<<< orphan*/  IPV4_SET_VERSION (TYPE_4__*,int) ; 
 int /*<<< orphan*/  IP_PROTO_ICMPV4 ; 
 TYPE_5__* IcmpApiEchoSend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IcmpApiFreeResult (TYPE_5__*) ; 
 int /*<<< orphan*/  NAT_ICMP_TIMEOUT_WITH_API ; 
 TYPE_13__* NewBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* NewBuf () ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_8__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_4__*,int) ; 

void NatIcmpThreadProc(THREAD *thread, void *param)
{
	NAT_ENTRY *n;
	ICMP_RESULT *ret = NULL;
	USHORT src_id = 0, src_seqno = 0;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	n = (NAT_ENTRY *)param;

	if (n->IcmpQueryBlock)
	{
		UCHAR *data = n->IcmpQueryBlock->Buf;
		UINT size = n->IcmpQueryBlock->Size;

		if (size >= (sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO)))
		{
			ICMP_HEADER *icmp = (ICMP_HEADER *)data;
			ICMP_ECHO *echo = (ICMP_ECHO *)(data + sizeof(ICMP_HEADER));

			if (icmp->Type == ICMP_TYPE_ECHO_REQUEST && icmp->Code == 0)
			{
				UCHAR *icmp_payload = data + sizeof(ICMP_HEADER) + sizeof(ICMP_ECHO);
				UINT icmp_payload_size = size - sizeof(ICMP_HEADER) - sizeof(ICMP_ECHO);
				IP dest_ip;

				src_id = Endian16(echo->Identifier);
				src_seqno = Endian16(echo->SeqNo);

				UINTToIP(&dest_ip, n->DestIp);

				// Send a query by using the ICMP API
				ret = IcmpApiEchoSend(&dest_ip, n->IcmpQueryBlock->Ttl,
					icmp_payload, icmp_payload_size, NAT_ICMP_TIMEOUT_WITH_API);
			}
		}
	}

	if (ret != NULL && ret->Timeout == false)
	{
		// Convert to an IPv4 + ICMP packet since the result of ICMP API was obtained
		IPV4_HEADER ipv4;
		ICMP_HEADER icmp;
		ICMP_ECHO echo;
		BUF *buf = NewBuf();

		// IPv4 header
		Zero(&ipv4, sizeof(ipv4));
		IPV4_SET_VERSION(&ipv4, 4);
		IPV4_SET_HEADER_LEN(&ipv4, sizeof(IPV4_HEADER) / 4);
		ipv4.TimeToLive = ret->Ttl;
		ipv4.Protocol = IP_PROTO_ICMPV4;
		ipv4.SrcIP = IPToUINT(&ret->IpAddress);
		ipv4.DstIP = 0x01010101;


		// ICMP header
		Zero(&icmp, sizeof(icmp));
		Zero(&echo, sizeof(echo));

		if (ret->Ok)
		{
			// Normal response
			echo.Identifier = Endian16(src_id);
			echo.SeqNo = Endian16(src_seqno);

			ipv4.TotalLength = Endian16((USHORT)(sizeof(ipv4) + sizeof(icmp) + sizeof(echo) + ret->DataSize));

			WriteBuf(buf, &ipv4, sizeof(ipv4));
			WriteBuf(buf, &icmp, sizeof(icmp));
			WriteBuf(buf, &echo, sizeof(echo));
			WriteBuf(buf, ret->Data, ret->DataSize);
		}
		else
		{
			// Error reply
			icmp.Type = ret->Type;
			icmp.Code = ret->Code;
			echo.Identifier = Endian16(src_id);
			echo.SeqNo = Endian16(src_seqno);

			ipv4.TotalLength = Endian16((USHORT)(sizeof(ipv4) + sizeof(icmp) + sizeof(echo) + n->IcmpOriginalCopySize));

			WriteBuf(buf, &ipv4, sizeof(ipv4));
			WriteBuf(buf, &icmp, sizeof(icmp));
			WriteBuf(buf, &echo, sizeof(echo));

			// Copy of the original packet to be included in the response packet
			WriteBuf(buf, n->IcmpOriginalCopy, n->IcmpOriginalCopySize);
		}

		n->IcmpResponseBlock = NewBlock(Clone(buf->Buf, buf->Size), buf->Size, 0);
		n->IcmpResponseBlock->Ttl = ret->Ttl;

		FreeBuf(buf);
	}
	IcmpApiFreeResult(ret);

	// Inform the completion of the processing
	n->IcmpTaskFinished = true;
	SetSockEvent(n->v->SockEvent);
}