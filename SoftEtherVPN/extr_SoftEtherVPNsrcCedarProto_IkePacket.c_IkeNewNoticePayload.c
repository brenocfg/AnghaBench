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
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  ProtocolId; void* Spi; void* MessageData; int /*<<< orphan*/  MessageType; } ;
struct TYPE_7__ {TYPE_1__ Notice; } ;
struct TYPE_8__ {TYPE_2__ Payload; } ;
typedef  TYPE_3__ IKE_PACKET_PAYLOAD ;

/* Variables and functions */
 int /*<<< orphan*/  IKE_PAYLOAD_NOTICE ; 
 TYPE_3__* IkeNewPayload (int /*<<< orphan*/ ) ; 
 void* MemToBuf (void*,scalar_t__) ; 

IKE_PACKET_PAYLOAD *IkeNewNoticePayload(UCHAR protocol_id, USHORT message_type,
										void *spi, UINT spi_size,
										void *message, UINT message_size)
{
	IKE_PACKET_PAYLOAD *p;
	if (spi == NULL && spi_size != 0)
	{
		return NULL;
	}
	if (message == NULL && message_size != 0)
	{
		return NULL;
	}

	p = IkeNewPayload(IKE_PAYLOAD_NOTICE);
	p->Payload.Notice.MessageType = message_type;
	p->Payload.Notice.MessageData = MemToBuf(message, message_size);
	p->Payload.Notice.Spi = MemToBuf(spi, spi_size);
	p->Payload.Notice.ProtocolId = protocol_id;

	return p;
}