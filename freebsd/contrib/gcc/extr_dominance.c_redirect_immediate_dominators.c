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
struct et_node {struct et_node* son; } ;
typedef  enum cdi_direction { ____Placeholder_cdi_direction } cdi_direction ;
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {struct et_node** dom; } ;

/* Variables and functions */
 scalar_t__ DOM_NO_FAST_QUERY ; 
 scalar_t__ DOM_OK ; 
 scalar_t__* dom_computed ; 
 int /*<<< orphan*/  et_set_father (struct et_node*,struct et_node*) ; 
 int /*<<< orphan*/  et_split (struct et_node*) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 

void
redirect_immediate_dominators (enum cdi_direction dir, basic_block bb,
			       basic_block to)
{
  struct et_node *bb_node = bb->dom[dir], *to_node = to->dom[dir], *son;

  gcc_assert (dom_computed[dir]);

  if (!bb_node->son)
    return;

  while (bb_node->son)
    {
      son = bb_node->son;

      et_split (son);
      et_set_father (son, to_node);
    }

  if (dom_computed[dir] == DOM_OK)
    dom_computed[dir] = DOM_NO_FAST_QUERY;
}