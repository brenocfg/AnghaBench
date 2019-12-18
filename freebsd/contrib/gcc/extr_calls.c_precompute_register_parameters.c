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
struct arg_data {scalar_t__ reg; scalar_t__ value; scalar_t__ mode; int /*<<< orphan*/  parallel_value; int /*<<< orphan*/  tree_value; int /*<<< orphan*/  unsignedp; int /*<<< orphan*/  pass_on_stack; } ;

/* Variables and functions */
 scalar_t__ BLKmode ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 scalar_t__ COSTS_N_INSNS (int) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  LEGITIMATE_CONSTANT_P (scalar_t__) ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  SET ; 
 scalar_t__ SMALL_REGISTER_CLASSES ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ convert_modes (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_to_mode_reg (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_group_load_into_temps (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_normal (int /*<<< orphan*/ ) ; 
 scalar_t__ force_reg (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  int_size_in_bytes (int /*<<< orphan*/ ) ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  pop_temp_slots () ; 
 int /*<<< orphan*/  preserve_temp_slots (scalar_t__) ; 
 int /*<<< orphan*/  push_temp_slots () ; 
 scalar_t__ rtx_cost (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
precompute_register_parameters (int num_actuals, struct arg_data *args,
				int *reg_parm_seen)
{
  int i;

  *reg_parm_seen = 0;

  for (i = 0; i < num_actuals; i++)
    if (args[i].reg != 0 && ! args[i].pass_on_stack)
      {
	*reg_parm_seen = 1;

	if (args[i].value == 0)
	  {
	    push_temp_slots ();
	    args[i].value = expand_normal (args[i].tree_value);
	    preserve_temp_slots (args[i].value);
	    pop_temp_slots ();
	  }

	/* If the value is a non-legitimate constant, force it into a
	   pseudo now.  TLS symbols sometimes need a call to resolve.  */
	if (CONSTANT_P (args[i].value)
	    && !LEGITIMATE_CONSTANT_P (args[i].value))
	  args[i].value = force_reg (args[i].mode, args[i].value);

	/* If we are to promote the function arg to a wider mode,
	   do it now.  */

	if (args[i].mode != TYPE_MODE (TREE_TYPE (args[i].tree_value)))
	  args[i].value
	    = convert_modes (args[i].mode,
			     TYPE_MODE (TREE_TYPE (args[i].tree_value)),
			     args[i].value, args[i].unsignedp);

	/* If we're going to have to load the value by parts, pull the
	   parts into pseudos.  The part extraction process can involve
	   non-trivial computation.  */
	if (GET_CODE (args[i].reg) == PARALLEL)
	  {
	    tree type = TREE_TYPE (args[i].tree_value);
	    args[i].parallel_value
	      = emit_group_load_into_temps (args[i].reg, args[i].value,
					    type, int_size_in_bytes (type));
	  }

	/* If the value is expensive, and we are inside an appropriately
	   short loop, put the value into a pseudo and then put the pseudo
	   into the hard reg.

	   For small register classes, also do this if this call uses
	   register parameters.  This is to avoid reload conflicts while
	   loading the parameters registers.  */

	else if ((! (REG_P (args[i].value)
		     || (GET_CODE (args[i].value) == SUBREG
			 && REG_P (SUBREG_REG (args[i].value)))))
		 && args[i].mode != BLKmode
		 && rtx_cost (args[i].value, SET) > COSTS_N_INSNS (1)
		 && ((SMALL_REGISTER_CLASSES && *reg_parm_seen)
		     || optimize))
	  args[i].value = copy_to_mode_reg (args[i].mode, args[i].value);
      }
}