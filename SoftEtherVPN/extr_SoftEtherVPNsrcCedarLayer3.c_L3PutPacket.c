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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {int /*<<< orphan*/ * CancelList; TYPE_1__* Switch; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  PKT ;
typedef  TYPE_1__ L3SW ;
typedef  TYPE_2__ L3IF ;

/* Variables and functions */
 int /*<<< orphan*/  CancelList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  L3RecvL2 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewCancelList () ; 
 int /*<<< orphan*/ * ParsePacket (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCancelList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void L3PutPacket(L3IF *f, void *data, UINT size)
{
	PKT *p;
	L3SW *s;
	if (f == NULL)
	{
		return;
	}

	s = f->Switch;

	if (data != NULL)
	{
		// Handle the next packet
		if (f->CancelList == NULL)
		{
			f->CancelList = NewCancelList();
		}

		// Packet analysis
		p = ParsePacket(data, size);

		if (p == NULL)
		{
			// Packet analysis failure
			Free(data);
		}
		else
		{
			// Packet analysis success
			Lock(s->lock);
			{
				L3RecvL2(f, p);
			}
			Unlock(s->lock);
		}
	}
	else
	{
		// Cancel for the cancellation list after all packet processing has been finished
		if (f->CancelList != NULL)
		{
			CancelList(f->CancelList);
			ReleaseCancelList(f->CancelList);
			f->CancelList = NULL;
		}
	}
}