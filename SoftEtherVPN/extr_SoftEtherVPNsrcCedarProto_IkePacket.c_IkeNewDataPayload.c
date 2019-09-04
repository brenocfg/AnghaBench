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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  Data; } ;
struct TYPE_7__ {TYPE_1__ GeneralData; } ;
struct TYPE_8__ {TYPE_2__ Payload; } ;
typedef  TYPE_3__ IKE_PACKET_PAYLOAD ;

/* Variables and functions */
 TYPE_3__* IkeNewPayload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemToBuf (void*,int /*<<< orphan*/ ) ; 

IKE_PACKET_PAYLOAD *IkeNewDataPayload(UCHAR payload_type, void *data, UINT size)
{
	IKE_PACKET_PAYLOAD *p;
	// Validate arguments
	if (data == NULL)
	{
		return NULL;
	}

	p = IkeNewPayload(payload_type);
	p->Payload.GeneralData.Data = MemToBuf(data, size);

	return p;
}