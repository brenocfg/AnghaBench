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
struct et_node {int dfs_num_in; } ;
typedef  enum cdi_direction { ____Placeholder_cdi_direction } cdi_direction ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {struct et_node** dom; } ;

/* Variables and functions */
 scalar_t__ DOM_OK ; 
 scalar_t__* dom_computed ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

unsigned
bb_dom_dfs_in (enum cdi_direction dir, basic_block bb)
{
  struct et_node *n = bb->dom[dir];

  gcc_assert (dom_computed[dir] == DOM_OK);
  return n->dfs_num_in;
}