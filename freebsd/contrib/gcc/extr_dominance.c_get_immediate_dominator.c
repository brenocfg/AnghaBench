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
 int /*<<< orphan*/ * dom_computed ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 

basic_block
get_immediate_dominator (enum cdi_direction dir, basic_block bb)
{
  struct et_node *node = bb->dom[dir];

  gcc_assert (dom_computed[dir]);

  if (!node->father)
    return NULL;

  return node->father->data;
}