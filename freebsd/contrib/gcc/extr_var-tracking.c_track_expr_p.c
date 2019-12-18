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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ BLKmode ; 
 scalar_t__ DECL_DEBUG_EXPR (scalar_t__) ; 
 scalar_t__ DECL_DEBUG_EXPR_IS_FROM (scalar_t__) ; 
 scalar_t__ DECL_IGNORED_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 int /*<<< orphan*/  DECL_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_RTL_IF_SET (scalar_t__) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INTVAL (scalar_t__) ; 
 scalar_t__ MAX_VAR_PARTS ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_STATIC (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ contains_symbol_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
track_expr_p (tree expr)
{
  rtx decl_rtl;
  tree realdecl;

  /* If EXPR is not a parameter or a variable do not track it.  */
  if (TREE_CODE (expr) != VAR_DECL && TREE_CODE (expr) != PARM_DECL)
    return 0;

  /* It also must have a name...  */
  if (!DECL_NAME (expr))
    return 0;

  /* ... and a RTL assigned to it.  */
  decl_rtl = DECL_RTL_IF_SET (expr);
  if (!decl_rtl)
    return 0;
  
  /* If this expression is really a debug alias of some other declaration, we 
     don't need to track this expression if the ultimate declaration is
     ignored.  */
  realdecl = expr;
  if (DECL_DEBUG_EXPR_IS_FROM (realdecl) && DECL_DEBUG_EXPR (realdecl))
    {
      realdecl = DECL_DEBUG_EXPR (realdecl);
      /* ??? We don't yet know how to emit DW_OP_piece for variable
	 that has been SRA'ed.  */
      if (!DECL_P (realdecl))
	return 0;
    }

  /* Do not track EXPR if REALDECL it should be ignored for debugging
     purposes.  */ 
  if (DECL_IGNORED_P (realdecl))
    return 0;

  /* Do not track global variables until we are able to emit correct location
     list for them.  */
  if (TREE_STATIC (realdecl))
    return 0;

  /* When the EXPR is a DECL for alias of some variable (see example)
     the TREE_STATIC flag is not used.  Disable tracking all DECLs whose
     DECL_RTL contains SYMBOL_REF.

     Example:
     extern char **_dl_argv_internal __attribute__ ((alias ("_dl_argv")));
     char **_dl_argv;
  */
  if (MEM_P (decl_rtl)
      && contains_symbol_ref (XEXP (decl_rtl, 0)))
    return 0;

  /* If RTX is a memory it should not be very large (because it would be
     an array or struct).  */
  if (MEM_P (decl_rtl))
    {
      /* Do not track structures and arrays.  */
      if (GET_MODE (decl_rtl) == BLKmode
	  || AGGREGATE_TYPE_P (TREE_TYPE (realdecl)))
	return 0;
      if (MEM_SIZE (decl_rtl)
	  && INTVAL (MEM_SIZE (decl_rtl)) > MAX_VAR_PARTS)
	return 0;
    }

  return 1;
}