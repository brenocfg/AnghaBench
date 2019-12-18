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
struct TYPE_3__ {scalar_t__ m64; } ;
struct fp_ext {scalar_t__ sign; int exp; TYPE_1__ mant; scalar_t__ lowmant; } ;
struct TYPE_4__ {scalar_t__ rnd; } ;

/* Variables and functions */
 scalar_t__ FPCR_ROUND_RM ; 
 TYPE_2__* FPDATA ; 
 scalar_t__ IS_INF (struct fp_ext*) ; 
 scalar_t__ IS_ZERO (struct fp_ext*) ; 
 int /*<<< orphan*/  PINSTR ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fp_addcarry (struct fp_ext*) ; 
 scalar_t__ fp_addmant (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_copy_ext (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_denormalize (struct fp_ext*,int) ; 
 int /*<<< orphan*/  fp_dyadic_check (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_nan (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_submant (struct fp_ext*,struct fp_ext*,struct fp_ext*) ; 

struct fp_ext *
fp_fadd(struct fp_ext *dest, struct fp_ext *src)
{
	int diff;

	dprint(PINSTR, "fadd\n");

	fp_dyadic_check(dest, src);

	if (IS_INF(dest)) {
		/* infinity - infinity == NaN */
		if (IS_INF(src) && (src->sign != dest->sign))
			fp_set_nan(dest);
		return dest;
	}
	if (IS_INF(src)) {
		fp_copy_ext(dest, src);
		return dest;
	}

	if (IS_ZERO(dest)) {
		if (IS_ZERO(src)) {
			if (src->sign != dest->sign) {
				if (FPDATA->rnd == FPCR_ROUND_RM)
					dest->sign = 1;
				else
					dest->sign = 0;
			}
		} else
			fp_copy_ext(dest, src);
		return dest;
	}

	dest->lowmant = src->lowmant = 0;

	if ((diff = dest->exp - src->exp) > 0)
		fp_denormalize(src, diff);
	else if ((diff = -diff) > 0)
		fp_denormalize(dest, diff);

	if (dest->sign == src->sign) {
		if (fp_addmant(dest, src))
			if (!fp_addcarry(dest))
				return dest;
	} else {
		if (dest->mant.m64 < src->mant.m64) {
			fp_submant(dest, src, dest);
			dest->sign = !dest->sign;
		} else
			fp_submant(dest, dest, src);
	}

	return dest;
}