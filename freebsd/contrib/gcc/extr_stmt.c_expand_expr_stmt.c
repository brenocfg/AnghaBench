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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ BLKmode ; 
 int /*<<< orphan*/  EQ ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ TREE_THIS_VOLATILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 scalar_t__ copy_to_reg (scalar_t__) ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 scalar_t__ expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_normal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_temp_slots () ; 
 scalar_t__ gen_label_rtx () ; 

void
expand_expr_stmt (tree exp)
{
  rtx value;
  tree type;

  value = expand_expr (exp, const0_rtx, VOIDmode, 0);
  type = TREE_TYPE (exp);

  /* If all we do is reference a volatile value in memory,
     copy it to a register to be sure it is actually touched.  */
  if (value && MEM_P (value) && TREE_THIS_VOLATILE (exp))
    {
      if (TYPE_MODE (type) == VOIDmode)
	;
      else if (TYPE_MODE (type) != BLKmode)
	value = copy_to_reg (value);
      else
	{
	  rtx lab = gen_label_rtx ();

	  /* Compare the value with itself to reference it.  */
	  emit_cmp_and_jump_insns (value, value, EQ,
				   expand_normal (TYPE_SIZE (type)),
				   BLKmode, 0, lab);
	  emit_label (lab);
	}
    }

  /* Free any temporaries used to evaluate this expression.  */
  free_temp_slots ();
}