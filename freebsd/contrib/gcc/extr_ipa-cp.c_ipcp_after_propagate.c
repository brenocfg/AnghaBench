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
 int /*<<< orphan*/  BOTTOM ; 
 scalar_t__ TOP ; 
 struct cgraph_node* cgraph_nodes ; 
 int ipa_method_formal_count (struct cgraph_node*) ; 
 scalar_t__ ipcp_cval_get_cvalue_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcp_method_cval (struct cgraph_node*,int) ; 
 int /*<<< orphan*/  ipcp_method_cval_set_cvalue_type (struct cgraph_node*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ipcp_after_propagate (void)
{
  int i, count;
  struct cgraph_node *node;
  bool prop_again;

  prop_again = false;
  for (node = cgraph_nodes; node; node = node->next)
    {
      count = ipa_method_formal_count (node);
      for (i = 0; i < count; i++)
	if (ipcp_cval_get_cvalue_type (ipcp_method_cval (node, i)) == TOP)
	  {
	    prop_again = true;
	    ipcp_method_cval_set_cvalue_type (node, i, BOTTOM);
	  }
    }
  return prop_again;
}