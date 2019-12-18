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
typedef  unsigned int sgl_floating_point ;
typedef  int boolean ;

/* Variables and functions */
 int FALSE ; 
 unsigned int INEXACTEXCEPTION ; 
 unsigned int INVALIDEXCEPTION ; 
 scalar_t__ Is_inexacttrap_enabled () ; 
 scalar_t__ Is_invalidtrap_enabled () ; 
 unsigned int NOEXCEPTION ; 
#define  ROUNDNEAREST 129 
#define  ROUNDPLUS 128 
 int Rounding_mode () ; 
 int SGL_BIAS ; 
 int SGL_INFINITY_EXPONENT ; 
 int SGL_P ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Set_invalidflag () ; 
 int /*<<< orphan*/  Sgl_addition (unsigned int,unsigned int,unsigned int) ; 
 unsigned int Sgl_all (unsigned int) ; 
 int /*<<< orphan*/  Sgl_clear_signexponent (unsigned int) ; 
 int /*<<< orphan*/  Sgl_clear_signexponent_set_hidden (unsigned int) ; 
 int Sgl_exponent (unsigned int) ; 
 int Sgl_hidden (unsigned int) ; 
 int /*<<< orphan*/  Sgl_increment (unsigned int) ; 
 scalar_t__ Sgl_islessthan (unsigned int,unsigned int) ; 
 scalar_t__ Sgl_isnotzero (unsigned int) ; 
 scalar_t__ Sgl_isnotzero_mantissa (unsigned int) ; 
 scalar_t__ Sgl_isone_hiddenoverflow (unsigned int) ; 
 scalar_t__ Sgl_isone_sign (unsigned int) ; 
 scalar_t__ Sgl_isone_signaling (unsigned int) ; 
 scalar_t__ Sgl_iszero_exponentmantissa (unsigned int) ; 
 scalar_t__ Sgl_iszero_sign (unsigned int) ; 
 int /*<<< orphan*/  Sgl_leftshiftby1 (unsigned int) ; 
 int Sgl_lowmantissa (unsigned int) ; 
 int /*<<< orphan*/  Sgl_makequietnan (unsigned int) ; 
 int /*<<< orphan*/  Sgl_normalize (unsigned int,int) ; 
 int /*<<< orphan*/  Sgl_rightshiftby1 (unsigned int) ; 
 int /*<<< orphan*/  Sgl_set_exponent (unsigned int,int) ; 
 int /*<<< orphan*/  Sgl_set_quiet (unsigned int) ; 
 int /*<<< orphan*/  Sgl_setzero (unsigned int) ; 
 int /*<<< orphan*/  Sgl_subtract (unsigned int,unsigned int,unsigned int) ; 

unsigned int
sgl_fsqrt(
    sgl_floating_point *srcptr,
    unsigned int *nullptr,
    sgl_floating_point *dstptr,
    unsigned int *status)
{
	register unsigned int src, result;
	register int src_exponent;
	register unsigned int newbit, sum;
	register boolean guardbit = FALSE, even_exponent;

	src = *srcptr;
        /*
         * check source operand for NaN or infinity
         */
        if ((src_exponent = Sgl_exponent(src)) == SGL_INFINITY_EXPONENT) {
                /*
                 * is signaling NaN?
                 */
                if (Sgl_isone_signaling(src)) {
                        /* trap if INVALIDTRAP enabled */
                        if (Is_invalidtrap_enabled()) return(INVALIDEXCEPTION);
                        /* make NaN quiet */
                        Set_invalidflag();
                        Sgl_set_quiet(src);
                }
                /*
                 * Return quiet NaN or positive infinity.
		 *  Fall through to negative test if negative infinity.
                 */
		if (Sgl_iszero_sign(src) || Sgl_isnotzero_mantissa(src)) {
                	*dstptr = src;
                	return(NOEXCEPTION);
		}
        }

        /*
         * check for zero source operand
         */
	if (Sgl_iszero_exponentmantissa(src)) {
		*dstptr = src;
		return(NOEXCEPTION);
	}

        /*
         * check for negative source operand 
         */
	if (Sgl_isone_sign(src)) {
		/* trap if INVALIDTRAP enabled */
		if (Is_invalidtrap_enabled()) return(INVALIDEXCEPTION);
		/* make NaN quiet */
		Set_invalidflag();
		Sgl_makequietnan(src);
		*dstptr = src;
		return(NOEXCEPTION);
	}

	/*
	 * Generate result
	 */
	if (src_exponent > 0) {
		even_exponent = Sgl_hidden(src);
		Sgl_clear_signexponent_set_hidden(src);
	}
	else {
		/* normalize operand */
		Sgl_clear_signexponent(src);
		src_exponent++;
		Sgl_normalize(src,src_exponent);
		even_exponent = src_exponent & 1;
	}
	if (even_exponent) {
		/* exponent is even */
		/* Add comment here.  Explain why odd exponent needs correction */
		Sgl_leftshiftby1(src);
	}
	/*
	 * Add comment here.  Explain following algorithm.
	 * 
	 * Trust me, it works.
	 *
	 */
	Sgl_setzero(result);
	newbit = 1 << SGL_P;
	while (newbit && Sgl_isnotzero(src)) {
		Sgl_addition(result,newbit,sum);
		if(sum <= Sgl_all(src)) {
			/* update result */
			Sgl_addition(result,(newbit<<1),result);
			Sgl_subtract(src,sum,src);
		}
		Sgl_rightshiftby1(newbit);
		Sgl_leftshiftby1(src);
	}
	/* correct exponent for pre-shift */
	if (even_exponent) {
		Sgl_rightshiftby1(result);
	}

	/* check for inexact */
	if (Sgl_isnotzero(src)) {
		if (!even_exponent && Sgl_islessthan(result,src)) 
			Sgl_increment(result);
		guardbit = Sgl_lowmantissa(result);
		Sgl_rightshiftby1(result);

		/*  now round result  */
		switch (Rounding_mode()) {
		case ROUNDPLUS:
		     Sgl_increment(result);
		     break;
		case ROUNDNEAREST:
		     /* stickybit is always true, so guardbit 
		      * is enough to determine rounding */
		     if (guardbit) {
			Sgl_increment(result);
		     }
		     break;
		}
		/* increment result exponent by 1 if mantissa overflowed */
		if (Sgl_isone_hiddenoverflow(result)) src_exponent+=2;

		if (Is_inexacttrap_enabled()) {
			Sgl_set_exponent(result,
			 ((src_exponent-SGL_BIAS)>>1)+SGL_BIAS);
			*dstptr = result;
			return(INEXACTEXCEPTION);
		}
		else Set_inexactflag();
	}
	else {
		Sgl_rightshiftby1(result);
	}
	Sgl_set_exponent(result,((src_exponent-SGL_BIAS)>>1)+SGL_BIAS);
	*dstptr = result;
	return(NOEXCEPTION);
}