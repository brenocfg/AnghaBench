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
 int /*<<< orphan*/  current_namespace ; 
 int /*<<< orphan*/  decl_namespace_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ancestor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pedwarn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_explicit_instantiation_namespace (tree spec)
{
  tree ns;

  /* DR 275: An explicit instantiation shall appear in an enclosing
     namespace of its template.  */
  ns = decl_namespace_context (spec);
  if (!is_ancestor (current_namespace, ns))
    pedwarn ("explicit instantiation of %qD in namespace %qD "
	     "(which does not enclose namespace %qD)",
	     spec, current_namespace, ns);
}