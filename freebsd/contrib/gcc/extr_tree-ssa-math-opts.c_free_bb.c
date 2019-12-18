#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct occurrence {TYPE_1__* bb; struct occurrence* children; struct occurrence* next; } ;
struct TYPE_2__ {int /*<<< orphan*/ * aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  occ_pool ; 
 int /*<<< orphan*/  pool_free (int /*<<< orphan*/ ,struct occurrence*) ; 

__attribute__((used)) static struct occurrence *
free_bb (struct occurrence *occ)
{
  struct occurrence *child, *next;

  /* First get the two pointers hanging off OCC.  */
  next = occ->next;
  child = occ->children;
  occ->bb->aux = NULL;
  pool_free (occ_pool, occ);

  /* Now ensure that we don't recurse unless it is necessary.  */
  if (!child)
    return next;
  else
    {
      while (next)
	next = free_bb (next);

      return child;
    }
}