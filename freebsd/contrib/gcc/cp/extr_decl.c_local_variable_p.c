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
 int /*<<< orphan*/  CP_DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAMESPACE_SCOPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 

int
local_variable_p (tree t)
{
  if ((TREE_CODE (t) == VAR_DECL
       /* A VAR_DECL with a context that is a _TYPE is a static data
	  member.  */
       && !TYPE_P (CP_DECL_CONTEXT (t))
       /* Any other non-local variable must be at namespace scope.  */
       && !DECL_NAMESPACE_SCOPE_P (t))
      || (TREE_CODE (t) == PARM_DECL))
    return 1;

  return 0;
}