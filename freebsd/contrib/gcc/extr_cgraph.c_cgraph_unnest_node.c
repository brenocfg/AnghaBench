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
struct cgraph_node {TYPE_1__* origin; struct cgraph_node* next_nested; } ;
struct TYPE_2__ {struct cgraph_node* nested; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (TYPE_1__*) ; 

void
cgraph_unnest_node (struct cgraph_node *node)
{
  struct cgraph_node **node2 = &node->origin->nested;
  gcc_assert (node->origin);

  while (*node2 != node)
    node2 = &(*node2)->next_nested;
  *node2 = node->next_nested;
  node->origin = NULL;
}