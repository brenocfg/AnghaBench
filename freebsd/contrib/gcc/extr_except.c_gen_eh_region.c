#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct eh_region {int type; scalar_t__ region_number; struct eh_region* next_peer; struct eh_region* inner; struct eh_region* outer; } ;
typedef  enum eh_region_type { ____Placeholder_eh_region_type } eh_region_type ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {scalar_t__ last_region_number; struct eh_region* region_tree; } ;

/* Variables and functions */
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  doing_eh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 struct eh_region* ggc_alloc_cleared (int) ; 

__attribute__((used)) static struct eh_region *
gen_eh_region (enum eh_region_type type, struct eh_region *outer)
{
  struct eh_region *new;

#ifdef ENABLE_CHECKING
  gcc_assert (doing_eh (0));
#endif

  /* Insert a new blank region as a leaf in the tree.  */
  new = ggc_alloc_cleared (sizeof (*new));
  new->type = type;
  new->outer = outer;
  if (outer)
    {
      new->next_peer = outer->inner;
      outer->inner = new;
    }
  else
    {
      new->next_peer = cfun->eh->region_tree;
      cfun->eh->region_tree = new;
    }

  new->region_number = ++cfun->eh->last_region_number;

  return new;
}