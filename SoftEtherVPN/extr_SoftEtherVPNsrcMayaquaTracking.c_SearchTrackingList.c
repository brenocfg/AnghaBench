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
typedef  scalar_t__ UINT64 ;
typedef  size_t UINT ;
struct TYPE_6__ {struct TYPE_6__* Next; TYPE_1__* Object; } ;
struct TYPE_5__ {scalar_t__ Address; } ;
typedef  TYPE_1__ TRACKING_OBJECT ;
typedef  TYPE_2__ TRACKING_LIST ;

/* Variables and functions */
 size_t TRACKING_HASH (scalar_t__) ; 
 TYPE_2__** hashlist ; 

TRACKING_OBJECT *SearchTrackingList(UINT64 Address)
{
	UINT i;
	// Validate arguments
	if (Address == 0)
	{
		return NULL;
	}

	i = TRACKING_HASH(Address);

	if (hashlist[i] != NULL)
	{
		TRACKING_LIST *tt = hashlist[i];

		while (true)
		{
			if (tt->Object->Address == Address)
			{
				return tt->Object;
			}

			tt = tt->Next;

			if (tt == NULL)
			{
				break;
			}
		}
	}

	return NULL;
}