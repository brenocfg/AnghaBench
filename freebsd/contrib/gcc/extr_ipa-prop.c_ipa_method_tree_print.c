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
typedef  int /*<<< orphan*/  tree ;
struct cgraph_node {struct cgraph_node* next; } ;
struct TYPE_2__ {char* (* decl_printable_name ) (int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ PARM_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 char* cgraph_node_name (struct cgraph_node*) ; 
 struct cgraph_node* cgraph_nodes ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int ipa_method_formal_count (struct cgraph_node*) ; 
 int /*<<< orphan*/  ipa_method_get_tree (struct cgraph_node*,int) ; 
 TYPE_1__ lang_hooks ; 
 char* stub1 (int /*<<< orphan*/ ,int) ; 
 char* stub2 (int /*<<< orphan*/ ,int) ; 

void
ipa_method_tree_print (FILE * f)
{
  int i, count;
  tree temp;
  struct cgraph_node *node;

  fprintf (f, "\nPARAM TREE MAP PRINT\n");
  for (node = cgraph_nodes; node; node = node->next)
    {
      fprintf (f, "method  %s Trees :: \n", cgraph_node_name (node));
      count = ipa_method_formal_count (node);
      for (i = 0; i < count; i++)
	{
	  temp = ipa_method_get_tree (node, i);
	  if (TREE_CODE (temp) == PARM_DECL)
	    fprintf (f, "  param [%d] : %s\n", i,
		     (*lang_hooks.decl_printable_name) (temp, 2));
	}

    }
}