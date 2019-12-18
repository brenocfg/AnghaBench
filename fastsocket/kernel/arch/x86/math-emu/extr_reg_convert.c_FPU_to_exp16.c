#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int sigh; int /*<<< orphan*/  sigl; } ;
typedef  TYPE_1__ FPU_REG ;

/* Variables and functions */
 int /*<<< orphan*/  EXCEPTION (int) ; 
 scalar_t__ EXP_UNDER ; 
 int EX_INTERNAL ; 
 int /*<<< orphan*/  FPU_normalize_nuo (TYPE_1__*) ; 
 int /*<<< orphan*/  addexponent (TYPE_1__*,int) ; 
 int /*<<< orphan*/  exponent (TYPE_1__ const*) ; 
 scalar_t__ exponent16 (TYPE_1__*) ; 
 int getsign (TYPE_1__ const*) ; 
 int /*<<< orphan*/  setexponent16 (TYPE_1__*,int /*<<< orphan*/ ) ; 

int FPU_to_exp16(FPU_REG const *a, FPU_REG *x)
{
	int sign = getsign(a);

	*(long long *)&(x->sigl) = *(const long long *)&(a->sigl);

	/* Set up the exponent as a 16 bit quantity. */
	setexponent16(x, exponent(a));

	if (exponent16(x) == EXP_UNDER) {
		/* The number is a de-normal or pseudodenormal. */
		/* We only deal with the significand and exponent. */

		if (x->sigh & 0x80000000) {
			/* Is a pseudodenormal. */
			/* This is non-80486 behaviour because the number
			   loses its 'denormal' identity. */
			addexponent(x, 1);
		} else {
			/* Is a denormal. */
			addexponent(x, 1);
			FPU_normalize_nuo(x);
		}
	}

	if (!(x->sigh & 0x80000000)) {
		EXCEPTION(EX_INTERNAL | 0x180);
	}

	return sign;
}