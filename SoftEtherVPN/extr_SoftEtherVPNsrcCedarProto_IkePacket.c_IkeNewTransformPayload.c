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
typedef  void* UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/ * ValueList; void* TransformId; void* Number; } ;
struct TYPE_7__ {TYPE_1__ Transform; } ;
struct TYPE_8__ {TYPE_2__ Payload; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ IKE_PACKET_PAYLOAD ;

/* Variables and functions */
 int /*<<< orphan*/  IKE_PAYLOAD_TRANSFORM ; 
 TYPE_3__* IkeNewPayload (int /*<<< orphan*/ ) ; 

IKE_PACKET_PAYLOAD *IkeNewTransformPayload(UCHAR number, UCHAR transform_id, LIST *value_list)
{
	IKE_PACKET_PAYLOAD *p;
	if (value_list == NULL)
	{
		return NULL;
	}

	p = IkeNewPayload(IKE_PAYLOAD_TRANSFORM);
	p->Payload.Transform.Number = number;
	p->Payload.Transform.TransformId = transform_id;
	p->Payload.Transform.ValueList = value_list;

	return p;
}