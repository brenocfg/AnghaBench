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
struct TYPE_4__ {int /*<<< orphan*/  NetBufferListPool; int /*<<< orphan*/  NetBufferList; } ;
typedef  TYPE_1__ PACKET_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  NdisFreeNetBufferList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisFreeNetBufferListPool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NeoFree (TYPE_1__*) ; 

void NeoFreePacketBuffer(PACKET_BUFFER *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	// Release the NET_BUFFER_LIST
	NdisFreeNetBufferList(p->NetBufferList);
	// Release the NET_BUFFER_LIST pool
	NdisFreeNetBufferListPool(p->NetBufferListPool);
	// Release the memory
	NeoFree(p);
}