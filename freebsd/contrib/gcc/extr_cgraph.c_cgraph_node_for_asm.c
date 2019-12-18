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
typedef  int /*<<< orphan*/  tree ;
struct cgraph_node {int /*<<< orphan*/  decl; struct cgraph_node* next; } ;

/* Variables and functions */
 struct cgraph_node* cgraph_nodes ; 
 scalar_t__ decl_assembler_name_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct cgraph_node *
cgraph_node_for_asm (tree asmname)
{
  struct cgraph_node *node;

  for (node = cgraph_nodes; node ; node = node->next)
    if (decl_assembler_name_equal (node->decl, asmname))
      return node;

  return NULL;
}