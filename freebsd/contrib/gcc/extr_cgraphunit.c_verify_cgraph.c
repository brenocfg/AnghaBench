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
struct cgraph_node {struct cgraph_node* next; } ;

/* Variables and functions */
 struct cgraph_node* cgraph_nodes ; 
 scalar_t__ errorcount ; 
 scalar_t__ sorrycount ; 
 int /*<<< orphan*/  verify_cgraph_node (struct cgraph_node*) ; 

void
verify_cgraph (void)
{
  struct cgraph_node *node;

  if (sorrycount || errorcount)
    return;

  for (node = cgraph_nodes; node; node = node->next)
    verify_cgraph_node (node);
}