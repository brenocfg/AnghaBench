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
struct TYPE_2__ {scalar_t__ finalized; } ;
struct cgraph_node {int reachable; struct cgraph_node* next_needed; int /*<<< orphan*/  decl; TYPE_1__ local; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgraph_global_info_ready ; 
 struct cgraph_node* cgraph_nodes_queue ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  notice_global_symbol (int /*<<< orphan*/ ) ; 

void
cgraph_mark_reachable_node (struct cgraph_node *node)
{
  if (!node->reachable && node->local.finalized)
    {
      notice_global_symbol (node->decl);
      node->reachable = 1;
      gcc_assert (!cgraph_global_info_ready);

      node->next_needed = cgraph_nodes_queue;
      cgraph_nodes_queue = node;
    }
}