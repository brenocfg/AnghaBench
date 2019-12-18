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

/* Variables and functions */
 int /*<<< orphan*/  build_component_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_indirect_ref (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 

tree
build_byref_local_var_access (tree expr, tree decl_name)
{
  tree exp = build_component_ref (expr, get_identifier ("__forwarding"));
  exp = build_indirect_ref (exp, "unary *");
  exp = build_component_ref (exp, decl_name);
  return exp;
}