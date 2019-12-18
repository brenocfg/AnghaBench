#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_7__ {struct TYPE_7__* Next; TYPE_1__* Object; } ;
struct TYPE_6__ {int /*<<< orphan*/  Address; } ;
typedef  TYPE_1__ TRACKING_OBJECT ;
typedef  TYPE_2__ TRACKING_LIST ;

/* Variables and functions */
 TYPE_2__* OSMemoryAlloc (int) ; 
 size_t TRACKING_HASH (int /*<<< orphan*/ ) ; 
 TYPE_2__** hashlist ; 

void InsertTrackingList(TRACKING_OBJECT *o)
{
	UINT i;
	TRACKING_LIST *t;
	// Validate arguments
	if (o == NULL)
	{
		return;
	}

	t = OSMemoryAlloc(sizeof(TRACKING_LIST));
	t->Object = o;
	t->Next = NULL;

	i = TRACKING_HASH(o->Address);

	if (hashlist[i] == NULL)
	{
		hashlist[i] = t;
	}
	else
	{
		TRACKING_LIST *tt = hashlist[i];
		while (true)
		{
			if (tt->Next == NULL)
			{
				tt->Next = t;
				break;
			}

			tt = tt->Next;
		}
	}
}