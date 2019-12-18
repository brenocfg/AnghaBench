#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ Value_t ;

/* Variables and functions */
 int maxrhs ; 
 int nitems ; 
 scalar_t__* ritem ; 

__attribute__((used)) static void
set_maxrhs(void)
{
    Value_t *itemp;
    Value_t *item_end;
    int length;
    int max;

    length = 0;
    max = 0;
    item_end = ritem + nitems;
    for (itemp = ritem; itemp < item_end; itemp++)
    {
	if (*itemp >= 0)
	{
	    length++;
	}
	else
	{
	    if (length > max)
		max = length;
	    length = 0;
	}
    }

    maxrhs = max;
}