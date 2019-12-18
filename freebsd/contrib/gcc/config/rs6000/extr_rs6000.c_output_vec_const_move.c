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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_VECTOR_ELT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EASY_VECTOR_15 (int) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_ALTIVEC ; 
 int TARGET_SPE ; 
#define  V16QImode 130 
#define  V4SImode 129 
#define  V8HImode 128 
 scalar_t__ VEC_DUPLICATE ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_easy_altivec_constant (int /*<<< orphan*/ ) ; 
 scalar_t__ zero_constant (int /*<<< orphan*/ ,int) ; 

const char *
output_vec_const_move (rtx *operands)
{
  int cst, cst2;
  enum machine_mode mode;
  rtx dest, vec;

  dest = operands[0];
  vec = operands[1];
  mode = GET_MODE (dest);

  if (TARGET_ALTIVEC)
    {
      rtx splat_vec;
      if (zero_constant (vec, mode))
	return "vxor %0,%0,%0";

      splat_vec = gen_easy_altivec_constant (vec);
      gcc_assert (GET_CODE (splat_vec) == VEC_DUPLICATE);
      operands[1] = XEXP (splat_vec, 0);
      if (!EASY_VECTOR_15 (INTVAL (operands[1])))
	return "#";

      switch (GET_MODE (splat_vec))
	{
	case V4SImode:
	  return "vspltisw %0,%1";

	case V8HImode:
	  return "vspltish %0,%1";

	case V16QImode:
	  return "vspltisb %0,%1";

	default:
	  gcc_unreachable ();
	}
    }

  gcc_assert (TARGET_SPE);

  /* Vector constant 0 is handled as a splitter of V2SI, and in the
     pattern of V1DI, V4HI, and V2SF.

     FIXME: We should probably return # and add post reload
     splitters for these, but this way is so easy ;-).  */
  cst = INTVAL (CONST_VECTOR_ELT (vec, 0));
  cst2 = INTVAL (CONST_VECTOR_ELT (vec, 1));
  operands[1] = CONST_VECTOR_ELT (vec, 0);
  operands[2] = CONST_VECTOR_ELT (vec, 1);
  if (cst == cst2)
    return "li %0,%1\n\tevmergelo %0,%0,%0";
  else
    return "li %0,%1\n\tevmergelo %0,%0,%0\n\tli %0,%2";
}