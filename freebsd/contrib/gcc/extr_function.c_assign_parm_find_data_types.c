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
typedef  int /*<<< orphan*/ * tree ;
struct assign_parm_data_one {int named_arg; int passed_pointer; int nominal_mode; int passed_mode; int promoted_mode; int /*<<< orphan*/ * passed_type; int /*<<< orphan*/ * nominal_type; } ;
struct assign_parm_data_all {int /*<<< orphan*/  args_so_far; } ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {scalar_t__ (* promote_function_args ) (int /*<<< orphan*/ *) ;scalar_t__ (* strict_argument_naming ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ calls; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DECL_ARG_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ PARM_DECL ; 
 int Pmode ; 
 scalar_t__ TREE_CHAIN (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_FIELDS (int /*<<< orphan*/ *) ; 
 int TYPE_MODE (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_TRANSPARENT_UNION (int /*<<< orphan*/ *) ; 
 int TYPE_UNSIGNED (int /*<<< orphan*/ *) ; 
 scalar_t__ UNION_TYPE ; 
 scalar_t__ VOID_TYPE_P (int /*<<< orphan*/ *) ; 
 int VOIDmode ; 
 int /*<<< orphan*/ * build_pointer_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * current_function_decl ; 
 int /*<<< orphan*/  current_function_stdarg ; 
 int /*<<< orphan*/ * error_mark_node ; 
 int /*<<< orphan*/  memset (struct assign_parm_data_one*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pass_by_reference (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int promote_mode (int /*<<< orphan*/ *,int,int*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *) ; 
 TYPE_2__ targetm ; 
 int /*<<< orphan*/ * void_type_node ; 

__attribute__((used)) static void
assign_parm_find_data_types (struct assign_parm_data_all *all, tree parm,
			     struct assign_parm_data_one *data)
{
  tree nominal_type, passed_type;
  enum machine_mode nominal_mode, passed_mode, promoted_mode;

  memset (data, 0, sizeof (*data));

  /* NAMED_ARG is a mis-nomer.  We really mean 'non-varadic'. */
  if (!current_function_stdarg)
    data->named_arg = 1;  /* No varadic parms.  */
  else if (TREE_CHAIN (parm))
    data->named_arg = 1;  /* Not the last non-varadic parm. */
  else if (targetm.calls.strict_argument_naming (&all->args_so_far))
    data->named_arg = 1;  /* Only varadic ones are unnamed.  */
  else
    data->named_arg = 0;  /* Treat as varadic.  */

  nominal_type = TREE_TYPE (parm);
  passed_type = DECL_ARG_TYPE (parm);

  /* Look out for errors propagating this far.  Also, if the parameter's
     type is void then its value doesn't matter.  */
  if (TREE_TYPE (parm) == error_mark_node
      /* This can happen after weird syntax errors
	 or if an enum type is defined among the parms.  */
      || TREE_CODE (parm) != PARM_DECL
      || passed_type == NULL
      || VOID_TYPE_P (nominal_type))
    {
      nominal_type = passed_type = void_type_node;
      nominal_mode = passed_mode = promoted_mode = VOIDmode;
      goto egress;
    }

  /* Find mode of arg as it is passed, and mode of arg as it should be
     during execution of this function.  */
  passed_mode = TYPE_MODE (passed_type);
  nominal_mode = TYPE_MODE (nominal_type);

  /* If the parm is to be passed as a transparent union, use the type of
     the first field for the tests below.  We have already verified that
     the modes are the same.  */
  if (TREE_CODE (passed_type) == UNION_TYPE
      && TYPE_TRANSPARENT_UNION (passed_type))
    passed_type = TREE_TYPE (TYPE_FIELDS (passed_type));

  /* See if this arg was passed by invisible reference.  */
  if (pass_by_reference (&all->args_so_far, passed_mode,
			 passed_type, data->named_arg))
    {
      passed_type = nominal_type = build_pointer_type (passed_type);
      data->passed_pointer = true;
      passed_mode = nominal_mode = Pmode;
    }

  /* Find mode as it is passed by the ABI.  */
  promoted_mode = passed_mode;
  if (targetm.calls.promote_function_args (TREE_TYPE (current_function_decl)))
    {
      int unsignedp = TYPE_UNSIGNED (passed_type);
      promoted_mode = promote_mode (passed_type, promoted_mode,
				    &unsignedp, 1);
    }

 egress:
  data->nominal_type = nominal_type;
  data->passed_type = passed_type;
  data->nominal_mode = nominal_mode;
  data->passed_mode = passed_mode;
  data->promoted_mode = promoted_mode;
}