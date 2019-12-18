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
typedef  scalar_t__ tree ;
struct sparc_args {scalar_t__ libcall_p; scalar_t__ prototype_p; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum mode_class { ____Placeholder_mode_class } mode_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (scalar_t__) ; 
 int BITS_PER_UNIT ; 
 int BLKmode ; 
 int GET_MODE_CLASS (int) ; 
 int MODE_COMPLEX_FLOAT ; 
 int MODE_FLOAT ; 
 int /*<<< orphan*/  MODE_INT ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ RECORD_TYPE ; 
 int SPARC_FP_ARG_FIRST ; 
 scalar_t__ SPARC_FP_REG_P (int) ; 
 int SPARC_INCOMING_INT_ARG_FIRST ; 
 int SPARC_INT_ARG_MAX ; 
 int SPARC_OUTGOING_INT_ARG_FIRST ; 
 scalar_t__ TARGET_ARCH32 ; 
 scalar_t__ TARGET_ARCH64 ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ UNION_TYPE ; 
 scalar_t__ VECTOR_TYPE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  function_arg_record_value (scalar_t__,int,int,int,int) ; 
 int function_arg_slotno (struct sparc_args const*,int,scalar_t__,int,int,int*,int*) ; 
 int /*<<< orphan*/  function_arg_union_value (int,int,int,int) ; 
 int /*<<< orphan*/  function_arg_vector_value (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_EXPR_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,int) ; 
 int int_size_in_bytes (scalar_t__) ; 
 int mode_for_size (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
function_arg (const struct sparc_args *cum, enum machine_mode mode,
	      tree type, int named, int incoming_p)
{
  int regbase = (incoming_p
		 ? SPARC_INCOMING_INT_ARG_FIRST
		 : SPARC_OUTGOING_INT_ARG_FIRST);
  int slotno, regno, padding;
  enum mode_class mclass = GET_MODE_CLASS (mode);

  slotno = function_arg_slotno (cum, mode, type, named, incoming_p,
				&regno, &padding);
  if (slotno == -1)
    return 0;

  /* Vector types deserve special treatment because they are polymorphic wrt
     their mode, depending upon whether VIS instructions are enabled.  */
  if (type && TREE_CODE (type) == VECTOR_TYPE)
    {
      HOST_WIDE_INT size = int_size_in_bytes (type);
      gcc_assert ((TARGET_ARCH32 && size <= 8)
		  || (TARGET_ARCH64 && size <= 16));

      if (mode == BLKmode)
	return function_arg_vector_value (size,
					  TYPE_MODE (TREE_TYPE (type)),
					  SPARC_FP_ARG_FIRST + 2*slotno);
      else
	mclass = MODE_FLOAT;
    }

  if (TARGET_ARCH32)
    return gen_rtx_REG (mode, regno);

  /* Structures up to 16 bytes in size are passed in arg slots on the stack
     and are promoted to registers if possible.  */
  if (type && TREE_CODE (type) == RECORD_TYPE)
    {
      HOST_WIDE_INT size = int_size_in_bytes (type);
      gcc_assert (size <= 16);

      return function_arg_record_value (type, mode, slotno, named, regbase);
    }

  /* Unions up to 16 bytes in size are passed in integer registers.  */
  else if (type && TREE_CODE (type) == UNION_TYPE)
    {
      HOST_WIDE_INT size = int_size_in_bytes (type);
      gcc_assert (size <= 16);

      return function_arg_union_value (size, mode, slotno, regno);
    }

  /* v9 fp args in reg slots beyond the int reg slots get passed in regs
     but also have the slot allocated for them.
     If no prototype is in scope fp values in register slots get passed
     in two places, either fp regs and int regs or fp regs and memory.  */
  else if ((mclass == MODE_FLOAT || mclass == MODE_COMPLEX_FLOAT)
	   && SPARC_FP_REG_P (regno))
    {
      rtx reg = gen_rtx_REG (mode, regno);
      if (cum->prototype_p || cum->libcall_p)
	{
	  /* "* 2" because fp reg numbers are recorded in 4 byte
	     quantities.  */
#if 0
	  /* ??? This will cause the value to be passed in the fp reg and
	     in the stack.  When a prototype exists we want to pass the
	     value in the reg but reserve space on the stack.  That's an
	     optimization, and is deferred [for a bit].  */
	  if ((regno - SPARC_FP_ARG_FIRST) >= SPARC_INT_ARG_MAX * 2)
	    return gen_rtx_PARALLEL (mode,
			    gen_rtvec (2,
				       gen_rtx_EXPR_LIST (VOIDmode,
						NULL_RTX, const0_rtx),
				       gen_rtx_EXPR_LIST (VOIDmode,
						reg, const0_rtx)));
	  else
#else
	  /* ??? It seems that passing back a register even when past
	     the area declared by REG_PARM_STACK_SPACE will allocate
	     space appropriately, and will not copy the data onto the
	     stack, exactly as we desire.

	     This is due to locate_and_pad_parm being called in
	     expand_call whenever reg_parm_stack_space > 0, which
	     while beneficial to our example here, would seem to be
	     in error from what had been intended.  Ho hum...  -- r~ */
#endif
	    return reg;
	}
      else
	{
	  rtx v0, v1;

	  if ((regno - SPARC_FP_ARG_FIRST) < SPARC_INT_ARG_MAX * 2)
	    {
	      int intreg;

	      /* On incoming, we don't need to know that the value
		 is passed in %f0 and %i0, and it confuses other parts
		 causing needless spillage even on the simplest cases.  */
	      if (incoming_p)
		return reg;

	      intreg = (SPARC_OUTGOING_INT_ARG_FIRST
			+ (regno - SPARC_FP_ARG_FIRST) / 2);

	      v0 = gen_rtx_EXPR_LIST (VOIDmode, reg, const0_rtx);
	      v1 = gen_rtx_EXPR_LIST (VOIDmode, gen_rtx_REG (mode, intreg),
				      const0_rtx);
	      return gen_rtx_PARALLEL (mode, gen_rtvec (2, v0, v1));
	    }
	  else
	    {
	      v0 = gen_rtx_EXPR_LIST (VOIDmode, NULL_RTX, const0_rtx);
	      v1 = gen_rtx_EXPR_LIST (VOIDmode, reg, const0_rtx);
	      return gen_rtx_PARALLEL (mode, gen_rtvec (2, v0, v1));
	    }
	}
    }

  /* All other aggregate types are passed in an integer register in a mode
     corresponding to the size of the type.  */
  else if (type && AGGREGATE_TYPE_P (type))
    {
      HOST_WIDE_INT size = int_size_in_bytes (type);
      gcc_assert (size <= 16);

      mode = mode_for_size (size * BITS_PER_UNIT, MODE_INT, 0);
    }

  return gen_rtx_REG (mode, regno);
}