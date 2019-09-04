#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {int Size; scalar_t__ Buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  PayloadList; int /*<<< orphan*/  Spi; int /*<<< orphan*/  ProtocolId; int /*<<< orphan*/  Number; } ;
struct TYPE_6__ {scalar_t__ SpiSize; int /*<<< orphan*/  ProtocolId; int /*<<< orphan*/  Number; } ;
typedef  TYPE_1__ IKE_PROPOSAL_HEADER ;
typedef  TYPE_2__ IKE_PACKET_PROPOSAL_PAYLOAD ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  IKE_PAYLOAD_TRANSFORM ; 
 int /*<<< orphan*/  IkeParsePayloadList (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemToBuf (int /*<<< orphan*/ *,scalar_t__) ; 

bool IkeParseProposalPayload(IKE_PACKET_PROPOSAL_PAYLOAD *t, BUF *b)
{
	IKE_PROPOSAL_HEADER *h;
	UCHAR *buf;
	UINT size;
	// Validate arguments
	if (t == NULL || b == NULL)
	{
		return false;
	}

	if (b->Size < sizeof(IKE_PROPOSAL_HEADER))
	{
		return false;
	}

	h = (IKE_PROPOSAL_HEADER *)b->Buf;

	t->Number = h->Number;
	t->ProtocolId = h->ProtocolId;

	buf = (UCHAR *)b->Buf;
	buf += sizeof(IKE_PROPOSAL_HEADER);
	size = b->Size - sizeof(IKE_PROPOSAL_HEADER);

	if (size < (UINT)h->SpiSize)
	{
		return false;
	}

	t->Spi = MemToBuf(buf, h->SpiSize);

	buf += h->SpiSize;
	size -= h->SpiSize;

	t->PayloadList = IkeParsePayloadList(buf, size, IKE_PAYLOAD_TRANSFORM);

	return true;
}