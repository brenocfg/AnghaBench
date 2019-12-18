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
typedef  scalar_t__ tree ;
struct cgraph_node {scalar_t__ decl; } ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  ipa_method_formal_count_set (struct cgraph_node*,int) ; 

void
ipa_method_formal_compute_count (struct cgraph_node *mt)
{
  tree fndecl;
  tree fnargs;
  tree parm;
  int param_num;

  fndecl = mt->decl;
  fnargs = DECL_ARGUMENTS (fndecl);
  param_num = 0;
  for (parm = fnargs; parm; parm = TREE_CHAIN (parm))
    param_num++;
  ipa_method_formal_count_set (mt, param_num);
}