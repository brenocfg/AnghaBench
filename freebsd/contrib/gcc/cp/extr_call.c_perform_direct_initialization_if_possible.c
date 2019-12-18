#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_4__ {scalar_t__ bad_p; } ;
typedef  TYPE_1__ conversion ;

/* Variables and functions */
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ build_cplus_new (scalar_t__,scalar_t__) ; 
 scalar_t__ build_special_member_call (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_tree_list (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  complete_ctor_identifier ; 
 int /*<<< orphan*/  conversion_obstack ; 
 void* conversion_obstack_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ convert_like_real (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ error_operand_p (scalar_t__) ; 
 TYPE_1__* implicit_conversion (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,void*) ; 

tree
perform_direct_initialization_if_possible (tree type,
					   tree expr,
					   bool c_cast_p)
{
  conversion *conv;
  void *p;

  if (type == error_mark_node || error_operand_p (expr))
    return error_mark_node;
  /* [dcl.init]

     If the destination type is a (possibly cv-qualified) class type:

     -- If the initialization is direct-initialization ...,
     constructors are considered. ... If no constructor applies, or
     the overload resolution is ambiguous, the initialization is
     ill-formed.  */
  if (CLASS_TYPE_P (type))
    {
      expr = build_special_member_call (NULL_TREE, complete_ctor_identifier,
					build_tree_list (NULL_TREE, expr),
					type, LOOKUP_NORMAL);
      return build_cplus_new (type, expr);
    }

  /* Get the high-water mark for the CONVERSION_OBSTACK.  */
  p = conversion_obstack_alloc (0);

  conv = implicit_conversion (type, TREE_TYPE (expr), expr,
			      c_cast_p,
			      LOOKUP_NORMAL);
  if (!conv || conv->bad_p)
    expr = NULL_TREE;
  else
    expr = convert_like_real (conv, expr, NULL_TREE, 0, 0,
			      /*issue_conversion_warnings=*/false,
			      c_cast_p);

  /* Free all the conversions we allocated.  */
  obstack_free (&conversion_obstack, p);

  return expr;
}