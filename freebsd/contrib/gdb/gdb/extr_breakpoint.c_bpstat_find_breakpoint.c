#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct breakpoint {int dummy; } ;
typedef  TYPE_1__* bpstat ;
struct TYPE_4__ {struct breakpoint* breakpoint_at; struct TYPE_4__* next; } ;

/* Variables and functions */

bpstat
bpstat_find_breakpoint (bpstat bsp, struct breakpoint *breakpoint)
{
  if (bsp == NULL)
    return NULL;

  for (; bsp != NULL; bsp = bsp->next)
    {
      if (bsp->breakpoint_at == breakpoint)
	return bsp;
    }
  return NULL;
}