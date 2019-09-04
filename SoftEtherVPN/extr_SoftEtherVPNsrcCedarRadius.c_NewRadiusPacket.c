#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  AvpList; void* PacketId; void* Code; } ;
typedef  TYPE_1__ RADIUS_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

RADIUS_PACKET *NewRadiusPacket(UCHAR code, UCHAR packet_id)
{
	RADIUS_PACKET *r = ZeroMalloc(sizeof(RADIUS_PACKET));

	r->Code = code;
	r->PacketId = packet_id;

	r->AvpList = NewListFast(NULL);

	return r;
}