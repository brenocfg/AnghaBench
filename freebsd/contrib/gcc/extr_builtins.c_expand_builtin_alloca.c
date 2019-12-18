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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_UNIT ; 
 int /*<<< orphan*/  INTEGER_TYPE ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  allocate_dynamic_stack_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_normal (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_mudflap ; 
 int /*<<< orphan*/  ptr_mode ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_alloca (tree arglist, rtx target)
{
  rtx op0;
  rtx result;

  /* In -fmudflap-instrumented code, alloca() and __builtin_alloca()
     should always expand to function calls.  These can be intercepted
     in libmudflap.  */
  if (flag_mudflap)
    return 0;

  if (!validate_arglist (arglist, INTEGER_TYPE, VOID_TYPE))
    return 0;

  /* Compute the argument.  */
  op0 = expand_normal (TREE_VALUE (arglist));

  /* Allocate the desired space.  */
  result = allocate_dynamic_stack_space (op0, target, BITS_PER_UNIT);
  result = convert_memory_address (ptr_mode, result);

  return result;
}