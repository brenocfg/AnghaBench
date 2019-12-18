#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  RecvQueue; int /*<<< orphan*/  SendQueue; } ;
typedef  int /*<<< orphan*/  PKT ;
typedef  TYPE_1__ NATIVE_NAT ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreePacketWithData (int /*<<< orphan*/ *) ; 
 void* GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 

void NnClearQueue(NATIVE_NAT *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	LockQueue(t->SendQueue);
	{
		while (true)
		{
			BLOCK *b = GetNext(t->SendQueue);

			if (b == NULL)
			{
				break;
			}

			FreeBlock(b);
		}
	}
	UnlockQueue(t->SendQueue);

	LockQueue(t->RecvQueue);
	{
		while (true)
		{
			PKT *p = GetNext(t->RecvQueue);

			if (p == NULL)
			{
				break;
			}

			FreePacketWithData(p);
		}
	}
	UnlockQueue(t->RecvQueue);
}