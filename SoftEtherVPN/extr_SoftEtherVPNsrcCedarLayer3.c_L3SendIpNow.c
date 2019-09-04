#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  MacAddress; } ;
struct TYPE_15__ {int /*<<< orphan*/  MacAddress; } ;
struct TYPE_14__ {TYPE_3__* Packet; } ;
struct TYPE_12__ {int /*<<< orphan*/  PointerL3; } ;
struct TYPE_13__ {scalar_t__ PacketSize; TYPE_2__ L3; TYPE_1__* MacHeader; } ;
struct TYPE_11__ {int /*<<< orphan*/  Protocol; } ;
typedef  int /*<<< orphan*/  MAC_HEADER ;
typedef  TYPE_4__ L3PACKET ;
typedef  TYPE_5__ L3IF ;
typedef  TYPE_6__ L3ARPENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L3SendL2Now (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  broadcast ; 

void L3SendIpNow(L3IF *f, L3ARPENTRY *a, L3PACKET *p)
{
	// Validate arguments
	if (f == NULL || p == NULL)
	{
		return;
	}

	L3SendL2Now(f, a != NULL ? a->MacAddress : broadcast, f->MacAddress, Endian16(p->Packet->MacHeader->Protocol),
		p->Packet->L3.PointerL3, p->Packet->PacketSize - sizeof(MAC_HEADER));
}