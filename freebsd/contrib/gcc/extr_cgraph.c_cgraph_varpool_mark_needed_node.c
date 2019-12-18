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
struct cgraph_varpool_node {int needed; int /*<<< orphan*/  decl; scalar_t__ finalized; } ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_ASM_WRITTEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_varpool_enqueue_needed_node (struct cgraph_varpool_node*) ; 

void
cgraph_varpool_mark_needed_node (struct cgraph_varpool_node *node)
{
  if (!node->needed && node->finalized
      && !TREE_ASM_WRITTEN (node->decl))
    cgraph_varpool_enqueue_needed_node (node);
  node->needed = 1;
}