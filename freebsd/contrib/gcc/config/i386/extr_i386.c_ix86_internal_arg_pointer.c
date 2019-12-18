#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {int /*<<< orphan*/  force_align_arg_pointer; } ;

/* Variables and functions */
 scalar_t__ DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_FILE_SCOPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ FORCE_PREFERRED_STACK_BOUNDARY_IN_MAIN ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ MAIN_NAME_P (scalar_t__) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  copy_to_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ix86_force_align_arg_pointer ; 
 int /*<<< orphan*/  ix86_force_align_arg_pointer_string ; 
 scalar_t__ lookup_attribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtual_incoming_args_rtx ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static rtx
ix86_internal_arg_pointer (void)
{
  bool has_force_align_arg_pointer =
    (0 != lookup_attribute (ix86_force_align_arg_pointer_string,
			    TYPE_ATTRIBUTES (TREE_TYPE (current_function_decl))));
  if ((FORCE_PREFERRED_STACK_BOUNDARY_IN_MAIN
       && DECL_NAME (current_function_decl)
       && MAIN_NAME_P (DECL_NAME (current_function_decl))
       && DECL_FILE_SCOPE_P (current_function_decl))
      || ix86_force_align_arg_pointer
      || has_force_align_arg_pointer)
    {
      /* Nested functions can't realign the stack due to a register
	 conflict.  */
      if (DECL_CONTEXT (current_function_decl)
	  && TREE_CODE (DECL_CONTEXT (current_function_decl)) == FUNCTION_DECL)
	{
	  if (ix86_force_align_arg_pointer)
	    warning (0, "-mstackrealign ignored for nested functions");
	  if (has_force_align_arg_pointer)
	    error ("%s not supported for nested functions",
		   ix86_force_align_arg_pointer_string);
	  return virtual_incoming_args_rtx;
	}
      cfun->machine->force_align_arg_pointer = gen_rtx_REG (Pmode, 2);
      return copy_to_reg (cfun->machine->force_align_arg_pointer);
    }
  else
    return virtual_incoming_args_rtx;
}