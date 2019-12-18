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
struct TYPE_8__ {int Halt; int /*<<< orphan*/  Event; int /*<<< orphan*/  Cancel; int /*<<< orphan*/  PacketQueue; int /*<<< orphan*/  PacketGeneratorThread; } ;
struct TYPE_7__ {TYPE_1__* PacketAdapter; } ;
struct TYPE_6__ {TYPE_3__* Param; } ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ NULL_LAN ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void NullPaFree(SESSION *s)
{
	// Validate arguments
	NULL_LAN *n;
	BLOCK *b;
	if (s == NULL || (n = s->PacketAdapter->Param) == NULL)
	{
		return;
	}

	n->Halt = true;
	Set(n->Event);

	WaitThread(n->PacketGeneratorThread, INFINITE);
	ReleaseThread(n->PacketGeneratorThread);

	LockQueue(n->PacketQueue);
	{
		while (b = GetNext(n->PacketQueue))
		{
			FreeBlock(b);
		}
	}
	UnlockQueue(n->PacketQueue);

	ReleaseQueue(n->PacketQueue);

	ReleaseCancel(n->Cancel);

	ReleaseEvent(n->Event);

	s->PacketAdapter->Param = NULL;
	Free(n);
}