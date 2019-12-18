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
struct cgraph_node {int needed; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgraph_mark_reachable_node (struct cgraph_node*) ; 

void
cgraph_mark_needed_node (struct cgraph_node *node)
{
  node->needed = 1;
  cgraph_mark_reachable_node (node);
}