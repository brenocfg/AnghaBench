#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ rtable; } ;
struct TYPE_4__ {scalar_t__ rtekind; } ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  TYPE_2__ Query ;

/* Variables and functions */
 scalar_t__ NIL ; 
 scalar_t__ RTE_RESULT ; 
 scalar_t__ linitial (scalar_t__) ; 
 int list_length (scalar_t__) ; 

bool
HasEmptyJoinTree(Query *query)
{
	if (query->rtable == NIL)
	{
		return true;
	}

#if PG_VERSION_NUM >= 120000
	else if (list_length(query->rtable) == 1)
	{
		RangeTblEntry *rte = (RangeTblEntry *) linitial(query->rtable);
		if (rte->rtekind == RTE_RESULT)
		{
			return true;
		}
	}
#endif

	return false;
}