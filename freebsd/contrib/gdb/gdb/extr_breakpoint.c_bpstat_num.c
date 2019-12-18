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
struct breakpoint {int number; } ;
typedef  TYPE_1__* bpstat ;
struct TYPE_3__ {struct TYPE_3__* next; struct breakpoint* breakpoint_at; } ;

/* Variables and functions */

int
bpstat_num (bpstat *bsp)
{
  struct breakpoint *b;

  if ((*bsp) == NULL)
    return 0;			/* No more breakpoint values */
  else
    {
      b = (*bsp)->breakpoint_at;
      *bsp = (*bsp)->next;
      if (b == NULL)
	return -1;		/* breakpoint that's been deleted since */
      else
	return b->number;	/* We have its number */
    }
}