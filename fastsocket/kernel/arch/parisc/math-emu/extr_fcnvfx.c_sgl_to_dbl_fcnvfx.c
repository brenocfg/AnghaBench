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
typedef  int /*<<< orphan*/  dbl_integer ;
typedef  scalar_t__ boolean ;

/* Variables and functions */
 int DBL_FX_MAX_EXP ; 
 int /*<<< orphan*/  Dint_copytoptr (int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Dint_decrement (int,unsigned int) ; 
 int /*<<< orphan*/  Dint_from_sgl_mantissa (unsigned int,int,int,unsigned int) ; 
 int /*<<< orphan*/  Dint_increment (int,unsigned int) ; 
 int /*<<< orphan*/  Dint_isone_lowp2 (unsigned int) ; 
 int /*<<< orphan*/  Dint_set_minint (int,unsigned int) ; 
 int /*<<< orphan*/  Dint_setone_sign (int,unsigned int) ; 
 int /*<<< orphan*/  Dint_setzero (int,unsigned int) ; 
 scalar_t__ FALSE ; 
 int INEXACTEXCEPTION ; 
 int INVALIDEXCEPTION ; 
 scalar_t__ Is_inexacttrap_enabled () ; 
 scalar_t__ Is_invalidtrap_enabled () ; 
 int NOEXCEPTION ; 
#define  ROUNDMINUS 130 
#define  ROUNDNEAREST 129 
#define  ROUNDPLUS 128 
 int Rounding_mode () ; 
 int SGL_BIAS ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Set_invalidflag () ; 
 int /*<<< orphan*/  Sgl_clear_signexponent_set_hidden (unsigned int) ; 
 int Sgl_exponent (unsigned int) ; 
 scalar_t__ Sgl_isinexact_to_fix (unsigned int,int) ; 
 scalar_t__ Sgl_isnotzero_exponentmantissa (unsigned int) ; 
 scalar_t__ Sgl_isnotzero_mantissa (unsigned int) ; 
 int /*<<< orphan*/  Sgl_isone_roundbit (unsigned int,int) ; 
 scalar_t__ Sgl_isone_sign (unsigned int) ; 
 int /*<<< orphan*/  Sgl_isone_stickybit (unsigned int,int) ; 
 scalar_t__ Sgl_iszero_sign (unsigned int) ; 
 scalar_t__ TRUE ; 

int
sgl_to_dbl_fcnvfx(
		sgl_floating_point *srcptr,
		unsigned int *nullptr,
		dbl_integer *dstptr,
		unsigned int *status)
{
	register int src_exponent, resultp1;
	register unsigned int src, temp, resultp2;
	register boolean inexact = FALSE;

	src = *srcptr;
	src_exponent = Sgl_exponent(src) - SGL_BIAS;

	/* 
	 * Test for overflow
	 */
	if (src_exponent > DBL_FX_MAX_EXP) {
		/* check for MININT */
		if ((src_exponent > DBL_FX_MAX_EXP + 1) || 
		Sgl_isnotzero_mantissa(src) || Sgl_iszero_sign(src)) {
                        if (Sgl_iszero_sign(src)) {
                              resultp1 = 0x7fffffff;
			      resultp2 = 0xffffffff;
			}
                        else {
			    resultp1 = 0x80000000; 
			    resultp2 = 0;
			}
	                if (Is_invalidtrap_enabled()) {
                            return(INVALIDEXCEPTION);
                        }
                        Set_invalidflag();
    		        Dint_copytoptr(resultp1,resultp2,dstptr);
			return(NOEXCEPTION);
		}
		Dint_set_minint(resultp1,resultp2);
		Dint_copytoptr(resultp1,resultp2,dstptr);
		return(NOEXCEPTION);
	}
	/*
	 * Generate result
	 */
	if (src_exponent >= 0) {
		temp = src;
		Sgl_clear_signexponent_set_hidden(temp);
		Dint_from_sgl_mantissa(temp,src_exponent,resultp1,resultp2);
		if (Sgl_isone_sign(src)) {
			Dint_setone_sign(resultp1,resultp2);
		}

		/* check for inexact */
		if (Sgl_isinexact_to_fix(src,src_exponent)) {
			inexact = TRUE;
                        /*  round result  */
                        switch (Rounding_mode()) {
                        case ROUNDPLUS:
                             if (Sgl_iszero_sign(src)) {
				Dint_increment(resultp1,resultp2);
			     }
                             break;
                        case ROUNDMINUS:
                             if (Sgl_isone_sign(src)) {
				Dint_decrement(resultp1,resultp2);
			     }
                             break;
                        case ROUNDNEAREST:
                             if (Sgl_isone_roundbit(src,src_exponent))
                                if (Sgl_isone_stickybit(src,src_exponent) || 
				(Dint_isone_lowp2(resultp2)))
				   if (Sgl_iszero_sign(src)) {
				      Dint_increment(resultp1,resultp2);
				   }
                                   else {
				      Dint_decrement(resultp1,resultp2);
				   }
                        }
                }
        }
	else {
		Dint_setzero(resultp1,resultp2);

		/* check for inexact */
		if (Sgl_isnotzero_exponentmantissa(src)) {
			inexact = TRUE;
                        /*  round result  */
                        switch (Rounding_mode()) {
                        case ROUNDPLUS:
                             if (Sgl_iszero_sign(src)) {
				Dint_increment(resultp1,resultp2);
			     }
                             break;
                        case ROUNDMINUS:
                             if (Sgl_isone_sign(src)) {
				Dint_decrement(resultp1,resultp2);
			     }
                             break;
                        case ROUNDNEAREST:
                             if (src_exponent == -1)
                                if (Sgl_isnotzero_mantissa(src))
                                   if (Sgl_iszero_sign(src)) {
				      Dint_increment(resultp1,resultp2);
				   }
                                   else {
				      Dint_decrement(resultp1,resultp2);
				   }
			}
		}
	}
	Dint_copytoptr(resultp1,resultp2,dstptr);
	if (inexact) {
		if (Is_inexacttrap_enabled()) return(INEXACTEXCEPTION);
		else Set_inexactflag();
	}
	return(NOEXCEPTION);
}