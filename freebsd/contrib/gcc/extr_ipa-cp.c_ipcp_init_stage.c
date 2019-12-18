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
struct cgraph_node {struct cgraph_edge* callees; struct cgraph_node* next; } ;
struct cgraph_edge {int /*<<< orphan*/  callee; struct cgraph_edge* next_callee; } ;

/* Variables and functions */
 struct cgraph_node* cgraph_nodes ; 
 int /*<<< orphan*/  ipa_callsite_compute_count (struct cgraph_edge*) ; 
 int /*<<< orphan*/  ipa_callsite_compute_param (struct cgraph_edge*) ; 
 scalar_t__ ipa_callsite_param_count (struct cgraph_edge*) ; 
 int /*<<< orphan*/  ipa_callsite_param_count_set (struct cgraph_edge*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipa_method_compute_modify (struct cgraph_node*) ; 
 int /*<<< orphan*/  ipa_method_compute_tree_map (struct cgraph_node*) ; 
 int /*<<< orphan*/  ipa_method_formal_compute_count (struct cgraph_node*) ; 
 scalar_t__ ipa_method_formal_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipa_method_formal_count_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcp_method_compute_scale (struct cgraph_node*) ; 
 int /*<<< orphan*/  ipcp_method_cval_init (struct cgraph_node*) ; 

__attribute__((used)) static void
ipcp_init_stage (void)
{
  struct cgraph_node *node;
  struct cgraph_edge *cs;

  for (node = cgraph_nodes; node; node = node->next)
    {
      ipa_method_formal_compute_count (node);
      ipa_method_compute_tree_map (node);
      ipcp_method_cval_init (node);
      ipa_method_compute_modify (node);
      ipcp_method_compute_scale (node);
    }
  for (node = cgraph_nodes; node; node = node->next)
    {
      /* building jump functions  */
      for (cs = node->callees; cs; cs = cs->next_callee)
	{
	  ipa_callsite_compute_count (cs);
	  if (ipa_callsite_param_count (cs)
	      != ipa_method_formal_count (cs->callee))
	    {
	      /* Handle cases of functions with 
	         a variable number of parameters.  */
	      ipa_callsite_param_count_set (cs, 0);
	      ipa_method_formal_count_set (cs->callee, 0);
	    }
	  else
	    ipa_callsite_compute_param (cs);
	}
    }
}