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
typedef  union parameter_info {int dummy; } parameter_info ;
typedef  int /*<<< orphan*/  tree ;
struct cgraph_node {int /*<<< orphan*/  decl; } ;
typedef  enum cvalue_type { ____Placeholder_cvalue_type } cvalue_type ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_const_val (union parameter_info*,int,int /*<<< orphan*/ ) ; 
 char* cgraph_node_name (struct cgraph_node*) ; 
 int /*<<< orphan*/  constant_val_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  ipa_method_get_tree (struct cgraph_node*,int) ; 

__attribute__((used)) static void
ipcp_propagate_const (struct cgraph_node *mt, int param,
		      union parameter_info *cvalue ,enum cvalue_type type)
{
  tree fndecl;
  tree const_val;
  tree parm_tree;

  if (dump_file)
    fprintf (dump_file, "propagating const to %s\n", cgraph_node_name (mt));
  fndecl = mt->decl;
  parm_tree = ipa_method_get_tree (mt, param);
  const_val = build_const_val (cvalue, type, TREE_TYPE (parm_tree));
  constant_val_insert (fndecl, parm_tree, const_val);
}