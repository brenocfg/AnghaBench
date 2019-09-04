#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {int /*<<< orphan*/  Size; void* Buf; } ;
struct TYPE_10__ {int /*<<< orphan*/  PacketQueue; } ;
struct TYPE_9__ {TYPE_1__* PacketAdapter; } ;
struct TYPE_8__ {TYPE_3__* Param; } ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ NULL_LAN ;
typedef  TYPE_4__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_4__*) ; 
 TYPE_4__* GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 

UINT NullPaGetNextPacket(SESSION *s, void **data)
{
	UINT size = 0;
	// Validate arguments
	NULL_LAN *n;
	if (s == NULL || (n = s->PacketAdapter->Param) == NULL)
	{
		return INFINITE;
	}

	LockQueue(n->PacketQueue);
	{
		BLOCK *b = GetNext(n->PacketQueue);

		if (b != NULL)
		{
			*data = b->Buf;
			size = b->Size;
			Free(b);
		}
	}
	UnlockQueue(n->PacketQueue);

	return size;
}