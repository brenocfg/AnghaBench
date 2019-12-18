#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {scalar_t__ (* expand_decl ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CONST_DECL ; 
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_HAS_VALUE_EXPR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_ORIGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RTL_SET_P (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ LABEL_DECL ; 
 int /*<<< orphan*/  TREE_ASM_WRITTEN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  expand_decl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  rest_of_decl_compilation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

void
expand_var (tree var)
{
  if (DECL_EXTERNAL (var))
    return;

  if (TREE_STATIC (var))
    /* If this is an inlined copy of a static local variable,
       look up the original decl.  */
    var = DECL_ORIGIN (var);

  if (TREE_STATIC (var)
      ? !TREE_ASM_WRITTEN (var)
      : !DECL_RTL_SET_P (var))
    {
      if (TREE_CODE (var) == VAR_DECL && DECL_HAS_VALUE_EXPR_P (var))
	/* Should be ignored.  */;
      else if (lang_hooks.expand_decl (var))
	/* OK.  */;
      else if (TREE_CODE (var) == VAR_DECL && !TREE_STATIC (var))
	expand_decl (var);
      else if (TREE_CODE (var) == VAR_DECL && TREE_STATIC (var))
	rest_of_decl_compilation (var, 0, 0);
      else
	/* No expansion needed.  */
	gcc_assert (TREE_CODE (var) == TYPE_DECL
		    || TREE_CODE (var) == CONST_DECL
		    || TREE_CODE (var) == FUNCTION_DECL
		    || TREE_CODE (var) == LABEL_DECL);
    }
}