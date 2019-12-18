#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int high; } ;
typedef  TYPE_2__ floatx80 ;
typedef  int float64 ;
typedef  int float32 ;
struct TYPE_15__ {int* fType; TYPE_1__* fpreg; } ;
struct TYPE_13__ {int fSingle; int fDouble; TYPE_2__ fExtended; } ;
typedef  TYPE_3__ FPA11 ;

/* Variables and functions */
 int BIT_AC ; 
 unsigned int CC_CARRY ; 
 unsigned int CC_NEGATIVE ; 
 unsigned int CC_OVERFLOW ; 
 unsigned int CC_ZERO ; 
 scalar_t__ CONSTANT_FM (unsigned int const) ; 
 TYPE_3__* GET_FPA11 () ; 
 scalar_t__ float32_eq_nocheck (int,int) ; 
 scalar_t__ float32_is_nan (int) ; 
 scalar_t__ float32_lt_nocheck (int,int) ; 
 int float32_to_float64 (int) ; 
 TYPE_2__ float32_to_floatx80 (int) ; 
 scalar_t__ float64_eq_nocheck (int,int) ; 
 scalar_t__ float64_is_nan (int) ; 
 scalar_t__ float64_lt_nocheck (int,int) ; 
 TYPE_2__ float64_to_floatx80 (int) ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 int /*<<< orphan*/  float_raise (int /*<<< orphan*/ ) ; 
 scalar_t__ floatx80_eq (TYPE_2__,TYPE_2__) ; 
 scalar_t__ floatx80_is_nan (TYPE_2__) ; 
 scalar_t__ floatx80_lt (TYPE_2__,TYPE_2__) ; 
 int getDoubleConstant (unsigned int) ; 
 TYPE_2__ getExtendedConstant (unsigned int) ; 
 unsigned int getFm (unsigned int const) ; 
 unsigned int getFn (unsigned int const) ; 
 int getSingleConstant (unsigned int) ; 
 int readFPSR () ; 
#define  typeDouble 130 
#define  typeExtended 129 
#define  typeSingle 128 
 int /*<<< orphan*/  writeConditionCodes (unsigned int) ; 

__attribute__((used)) static unsigned int PerformComparison(const unsigned int opcode)
{
	FPA11 *fpa11 = GET_FPA11();
	unsigned int Fn = getFn(opcode), Fm = getFm(opcode);
	int e_flag = opcode & 0x400000;	/* 1 if CxFE */
	int n_flag = opcode & 0x200000;	/* 1 if CNxx */
	unsigned int flags = 0;

#ifdef CONFIG_FPE_NWFPE_XP
	floatx80 rFn, rFm;

	/* Check for unordered condition and convert all operands to 80-bit
	   format.
	   ?? Might be some mileage in avoiding this conversion if possible.
	   Eg, if both operands are 32-bit, detect this and do a 32-bit
	   comparison (cheaper than an 80-bit one).  */
	switch (fpa11->fType[Fn]) {
	case typeSingle:
		//printk("single.\n");
		if (float32_is_nan(fpa11->fpreg[Fn].fSingle))
			goto unordered;
		rFn = float32_to_floatx80(fpa11->fpreg[Fn].fSingle);
		break;

	case typeDouble:
		//printk("double.\n");
		if (float64_is_nan(fpa11->fpreg[Fn].fDouble))
			goto unordered;
		rFn = float64_to_floatx80(fpa11->fpreg[Fn].fDouble);
		break;

	case typeExtended:
		//printk("extended.\n");
		if (floatx80_is_nan(fpa11->fpreg[Fn].fExtended))
			goto unordered;
		rFn = fpa11->fpreg[Fn].fExtended;
		break;

	default:
		return 0;
	}

	if (CONSTANT_FM(opcode)) {
		//printk("Fm is a constant: #%d.\n",Fm);
		rFm = getExtendedConstant(Fm);
		if (floatx80_is_nan(rFm))
			goto unordered;
	} else {
		//printk("Fm = r%d which contains a ",Fm);
		switch (fpa11->fType[Fm]) {
		case typeSingle:
			//printk("single.\n");
			if (float32_is_nan(fpa11->fpreg[Fm].fSingle))
				goto unordered;
			rFm = float32_to_floatx80(fpa11->fpreg[Fm].fSingle);
			break;

		case typeDouble:
			//printk("double.\n");
			if (float64_is_nan(fpa11->fpreg[Fm].fDouble))
				goto unordered;
			rFm = float64_to_floatx80(fpa11->fpreg[Fm].fDouble);
			break;

		case typeExtended:
			//printk("extended.\n");
			if (floatx80_is_nan(fpa11->fpreg[Fm].fExtended))
				goto unordered;
			rFm = fpa11->fpreg[Fm].fExtended;
			break;

		default:
			return 0;
		}
	}

	if (n_flag)
		rFm.high ^= 0x8000;

	/* test for less than condition */
	if (floatx80_lt(rFn, rFm))
		flags |= CC_NEGATIVE;

	/* test for equal condition */
	if (floatx80_eq(rFn, rFm))
		flags |= CC_ZERO;

	/* test for greater than or equal condition */
	if (floatx80_lt(rFm, rFn))
		flags |= CC_CARRY;

#else
	if (CONSTANT_FM(opcode)) {
		/* Fm is a constant.  Do the comparison in whatever precision
		   Fn happens to be stored in.  */
		if (fpa11->fType[Fn] == typeSingle) {
			float32 rFm = getSingleConstant(Fm);
			float32 rFn = fpa11->fpreg[Fn].fSingle;

			if (float32_is_nan(rFn))
				goto unordered;

			if (n_flag)
				rFm ^= 0x80000000;

			/* test for less than condition */
			if (float32_lt_nocheck(rFn, rFm))
				flags |= CC_NEGATIVE;

			/* test for equal condition */
			if (float32_eq_nocheck(rFn, rFm))
				flags |= CC_ZERO;

			/* test for greater than or equal condition */
			if (float32_lt_nocheck(rFm, rFn))
				flags |= CC_CARRY;
		} else {
			float64 rFm = getDoubleConstant(Fm);
			float64 rFn = fpa11->fpreg[Fn].fDouble;

			if (float64_is_nan(rFn))
				goto unordered;

			if (n_flag)
				rFm ^= 0x8000000000000000ULL;

			/* test for less than condition */
			if (float64_lt_nocheck(rFn, rFm))
				flags |= CC_NEGATIVE;

			/* test for equal condition */
			if (float64_eq_nocheck(rFn, rFm))
				flags |= CC_ZERO;

			/* test for greater than or equal condition */
			if (float64_lt_nocheck(rFm, rFn))
				flags |= CC_CARRY;
		}
	} else {
		/* Both operands are in registers.  */
		if (fpa11->fType[Fn] == typeSingle
		    && fpa11->fType[Fm] == typeSingle) {
			float32 rFm = fpa11->fpreg[Fm].fSingle;
			float32 rFn = fpa11->fpreg[Fn].fSingle;

			if (float32_is_nan(rFn)
			    || float32_is_nan(rFm))
				goto unordered;

			if (n_flag)
				rFm ^= 0x80000000;

			/* test for less than condition */
			if (float32_lt_nocheck(rFn, rFm))
				flags |= CC_NEGATIVE;

			/* test for equal condition */
			if (float32_eq_nocheck(rFn, rFm))
				flags |= CC_ZERO;

			/* test for greater than or equal condition */
			if (float32_lt_nocheck(rFm, rFn))
				flags |= CC_CARRY;
		} else {
			/* Promote 32-bit operand to 64 bits.  */
			float64 rFm, rFn;

			rFm = (fpa11->fType[Fm] == typeSingle) ?
			    float32_to_float64(fpa11->fpreg[Fm].fSingle)
			    : fpa11->fpreg[Fm].fDouble;

			rFn = (fpa11->fType[Fn] == typeSingle) ?
			    float32_to_float64(fpa11->fpreg[Fn].fSingle)
			    : fpa11->fpreg[Fn].fDouble;

			if (float64_is_nan(rFn)
			    || float64_is_nan(rFm))
				goto unordered;

			if (n_flag)
				rFm ^= 0x8000000000000000ULL;

			/* test for less than condition */
			if (float64_lt_nocheck(rFn, rFm))
				flags |= CC_NEGATIVE;

			/* test for equal condition */
			if (float64_eq_nocheck(rFn, rFm))
				flags |= CC_ZERO;

			/* test for greater than or equal condition */
			if (float64_lt_nocheck(rFm, rFn))
				flags |= CC_CARRY;
		}
	}

#endif

	writeConditionCodes(flags);

	return 1;

      unordered:
	/* ?? The FPA data sheet is pretty vague about this, in particular
	   about whether the non-E comparisons can ever raise exceptions.
	   This implementation is based on a combination of what it says in
	   the data sheet, observation of how the Acorn emulator actually
	   behaves (and how programs expect it to) and guesswork.  */
	flags |= CC_OVERFLOW;
	flags &= ~(CC_ZERO | CC_NEGATIVE);

	if (BIT_AC & readFPSR())
		flags |= CC_CARRY;

	if (e_flag)
		float_raise(float_flag_invalid);

	writeConditionCodes(flags);
	return 1;
}