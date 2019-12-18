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
typedef  scalar_t__ tree ;
struct TYPE_2__ {int externally_visible; int /*<<< orphan*/  inlinable; int /*<<< orphan*/  disregard_inline_limits; } ;
struct cgraph_node {TYPE_1__ local; int /*<<< orphan*/  origin; scalar_t__ needed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (scalar_t__) ; 
 scalar_t__ DECL_ASSEMBLER_NAME_SET_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_ATTRIBUTES (scalar_t__) ; 
 scalar_t__ DECL_COMDAT (scalar_t__) ; 
 int /*<<< orphan*/  DECL_DECLARED_INLINE_P (scalar_t__) ; 
 scalar_t__ DECL_EXTERNAL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_INLINE (scalar_t__) ; 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 scalar_t__ DECL_STATIC_CONSTRUCTOR (scalar_t__) ; 
 scalar_t__ DECL_STATIC_DESTRUCTOR (scalar_t__) ; 
 scalar_t__ MAIN_NAME_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PUBLIC (scalar_t__) ; 
 scalar_t__ TREE_SYMBOL_REFERENCED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_default_inline_p (struct cgraph_node*,int /*<<< orphan*/ *) ; 
 scalar_t__ decl_function_context (scalar_t__) ; 
 scalar_t__ flag_unit_at_a_time ; 
 int /*<<< orphan*/  flag_whole_program ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optimize ; 

__attribute__((used)) static bool
decide_is_function_needed (struct cgraph_node *node, tree decl)
{
  tree origin;
  if (MAIN_NAME_P (DECL_NAME (decl))
      && TREE_PUBLIC (decl))
    {
      node->local.externally_visible = true;
      return true;
    }

  /* If the user told us it is used, then it must be so.  */
  if (node->local.externally_visible)
    return true;

  if (!flag_unit_at_a_time && lookup_attribute ("used", DECL_ATTRIBUTES (decl)))
    return true;

  /* ??? If the assembler name is set by hand, it is possible to assemble
     the name later after finalizing the function and the fact is noticed
     in assemble_name then.  This is arguably a bug.  */
  if (DECL_ASSEMBLER_NAME_SET_P (decl)
      && TREE_SYMBOL_REFERENCED (DECL_ASSEMBLER_NAME (decl)))
    return true;

  /* If we decided it was needed before, but at the time we didn't have
     the body of the function available, then it's still needed.  We have
     to go back and re-check its dependencies now.  */
  if (node->needed)
    return true;

  /* Externally visible functions must be output.  The exception is
     COMDAT functions that must be output only when they are needed.

     When not optimizing, also output the static functions. (see
     PR24561), but don't do so for always_inline functions, functions
     declared inline and nested functions.  These was optimized out
     in the original implementation and it is unclear whether we want
     to change the behavior here.  */
  if (((TREE_PUBLIC (decl)
	|| (!optimize && !node->local.disregard_inline_limits
	    && !DECL_DECLARED_INLINE_P (decl)
	    && !node->origin))
      && !flag_whole_program)
      && !DECL_COMDAT (decl) && !DECL_EXTERNAL (decl))
    return true;

  /* Constructors and destructors are reachable from the runtime by
     some mechanism.  */
  if (DECL_STATIC_CONSTRUCTOR (decl) || DECL_STATIC_DESTRUCTOR (decl))
    return true;

  if (flag_unit_at_a_time)
    return false;

  /* If not doing unit at a time, then we'll only defer this function
     if its marked for inlining.  Otherwise we want to emit it now.  */

  /* "extern inline" functions are never output locally.  */
  if (DECL_EXTERNAL (decl))
    return false;
  /* Nested functions of extern inline function shall not be emit unless
     we inlined the origin.  */
  for (origin = decl_function_context (decl); origin;
       origin = decl_function_context (origin))
    if (DECL_EXTERNAL (origin))
      return false;
  /* We want to emit COMDAT functions only when absolutely necessary.  */
  if (DECL_COMDAT (decl))
    return false;
  if (!DECL_INLINE (decl)
      || (!node->local.disregard_inline_limits
	  /* When declared inline, defer even the uninlinable functions.
	     This allows them to be eliminated when unused.  */
	  && !DECL_DECLARED_INLINE_P (decl)
	  && (!node->local.inlinable || !cgraph_default_inline_p (node, NULL))))
    return true;

  return false;
}