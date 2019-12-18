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
struct cgraph_varpool_node {int /*<<< orphan*/  decl; struct cgraph_varpool_node* next_needed; } ;

/* Variables and functions */
 struct cgraph_varpool_node* cgraph_varpool_first_unanalyzed_node ; 
 struct cgraph_varpool_node* cgraph_varpool_last_needed_node ; 
 struct cgraph_varpool_node* cgraph_varpool_nodes_queue ; 
 int /*<<< orphan*/  notice_global_symbol (int /*<<< orphan*/ ) ; 

void
cgraph_varpool_enqueue_needed_node (struct cgraph_varpool_node *node)
{
  if (cgraph_varpool_last_needed_node)
    cgraph_varpool_last_needed_node->next_needed = node;
  cgraph_varpool_last_needed_node = node;
  node->next_needed = NULL;
  if (!cgraph_varpool_nodes_queue)
    cgraph_varpool_nodes_queue = node;
  if (!cgraph_varpool_first_unanalyzed_node)
    cgraph_varpool_first_unanalyzed_node = node;
  notice_global_symbol (node->decl);
}