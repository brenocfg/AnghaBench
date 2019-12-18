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
struct TYPE_3__ {int splitchar; struct TYPE_3__* hikid; struct TYPE_3__* lokid; struct TYPE_3__* eqkid; } ;
typedef  TYPE_1__ ternary_node ;
typedef  int /*<<< orphan*/ * PTR ;

/* Variables and functions */

PTR
ternary_search (const ternary_node *p, const char *s)
{
  const ternary_node *curr;
  int diff, spchar;
  spchar = *s;
  curr = p;
  /* Loop while we haven't hit a NULL node or returned */
  while (curr)
    {
      /* Calculate the difference */
      diff = spchar - curr->splitchar;
      /* Handle the equal case */
      if (diff == 0)
	{
	  if (spchar == 0)
	    return (PTR) curr->eqkid;
	  spchar = *++s;
	  curr = curr->eqkid;
	}
      /* Handle the less than case */
      else if (diff < 0)
	curr = curr->lokid;
      /* All that's left is greater than */
      else
	curr = curr->hikid;
    }
  return NULL;
}