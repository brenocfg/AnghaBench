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
struct TYPE_2__ {int /*<<< orphan*/ * static_chain_decl; } ;

/* Variables and functions */
 unsigned long ARM_FT_INTERWORKED ; 
 unsigned long ARM_FT_NAKED ; 
 unsigned long ARM_FT_NESTED ; 
 unsigned long ARM_FT_NORMAL ; 
 unsigned long ARM_FT_UNKNOWN ; 
 unsigned long ARM_FT_VOLATILE ; 
 scalar_t__ DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TARGET_INTERWORK ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_NOTHROW (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_THIS_VOLATILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  USING_SJLJ_EXCEPTIONS ; 
 unsigned long arm_isr_value (int /*<<< orphan*/ ) ; 
 TYPE_1__* cfun ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ flag_exceptions ; 
 scalar_t__ flag_unwind_tables ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ lookup_attribute (char*,scalar_t__) ; 
 scalar_t__ optimize ; 

__attribute__((used)) static unsigned long
arm_compute_func_type (void)
{
  unsigned long type = ARM_FT_UNKNOWN;
  tree a;
  tree attr;

  gcc_assert (TREE_CODE (current_function_decl) == FUNCTION_DECL);

  /* Decide if the current function is volatile.  Such functions
     never return, and many memory cycles can be saved by not storing
     register values that will never be needed again.  This optimization
     was added to speed up context switching in a kernel application.  */
  if (optimize > 0
      && (TREE_NOTHROW (current_function_decl)
          || !(flag_unwind_tables
               || (flag_exceptions && !USING_SJLJ_EXCEPTIONS)))
      && TREE_THIS_VOLATILE (current_function_decl))
    type |= ARM_FT_VOLATILE;

  if (cfun->static_chain_decl != NULL)
    type |= ARM_FT_NESTED;

  attr = DECL_ATTRIBUTES (current_function_decl);

  a = lookup_attribute ("naked", attr);
  if (a != NULL_TREE)
    type |= ARM_FT_NAKED;

  a = lookup_attribute ("isr", attr);
  if (a == NULL_TREE)
    a = lookup_attribute ("interrupt", attr);

  if (a == NULL_TREE)
    type |= TARGET_INTERWORK ? ARM_FT_INTERWORKED : ARM_FT_NORMAL;
  else
    type |= arm_isr_value (TREE_VALUE (a));

  return type;
}