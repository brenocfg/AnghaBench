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

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ NULL_TREE ; 
 int TFF_CHASE_TYPEDEF ; 
 int TFF_RETURN_TYPE ; 
 int TFF_SCOPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_decl (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_function_decl (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_type (scalar_t__,int) ; 
 scalar_t__ global_namespace ; 
 int /*<<< orphan*/  pp_cxx_colon_colon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_scope (tree scope, int flags)
{
  int f = ~TFF_RETURN_TYPE & (flags & (TFF_SCOPE | TFF_CHASE_TYPEDEF));

  if (scope == NULL_TREE)
    return;

  if (TREE_CODE (scope) == NAMESPACE_DECL)
    {
      if (scope != global_namespace)
	{
	  dump_decl (scope, f);
	  pp_cxx_colon_colon (cxx_pp);
	}
    }
  else if (AGGREGATE_TYPE_P (scope))
    {
      dump_type (scope, f);
      pp_cxx_colon_colon (cxx_pp);
    }
  else if ((flags & TFF_SCOPE) && TREE_CODE (scope) == FUNCTION_DECL)
    {
      dump_function_decl (scope, f);
      pp_cxx_colon_colon (cxx_pp);
    }
}