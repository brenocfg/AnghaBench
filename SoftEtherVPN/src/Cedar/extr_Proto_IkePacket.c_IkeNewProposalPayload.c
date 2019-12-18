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
typedef  scalar_t__ UINT ;
typedef  void* UCHAR ;
struct TYPE_7__ {int /*<<< orphan*/ * PayloadList; int /*<<< orphan*/  Spi; void* ProtocolId; void* Number; } ;
struct TYPE_6__ {TYPE_2__ Proposal; } ;
struct TYPE_8__ {TYPE_1__ Payload; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ IKE_PACKET_PAYLOAD ;

/* Variables and functions */
 int /*<<< orphan*/  IKE_PAYLOAD_PROPOSAL ; 
 TYPE_3__* IkeNewPayload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemToBuf (void*,scalar_t__) ; 

IKE_PACKET_PAYLOAD *IkeNewProposalPayload(UCHAR number, UCHAR protocol_id, void *spi, UINT spi_size, LIST *payload_list)
{
	IKE_PACKET_PAYLOAD *p;
	if (payload_list == NULL || (spi == NULL && spi_size != 0))
	{
		return NULL;
	}

	p = IkeNewPayload(IKE_PAYLOAD_PROPOSAL);
	p->Payload.Proposal.Number = number;
	p->Payload.Proposal.ProtocolId = protocol_id;
	p->Payload.Proposal.Spi = MemToBuf(spi, spi_size);
	p->Payload.Proposal.PayloadList = payload_list;

	return p;
}