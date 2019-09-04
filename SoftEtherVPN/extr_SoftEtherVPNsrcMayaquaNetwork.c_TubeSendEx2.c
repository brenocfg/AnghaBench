#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {scalar_t__ num_item; } ;
struct TYPE_7__ {int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  Event; TYPE_2__* Queue; int /*<<< orphan*/  SizeOfHeader; } ;
typedef  TYPE_1__ TUBE ;

/* Variables and functions */
 int /*<<< orphan*/  InsertQueue (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int IsTubeConnected (TYPE_1__*) ; 
 int /*<<< orphan*/  LockQueue (TYPE_2__*) ; 
 int /*<<< orphan*/  NewTubeData (void*,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (TYPE_2__*) ; 

bool TubeSendEx2(TUBE *t, void *data, UINT size, void *header, bool no_flush, UINT max_num_in_queue)
{
	// Validate arguments
	if (t == NULL || data == NULL || size == 0)
	{
		return false;
	}

	if (IsTubeConnected(t) == false)
	{
		return false;
	}

	LockQueue(t->Queue);
	{
		if (max_num_in_queue == 0 || (t->Queue->num_item <= max_num_in_queue))
		{
			InsertQueue(t->Queue, NewTubeData(data, size, header, t->SizeOfHeader));
		}
		else
		{
			no_flush = true;
		}
	}
	UnlockQueue(t->Queue);

	if (no_flush == false)
	{
		Set(t->Event);
		SetSockEvent(t->SockEvent);
	}

	return true;
}