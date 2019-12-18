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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 int /*<<< orphan*/ * CP_DECL_CONTEXT (int /*<<< orphan*/ * const) ; 
 scalar_t__ DECL_NAMESPACE_STD_P (int /*<<< orphan*/ *) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/ * const) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/ * global_namespace ; 
 int /*<<< orphan*/  write_string (char*) ; 
 int /*<<< orphan*/  write_unqualified_name (int /*<<< orphan*/ * const) ; 

__attribute__((used)) static void
write_unscoped_name (const tree decl)
{
  tree context = CP_DECL_CONTEXT (decl);

  MANGLE_TRACE_TREE ("unscoped-name", decl);

  /* Is DECL in ::std?  */
  if (DECL_NAMESPACE_STD_P (context))
    {
      write_string ("St");
      write_unqualified_name (decl);
    }
  else
    {
      /* If not, it should be either in the global namespace, or directly
	 in a local function scope.  */
      gcc_assert (context == global_namespace
		  || context == NULL
		  || TREE_CODE (context) == FUNCTION_DECL);

      write_unqualified_name (decl);
    }
}