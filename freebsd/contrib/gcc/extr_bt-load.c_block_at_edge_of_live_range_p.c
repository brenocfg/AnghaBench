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
typedef  TYPE_1__* btr_user ;
typedef  TYPE_2__* btr_def ;
struct TYPE_5__ {scalar_t__ bb; TYPE_1__* uses; scalar_t__ other_btr_uses_after_use; scalar_t__ other_btr_uses_before_def; } ;
struct TYPE_4__ {scalar_t__ bb; struct TYPE_4__* next; } ;

/* Variables and functions */
 scalar_t__ BASIC_BLOCK (int) ; 

__attribute__((used)) static int
block_at_edge_of_live_range_p (int bb, btr_def def)
{
  if (def->other_btr_uses_before_def && BASIC_BLOCK (bb) == def->bb)
    return 1;
  else if (def->other_btr_uses_after_use)
    {
      btr_user user;
      for (user = def->uses; user != NULL; user = user->next)
	if (BASIC_BLOCK (bb) == user->bb)
	  return 1;
    }
  return 0;
}