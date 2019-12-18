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
typedef  scalar_t__ u_char ;
typedef  int /*<<< orphan*/  FPU_REG ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_INF ; 
 int /*<<< orphan*/  CONST_Z ; 
 int /*<<< orphan*/  EXCEPTION (int) ; 
 int EX_INTERNAL ; 
 int EX_Invalid ; 
 int EX_StackUnder ; 
 scalar_t__ FPU_Special (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FPU_copy_to_reg0 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ FPU_divide_by_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FPU_settag0 (scalar_t__) ; 
 int /*<<< orphan*/  FPU_stack_overflow () ; 
 int /*<<< orphan*/  FPU_stack_underflow () ; 
 int /*<<< orphan*/  FPU_to_exp16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGN_NEG ; 
 scalar_t__ STACK_OVERFLOW ; 
 scalar_t__ TAG_Empty ; 
 scalar_t__ TAG_Special ; 
 scalar_t__ TAG_Valid ; 
 scalar_t__ TAG_Zero ; 
 scalar_t__ TW_Denormal ; 
 scalar_t__ TW_Infinity ; 
 scalar_t__ TW_NaN ; 
 int /*<<< orphan*/  clear_C1 () ; 
 int control_word ; 
 int /*<<< orphan*/  convert_l2reg (long*,int) ; 
 scalar_t__ denormal_operand () ; 
 int /*<<< orphan*/  exponent (int /*<<< orphan*/ *) ; 
 long exponent16 (int /*<<< orphan*/ *) ; 
 scalar_t__ getsign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push () ; 
 scalar_t__ real_1op_NaN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setexponent16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setexponentpos (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpositive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsign (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void fxtract(FPU_REG *st0_ptr, u_char st0_tag)
{
	FPU_REG *st_new_ptr;
	u_char sign;
	register FPU_REG *st1_ptr = st0_ptr;	/* anticipate */

	if (STACK_OVERFLOW) {
		FPU_stack_overflow();
		return;
	}

	clear_C1();

	if (st0_tag == TAG_Valid) {
		long e;

		push();
		sign = getsign(st1_ptr);
		reg_copy(st1_ptr, st_new_ptr);
		setexponent16(st_new_ptr, exponent(st_new_ptr));

	      denormal_arg:

		e = exponent16(st_new_ptr);
		convert_l2reg(&e, 1);
		setexponentpos(st_new_ptr, 0);
		setsign(st_new_ptr, sign);
		FPU_settag0(TAG_Valid);	/* Needed if arg was a denormal */
		return;
	} else if (st0_tag == TAG_Zero) {
		sign = getsign(st0_ptr);

		if (FPU_divide_by_zero(0, SIGN_NEG) < 0)
			return;

		push();
		FPU_copy_to_reg0(&CONST_Z, TAG_Zero);
		setsign(st_new_ptr, sign);
		return;
	}

	if (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);

	if (st0_tag == TW_Denormal) {
		if (denormal_operand() < 0)
			return;

		push();
		sign = getsign(st1_ptr);
		FPU_to_exp16(st1_ptr, st_new_ptr);
		goto denormal_arg;
	} else if (st0_tag == TW_Infinity) {
		sign = getsign(st0_ptr);
		setpositive(st0_ptr);
		push();
		FPU_copy_to_reg0(&CONST_INF, TAG_Special);
		setsign(st_new_ptr, sign);
		return;
	} else if (st0_tag == TW_NaN) {
		if (real_1op_NaN(st0_ptr) < 0)
			return;

		push();
		FPU_copy_to_reg0(st0_ptr, TAG_Special);
		return;
	} else if (st0_tag == TAG_Empty) {
		/* Is this the correct behaviour? */
		if (control_word & EX_Invalid) {
			FPU_stack_underflow();
			push();
			FPU_stack_underflow();
		} else
			EXCEPTION(EX_StackUnder);
	}
#ifdef PARANOID
	else
		EXCEPTION(EX_INTERNAL | 0x119);
#endif /* PARANOID */
}