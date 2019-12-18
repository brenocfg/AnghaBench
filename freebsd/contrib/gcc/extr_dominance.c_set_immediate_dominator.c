#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct et_node {TYPE_1__* father; } ;
typedef  enum cdi_direction { ____Placeholder_cdi_direction } cdi_direction ;
typedef  TYPE_2__* basic_block ;
struct TYPE_6__ {struct et_node** dom; } ;
struct TYPE_5__ {TYPE_2__* data; } ;

/* Variables and functions */
 scalar_t__ DOM_NO_FAST_QUERY ; 
 scalar_t__ DOM_OK ; 
 scalar_t__* dom_computed ; 
 int /*<<< orphan*/  et_set_father (struct et_node*,struct et_node*) ; 
 int /*<<< orphan*/  et_split (struct et_node*) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 

inline void
set_immediate_dominator (enum cdi_direction dir, basic_block bb,
			 basic_block dominated_by)
{
  struct et_node *node = bb->dom[dir];

  gcc_assert (dom_computed[dir]);

  if (node->father)
    {
      if (node->father->data == dominated_by)
	return;
      et_split (node);
    }

  if (dominated_by)
    et_set_father (node, dominated_by->dom[dir]);

  if (dom_computed[dir] == DOM_OK)
    dom_computed[dir] = DOM_NO_FAST_QUERY;
}