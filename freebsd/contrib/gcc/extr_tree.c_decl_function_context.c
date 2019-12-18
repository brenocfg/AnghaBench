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
 scalar_t__ BLOCK ; 
 scalar_t__ BLOCK_SUPERCONTEXT (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_VINDEX (scalar_t__) ; 
 scalar_t__ ERROR_MARK ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 scalar_t__ get_containing_scope (scalar_t__) ; 

tree
decl_function_context (tree decl)
{
  tree context;

  if (TREE_CODE (decl) == ERROR_MARK)
    return 0;

  /* C++ virtual functions use DECL_CONTEXT for the class of the vtable
     where we look up the function at runtime.  Such functions always take
     a first argument of type 'pointer to real context'.

     C++ should really be fixed to use DECL_CONTEXT for the real context,
     and use something else for the "virtual context".  */
  else if (TREE_CODE (decl) == FUNCTION_DECL && DECL_VINDEX (decl))
    context
      = TYPE_MAIN_VARIANT
	(TREE_TYPE (TREE_VALUE (TYPE_ARG_TYPES (TREE_TYPE (decl)))));
  else
    context = DECL_CONTEXT (decl);

  while (context && TREE_CODE (context) != FUNCTION_DECL)
    {
      if (TREE_CODE (context) == BLOCK)
	context = BLOCK_SUPERCONTEXT (context);
      else
	context = get_containing_scope (context);
    }

  return context;
}