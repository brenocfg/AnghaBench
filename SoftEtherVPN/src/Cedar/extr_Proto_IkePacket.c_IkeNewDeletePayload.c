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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/ * SpiList; int /*<<< orphan*/  ProtocolId; } ;
struct TYPE_7__ {TYPE_1__ Delete; } ;
struct TYPE_8__ {TYPE_2__ Payload; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ IKE_PACKET_PAYLOAD ;

/* Variables and functions */
 int /*<<< orphan*/  IKE_PAYLOAD_DELETE ; 
 TYPE_3__* IkeNewPayload (int /*<<< orphan*/ ) ; 

IKE_PACKET_PAYLOAD *IkeNewDeletePayload(UCHAR protocol_id, LIST *spi_list)
{
	IKE_PACKET_PAYLOAD *p;
	if (spi_list == NULL)
	{
		return NULL;
	}

	p = IkeNewPayload(IKE_PAYLOAD_DELETE);
	p->Payload.Delete.ProtocolId = protocol_id;
	p->Payload.Delete.SpiList = spi_list;

	return p;
}