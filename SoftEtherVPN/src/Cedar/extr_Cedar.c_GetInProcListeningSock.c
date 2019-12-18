#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  ListenerList; } ;
struct TYPE_8__ {scalar_t__ Protocol; int /*<<< orphan*/  lock; TYPE_1__* Sock; } ;
struct TYPE_7__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ LISTENER ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 scalar_t__ LISTENER_INPROC ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

SOCK *GetInProcListeningSock(CEDAR *c)
{
	SOCK *s = NULL;
	// Validate arguments
	if (c == NULL)
	{
		return NULL;
	}

	LockList(c->ListenerList);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(c->ListenerList);i++)
		{
			LISTENER *r = LIST_DATA(c->ListenerList, i);

			if (r->Protocol == LISTENER_INPROC)
			{
				Lock(r->lock);
				{
					s = r->Sock;

					if (s != NULL)
					{
						AddRef(s->ref);
					}
				}
				Unlock(r->lock);
				break;
			}
		}
	}
	UnlockList(c->ListenerList);

	return s;
}