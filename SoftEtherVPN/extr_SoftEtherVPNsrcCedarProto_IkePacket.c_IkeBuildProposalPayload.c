#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h ;
struct TYPE_16__ {int /*<<< orphan*/  Size; } ;
struct TYPE_15__ {int /*<<< orphan*/  PayloadList; TYPE_3__* Spi; int /*<<< orphan*/  ProtocolId; int /*<<< orphan*/  Number; } ;
struct TYPE_14__ {int /*<<< orphan*/  SpiSize; int /*<<< orphan*/  ProtocolId; int /*<<< orphan*/  NumTransforms; int /*<<< orphan*/  Number; } ;
typedef  TYPE_1__ IKE_PROPOSAL_HEADER ;
typedef  TYPE_2__ IKE_PACKET_PROPOSAL_PAYLOAD ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 TYPE_3__* IkeBuildPayloadList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_NUM (int /*<<< orphan*/ ) ; 
 TYPE_3__* NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (TYPE_3__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  WriteBufBuf (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

BUF *IkeBuildProposalPayload(IKE_PACKET_PROPOSAL_PAYLOAD *t)
{
	IKE_PROPOSAL_HEADER h;
	BUF *ret, *b;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	Zero(&h, sizeof(h));
	h.Number = t->Number;
	h.NumTransforms = LIST_NUM(t->PayloadList);
	h.ProtocolId = t->ProtocolId;
	h.SpiSize = t->Spi->Size;

	ret = NewBuf();
	WriteBuf(ret, &h, sizeof(h));
	WriteBufBuf(ret, t->Spi);

	b = IkeBuildPayloadList(t->PayloadList);
	WriteBufBuf(ret, b);

	FreeBuf(b);

	return ret;
}