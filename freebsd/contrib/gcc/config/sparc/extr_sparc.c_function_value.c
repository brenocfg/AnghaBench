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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum mode_class { ____Placeholder_mode_class } mode_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (scalar_t__) ; 
 int BITS_PER_UNIT ; 
 int BLKmode ; 
 int GET_MODE_CLASS (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 int MODE_COMPLEX_FLOAT ; 
 int MODE_FLOAT ; 
 int MODE_INT ; 
 scalar_t__ RECORD_TYPE ; 
 int SPARC_FP_ARG_FIRST ; 
 int SPARC_INCOMING_INT_ARG_FIRST ; 
 int SPARC_OUTGOING_INT_ARG_FIRST ; 
 scalar_t__ TARGET_ARCH32 ; 
 scalar_t__ TARGET_ARCH64 ; 
 scalar_t__ TARGET_FPU ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ UNION_TYPE ; 
 scalar_t__ UNITS_PER_WORD ; 
 scalar_t__ VECTOR_TYPE ; 
 int /*<<< orphan*/  function_arg_record_value (scalar_t__,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  function_arg_union_value (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  function_arg_vector_value (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,int) ; 
 int int_size_in_bytes (scalar_t__) ; 
 int mode_for_size (int,int,int /*<<< orphan*/ ) ; 
 int word_mode ; 

rtx
function_value (tree type, enum machine_mode mode, int incoming_p)
{
  /* Beware that the two values are swapped here wrt function_arg.  */
  int regbase = (incoming_p
		 ? SPARC_OUTGOING_INT_ARG_FIRST
		 : SPARC_INCOMING_INT_ARG_FIRST);
  enum mode_class mclass = GET_MODE_CLASS (mode);
  int regno;

  /* Vector types deserve special treatment because they are polymorphic wrt
     their mode, depending upon whether VIS instructions are enabled.  */
  if (type && TREE_CODE (type) == VECTOR_TYPE)
    {
      HOST_WIDE_INT size = int_size_in_bytes (type);
      gcc_assert ((TARGET_ARCH32 && size <= 8)
		  || (TARGET_ARCH64 && size <= 32));

      if (mode == BLKmode)
	return function_arg_vector_value (size,
					  TYPE_MODE (TREE_TYPE (type)),
					  SPARC_FP_ARG_FIRST);
      else
	mclass = MODE_FLOAT;
    }

  if (TARGET_ARCH64 && type)
    {
      /* Structures up to 32 bytes in size are returned in registers.  */
      if (TREE_CODE (type) == RECORD_TYPE)
	{
	  HOST_WIDE_INT size = int_size_in_bytes (type);
	  gcc_assert (size <= 32);

	  return function_arg_record_value (type, mode, 0, 1, regbase);
	}

      /* Unions up to 32 bytes in size are returned in integer registers.  */
      else if (TREE_CODE (type) == UNION_TYPE)
	{
	  HOST_WIDE_INT size = int_size_in_bytes (type);
	  gcc_assert (size <= 32);

	  return function_arg_union_value (size, mode, 0, regbase);
	}

      /* Objects that require it are returned in FP registers.  */
      else if (mclass == MODE_FLOAT || mclass == MODE_COMPLEX_FLOAT)
	;

      /* All other aggregate types are returned in an integer register in a
	 mode corresponding to the size of the type.  */
      else if (AGGREGATE_TYPE_P (type))
	{
	  /* All other aggregate types are passed in an integer register
	     in a mode corresponding to the size of the type.  */
	  HOST_WIDE_INT size = int_size_in_bytes (type);
	  gcc_assert (size <= 32);

	  mode = mode_for_size (size * BITS_PER_UNIT, MODE_INT, 0);

	  /* ??? We probably should have made the same ABI change in
	     3.4.0 as the one we made for unions.   The latter was
	     required by the SCD though, while the former is not
	     specified, so we favored compatibility and efficiency.

	     Now we're stuck for aggregates larger than 16 bytes,
	     because OImode vanished in the meantime.  Let's not
	     try to be unduly clever, and simply follow the ABI
	     for unions in that case.  */
	  if (mode == BLKmode)
	    return function_arg_union_value (size, mode, 0, regbase);
	  else
	    mclass = MODE_INT;
	}

      /* This must match PROMOTE_FUNCTION_MODE.  */
      else if (mclass == MODE_INT && GET_MODE_SIZE (mode) < UNITS_PER_WORD)
	mode = word_mode;
    }

  if ((mclass == MODE_FLOAT || mclass == MODE_COMPLEX_FLOAT) && TARGET_FPU)
    regno = SPARC_FP_ARG_FIRST;
  else
    regno = regbase;

  return gen_rtx_REG (mode, regno);
}