#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_19__ {int Size; void* Buf; } ;
struct TYPE_18__ {int Protocol; int IsControl; int DataSize; TYPE_1__* Lcp; scalar_t__* Data; } ;
struct TYPE_17__ {int IsTerminateReceived; int /*<<< orphan*/  NextId; } ;
struct TYPE_16__ {scalar_t__ Code; int DataSize; void* Data; int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ PPP_SESSION ;
typedef  TYPE_3__ PPP_PACKET ;
typedef  TYPE_4__ BUF ;

/* Variables and functions */
 void* Clone (void*,int) ; 
 scalar_t__ Endian16 (int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_4__*) ; 
 int /*<<< orphan*/  FreePPPPacket (TYPE_3__*) ; 
 TYPE_4__* NewBuf () ; 
 void* NewPPPLCP (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* PPPRecvPacket (TYPE_2__*,int) ; 
 int PPPSendPacket (TYPE_2__*,TYPE_3__*) ; 
 int PPP_IS_SUPPORTED_PROTOCOL (int) ; 
 scalar_t__ PPP_LCP_CODE_DROP ; 
 scalar_t__ PPP_LCP_CODE_ECHO_REQUEST ; 
 scalar_t__ PPP_LCP_CODE_ECHO_RESPONSE ; 
 scalar_t__ PPP_LCP_CODE_IDENTIFICATION ; 
 scalar_t__ PPP_LCP_CODE_PROTOCOL_REJECT ; 
 scalar_t__ PPP_LCP_CODE_TERMINATE_ACK ; 
 scalar_t__ PPP_LCP_CODE_TERMINATE_REQ ; 
 scalar_t__ PPP_PROTOCOL_LCP ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 int /*<<< orphan*/  WHERE ; 
 int /*<<< orphan*/  WriteBuf (TYPE_4__*,scalar_t__*,int) ; 
 TYPE_3__* ZeroMalloc (int) ; 

PPP_PACKET *PPPRecvPacketWithLowLayerProcessing(PPP_SESSION *p, bool async)
{
	PPP_PACKET *pp = NULL;
	// Validate arguments
	if (p == NULL)
	{
		return NULL;
	}

LABEL_LOOP:
	pp = PPPRecvPacket(p, async);
	if (pp == NULL)
	{
		return NULL;
	}

	if (PPP_IS_SUPPORTED_PROTOCOL(pp->Protocol) == false)
	{
		// Unsupported algorithm
		PPP_PACKET *pp2 = ZeroMalloc(sizeof(PPP_PACKET));
		BUF *buf;
		UCHAR c;
		USHORT us;

		pp2->Protocol = PPP_PROTOCOL_LCP;
		pp2->IsControl = false;

		buf = NewBuf();

		// Code
		c = PPP_LCP_CODE_PROTOCOL_REJECT;
		WriteBuf(buf, &c, 1);

		// ID
		c = p->NextId++;
		WriteBuf(buf, &c, 1);

		// Length
		us = Endian16(pp->DataSize + 6);
		WriteBuf(buf, &us, 2);

		// Rejected Protocol
		us = Endian16(pp->Protocol);
		WriteBuf(buf, &us, 2);

		// Packet Data
		WriteBuf(buf, pp->Data, pp->DataSize);

		pp2->Data = Clone(buf->Buf, buf->Size);
		pp2->DataSize = buf->Size;

		FreePPPPacket(pp);

		FreeBuf(buf);

		if (PPPSendPacket(p, pp2) == false)
		{
			FreePPPPacket(pp2);
			return NULL;
		}

		FreePPPPacket(pp2);
		goto LABEL_LOOP;
	}

	if (pp->IsControl && pp->Protocol == PPP_PROTOCOL_LCP)
	{
		if (pp->Lcp->Code == PPP_LCP_CODE_ECHO_REQUEST)
		{
			// Immediately return the echo response to the echo request
			PPP_PACKET *pp2 = ZeroMalloc(sizeof(PPP_PACKET));

			pp2->IsControl = true;
			pp2->Protocol = PPP_PROTOCOL_LCP;
			pp2->Lcp = NewPPPLCP(PPP_LCP_CODE_ECHO_RESPONSE, pp->Lcp->Id);
			pp2->Lcp->Data = Clone(pp->Lcp->Data, pp->Lcp->DataSize);
			pp2->Lcp->DataSize = pp->Lcp->DataSize;

			FreePPPPacket(pp);

			if (PPPSendPacket(p, pp2) == false)
			{
				FreePPPPacket(pp2);
				return NULL;
			}

			FreePPPPacket(pp2);
			goto LABEL_LOOP;
		}
		else if (pp->Lcp->Code == PPP_LCP_CODE_ECHO_RESPONSE)
		{
			// Ignore the Echo response packet
			FreePPPPacket(pp);
			goto LABEL_LOOP;
		}
		else if (pp->Lcp->Code == PPP_LCP_CODE_DROP)
		{
			// Ignore the Drop packet
			FreePPPPacket(pp);
			goto LABEL_LOOP;
		}
		else if (pp->Lcp->Code == PPP_LCP_CODE_IDENTIFICATION)
		{
			// Ignore the Identification packet
			FreePPPPacket(pp);
			WHERE;
			goto LABEL_LOOP;
		}
		else if (pp->Lcp->Code == PPP_LCP_CODE_TERMINATE_REQ)
		{
			// Return the Terminate ACK If a Terminate Request has been received
			PPP_PACKET *pp2 = ZeroMalloc(sizeof(PPP_PACKET));

			pp2->IsControl = true;
			pp2->Protocol = PPP_PROTOCOL_LCP;
			pp2->Lcp = NewPPPLCP(PPP_LCP_CODE_TERMINATE_ACK, pp->Lcp->Id);
			pp2->Lcp->Data = Clone(pp->Lcp->Data, pp->Lcp->DataSize);
			pp2->Lcp->DataSize = pp->Lcp->DataSize;

			p->IsTerminateReceived = true;

			FreePPPPacket(pp);

			if (PPPSendPacket(p, pp2) == false)
			{
				FreePPPPacket(pp2);
				return NULL;
			}

			SleepThread(100);

			FreePPPPacket(pp2);
			goto LABEL_LOOP;
		}
	}

	return pp;
}