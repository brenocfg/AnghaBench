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
struct tree_opt_pass {struct tree_opt_pass* next; scalar_t__ sub; } ;
struct cgraph_node {int /*<<< orphan*/ * decl; scalar_t__ analyzed; struct cgraph_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  CDI_POST_DOMINATORS ; 
 int /*<<< orphan*/  DECL_STRUCT_FUNCTION (int /*<<< orphan*/ *) ; 
 struct cgraph_node* cgraph_nodes ; 
 int /*<<< orphan*/ * current_function_decl ; 
 scalar_t__ execute_one_pass (struct tree_opt_pass*) ; 
 int /*<<< orphan*/  execute_pass_list (scalar_t__) ; 
 int /*<<< orphan*/  free_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ggc_collect () ; 
 int /*<<< orphan*/  pop_cfun () ; 
 int /*<<< orphan*/  push_cfun (int /*<<< orphan*/ ) ; 

void
execute_ipa_pass_list (struct tree_opt_pass *pass)
{
  do
    {
      if (execute_one_pass (pass) && pass->sub)
	{
	  struct cgraph_node *node;
	  for (node = cgraph_nodes; node; node = node->next)
	    if (node->analyzed)
	      {
		push_cfun (DECL_STRUCT_FUNCTION (node->decl));
		current_function_decl = node->decl;
		execute_pass_list (pass->sub);
		free_dominance_info (CDI_DOMINATORS);
		free_dominance_info (CDI_POST_DOMINATORS);
		current_function_decl = NULL;
		pop_cfun ();
		ggc_collect ();
	      }
	}
      pass = pass->next;
    }
  while (pass);
}