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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {scalar_t__ (* promote_function_return ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ calls; } ;

/* Variables and functions */
 int DECL_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RTL (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_modes (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  emit_group_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_null_return_1 () ; 
 int /*<<< orphan*/  int_size_in_bytes (int /*<<< orphan*/ ) ; 
 int promote_mode (int /*<<< orphan*/ ,int,int*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static void
expand_value_return (rtx val)
{
  /* Copy the value to the return location
     unless it's already there.  */

  rtx return_reg = DECL_RTL (DECL_RESULT (current_function_decl));
  if (return_reg != val)
    {
      tree type = TREE_TYPE (DECL_RESULT (current_function_decl));
      if (targetm.calls.promote_function_return (TREE_TYPE (current_function_decl)))
      {
	int unsignedp = TYPE_UNSIGNED (type);
	enum machine_mode old_mode
	  = DECL_MODE (DECL_RESULT (current_function_decl));
	enum machine_mode mode
	  = promote_mode (type, old_mode, &unsignedp, 1);

	if (mode != old_mode)
	  val = convert_modes (mode, old_mode, val, unsignedp);
      }
      if (GET_CODE (return_reg) == PARALLEL)
	emit_group_load (return_reg, val, type, int_size_in_bytes (type));
      else
	emit_move_insn (return_reg, val);
    }

  expand_null_return_1 ();
}