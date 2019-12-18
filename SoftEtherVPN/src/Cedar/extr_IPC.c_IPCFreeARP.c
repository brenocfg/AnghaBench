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
struct TYPE_4__ {int /*<<< orphan*/  PacketQueue; } ;
typedef  TYPE_1__ IPC_ARP ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ ) ; 

void IPCFreeARP(IPC_ARP *a)
{
	BLOCK *b;
	// Validate arguments
	if (a == NULL)
	{
		return;
	}

	while (true)
	{
		b = GetNext(a->PacketQueue);
		if (b == NULL)
		{
			break;
		}

		FreeBlock(b);
	}

	ReleaseQueue(a->PacketQueue);

	Free(a);
}