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

/* Variables and functions */
 int MAX_COST ; 

__attribute__((used)) static int
preferable (int cost_a, int regcost_a, int cost_b, int regcost_b)
{
  /* First, get rid of cases involving expressions that are entirely
     unwanted.  */
  if (cost_a != cost_b)
    {
      if (cost_a == MAX_COST)
	return 1;
      if (cost_b == MAX_COST)
	return -1;
    }

  /* Avoid extending lifetimes of hardregs.  */
  if (regcost_a != regcost_b)
    {
      if (regcost_a == MAX_COST)
	return 1;
      if (regcost_b == MAX_COST)
	return -1;
    }

  /* Normal operation costs take precedence.  */
  if (cost_a != cost_b)
    return cost_a - cost_b;
  /* Only if these are identical consider effects on register pressure.  */
  if (regcost_a != regcost_b)
    return regcost_a - regcost_b;
  return 0;
}