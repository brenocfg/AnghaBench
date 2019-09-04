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
struct TYPE_4__ {int /*<<< orphan*/ * PutPacket; int /*<<< orphan*/ * GetNextPacket; int /*<<< orphan*/ * GetCancel; int /*<<< orphan*/ * Free; int /*<<< orphan*/ * Init; } ;
typedef  int /*<<< orphan*/  PA_PUTPACKET ;
typedef  int /*<<< orphan*/  PA_INIT ;
typedef  int /*<<< orphan*/  PA_GETNEXTPACKET ;
typedef  int /*<<< orphan*/  PA_GETCANCEL ;
typedef  int /*<<< orphan*/  PA_FREE ;
typedef  TYPE_1__ PACKET_ADAPTER ;

/* Variables and functions */
 TYPE_1__* ZeroMalloc (int) ; 

PACKET_ADAPTER *NewPacketAdapter(PA_INIT *init, PA_GETCANCEL *getcancel, PA_GETNEXTPACKET *getnext,
								 PA_PUTPACKET *put, PA_FREE *free)
{
	PACKET_ADAPTER *pa;
	// Validate arguments
	if (init == NULL || getcancel == NULL || getnext == NULL || put == NULL || free == NULL)
	{
		return NULL;
	}

	pa = ZeroMalloc(sizeof(PACKET_ADAPTER));

	pa->Init = init;
	pa->Free = free;
	pa->GetCancel = getcancel;
	pa->GetNextPacket = getnext;
	pa->PutPacket = put;

	return pa;
}