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
struct cgraph_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOTTOM ; 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SCALAR_FLOAT_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOP ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int ipa_method_formal_count (struct cgraph_node*) ; 
 int /*<<< orphan*/  ipa_method_get_tree (struct cgraph_node*,int) ; 
 int /*<<< orphan*/  ipcp_formal_create (struct cgraph_node*) ; 
 int /*<<< orphan*/  ipcp_method_cval_set_cvalue_type (struct cgraph_node*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipcp_method_cval_init (struct cgraph_node *mt)
{
  int i;
  tree parm_tree;

  ipcp_formal_create (mt);
  for (i = 0; i < ipa_method_formal_count (mt); i++)
    {
      parm_tree = ipa_method_get_tree (mt, i);
      if (INTEGRAL_TYPE_P (TREE_TYPE (parm_tree)) 
	  || SCALAR_FLOAT_TYPE_P (TREE_TYPE (parm_tree)) 
	  || POINTER_TYPE_P (TREE_TYPE (parm_tree)))
	ipcp_method_cval_set_cvalue_type (mt, i, TOP);
      else
	ipcp_method_cval_set_cvalue_type (mt, i, BOTTOM);
    }
}