#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int Mandatory; int DataSize; int /*<<< orphan*/  Data; int /*<<< orphan*/  Type; } ;
struct TYPE_5__ {int IsControl; int HasLength; int HasSequence; int Ver; int /*<<< orphan*/  AvpList; scalar_t__ MessageType; } ;
typedef  TYPE_1__ L2TP_PACKET ;
typedef  TYPE_2__ L2TP_AVP ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Clone (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Endian16 (scalar_t__) ; 
 int /*<<< orphan*/  L2TP_AVP_TYPE_MESSAGE_TYPE ; 
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 void* ZeroMalloc (int) ; 

L2TP_PACKET *NewL2TPControlPacket(UINT message_type, bool is_v3)
{
	L2TP_PACKET *p = ZeroMalloc(sizeof(L2TP_PACKET));

	p->IsControl = true;
	p->HasLength = true;
	p->HasSequence = true;
	p->Ver = (is_v3 ? 3 : 2);
	p->MessageType = message_type;

	p->AvpList = NewListFast(NULL);

	if (message_type != 0)
	{
		L2TP_AVP *a;
		USHORT us;

		a = ZeroMalloc(sizeof(L2TP_AVP));

		a->Type = L2TP_AVP_TYPE_MESSAGE_TYPE;
		a->Mandatory = true;

		us = Endian16(message_type);
		a->Data = Clone(&us, sizeof(USHORT));
		a->DataSize = sizeof(USHORT);

		Add(p->AvpList, a);
	}

	return p;
}