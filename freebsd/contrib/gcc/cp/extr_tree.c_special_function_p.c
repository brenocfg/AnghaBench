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
typedef  int /*<<< orphan*/  special_function_kind ;

/* Variables and functions */
 scalar_t__ DECL_BASE_DESTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_COMPLETE_DESTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_CONV_FN_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_COPY_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_DELETING_DESTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_MAYBE_IN_CHARGE_DESTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_OVERLOADED_OPERATOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NOP_EXPR ; 
 int /*<<< orphan*/  sfk_assignment_operator ; 
 int /*<<< orphan*/  sfk_base_destructor ; 
 int /*<<< orphan*/  sfk_complete_destructor ; 
 int /*<<< orphan*/  sfk_constructor ; 
 int /*<<< orphan*/  sfk_conversion ; 
 int /*<<< orphan*/  sfk_copy_constructor ; 
 int /*<<< orphan*/  sfk_deleting_destructor ; 
 int /*<<< orphan*/  sfk_destructor ; 
 int /*<<< orphan*/  sfk_none ; 

special_function_kind
special_function_p (tree decl)
{
  /* Rather than doing all this stuff with magic names, we should
     probably have a field of type `special_function_kind' in
     DECL_LANG_SPECIFIC.  */
  if (DECL_COPY_CONSTRUCTOR_P (decl))
    return sfk_copy_constructor;
  if (DECL_CONSTRUCTOR_P (decl))
    return sfk_constructor;
  if (DECL_OVERLOADED_OPERATOR_P (decl) == NOP_EXPR)
    return sfk_assignment_operator;
  if (DECL_MAYBE_IN_CHARGE_DESTRUCTOR_P (decl))
    return sfk_destructor;
  if (DECL_COMPLETE_DESTRUCTOR_P (decl))
    return sfk_complete_destructor;
  if (DECL_BASE_DESTRUCTOR_P (decl))
    return sfk_base_destructor;
  if (DECL_DELETING_DESTRUCTOR_P (decl))
    return sfk_deleting_destructor;
  if (DECL_CONV_FN_P (decl))
    return sfk_conversion;

  return sfk_none;
}