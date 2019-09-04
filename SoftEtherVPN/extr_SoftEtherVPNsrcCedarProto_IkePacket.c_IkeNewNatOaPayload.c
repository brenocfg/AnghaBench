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
struct TYPE_6__ {int /*<<< orphan*/  IpAddress; } ;
struct TYPE_7__ {TYPE_1__ NatOa; } ;
struct TYPE_8__ {int /*<<< orphan*/  PayloadType; TYPE_2__ Payload; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_3__ IKE_PACKET_PAYLOAD ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* IkeNewPayload (int /*<<< orphan*/ ) ; 

IKE_PACKET_PAYLOAD *IkeNewNatOaPayload(UCHAR payload_type, IP *ip)
{
	IKE_PACKET_PAYLOAD *p;
	// Validate arguments
	if (ip == NULL)
	{
		return NULL;
	}

	p = IkeNewPayload(payload_type);
	Copy(&p->Payload.NatOa.IpAddress, ip, sizeof(IP));
	p->PayloadType = payload_type;

	return p;
}