#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* m32; scalar_t__ m64; } ;
struct fp_ext {int sign; int exp; TYPE_1__ mant; scalar_t__ lowmant; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPSR_EXC_UNFL ; 
 scalar_t__ IS_INF (struct fp_ext*) ; 
 scalar_t__ IS_ZERO (struct fp_ext*) ; 
 int /*<<< orphan*/  PINSTR ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fp_copy_ext (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_denormalize (struct fp_ext*,int) ; 
 int /*<<< orphan*/  fp_dyadic_check (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_mul64 (int,int,int,int) ; 
 int /*<<< orphan*/  fp_set_nan (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_ovrflw (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_sr (int /*<<< orphan*/ ) ; 

struct fp_ext *
fp_fsglmul(struct fp_ext *dest, struct fp_ext *src)
{
	int exp;

	dprint(PINSTR, "fsglmul\n");

	fp_dyadic_check(dest, src);

	/* calculate the correct sign now, as it's necessary for infinities */
	dest->sign = src->sign ^ dest->sign;

	/* Handle infinities */
	if (IS_INF(dest)) {
		if (IS_ZERO(src))
			fp_set_nan(dest);
		return dest;
	}
	if (IS_INF(src)) {
		if (IS_ZERO(dest))
			fp_set_nan(dest);
		else
			fp_copy_ext(dest, src);
		return dest;
	}

	/* Of course, as we all know, zero * anything = zero.  You may
	   not have known that it might be a positive or negative
	   zero... */
	if (IS_ZERO(dest) || IS_ZERO(src)) {
		dest->exp = 0;
		dest->mant.m64 = 0;
		dest->lowmant = 0;

		return dest;
	}

	exp = dest->exp + src->exp - 0x3ffe;

	/* do a 32-bit multiply */
	fp_mul64(dest->mant.m32[0], dest->mant.m32[1],
		 dest->mant.m32[0] & 0xffffff00,
		 src->mant.m32[0] & 0xffffff00);

	if (exp >= 0x7fff) {
		fp_set_ovrflw(dest);
		return dest;
	}
	dest->exp = exp;
	if (exp < 0) {
		fp_set_sr(FPSR_EXC_UNFL);
		fp_denormalize(dest, -exp);
	}

	return dest;
}