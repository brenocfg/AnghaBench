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

/* Variables and functions */
 int INEXACTEXCEPTION ; 
 int INVALIDEXCEPTION ; 
 int /*<<< orphan*/  Int_from_sgl_mantissa (unsigned int,int) ; 
 scalar_t__ Is_inexacttrap_enabled () ; 
 scalar_t__ Is_invalidtrap_enabled () ; 
 int NOEXCEPTION ; 
 int SGL_BIAS ; 
 int SGL_FX_MAX_EXP ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Set_invalidflag () ; 
 int Sgl_all (unsigned int) ; 
 int /*<<< orphan*/  Sgl_clear_signexponent_set_hidden (unsigned int) ; 
 int Sgl_exponent (unsigned int) ; 
 scalar_t__ Sgl_isinexact_to_fix (unsigned int,int) ; 
 scalar_t__ Sgl_isnotzero_exponentmantissa (unsigned int) ; 
 scalar_t__ Sgl_isnotzero_mantissa (unsigned int) ; 
 scalar_t__ Sgl_isone_sign (unsigned int) ; 
 scalar_t__ Sgl_iszero_sign (unsigned int) ; 

int
sgl_to_sgl_fcnvfxt(
		    sgl_floating_point *srcptr,
		    unsigned int *nullptr,
		    int *dstptr,
		    unsigned int *status)
{
	register unsigned int src, temp;
	register int src_exponent, result;

	src = *srcptr;
	src_exponent = Sgl_exponent(src) - SGL_BIAS;

	/* 
	 * Test for overflow
	 */
	if (src_exponent > SGL_FX_MAX_EXP) {
		/* check for MININT */
		if ((src_exponent > SGL_FX_MAX_EXP + 1) || 
		Sgl_isnotzero_mantissa(src) || Sgl_iszero_sign(src)) {
                        if (Sgl_iszero_sign(src)) result = 0x7fffffff;
                        else result = 0x80000000; 

	                if (Is_invalidtrap_enabled()) {
                            return(INVALIDEXCEPTION);
                        }
                        Set_invalidflag();
			*dstptr = result;
			return(NOEXCEPTION);
		}
	}
	/*
	 * Generate result
	 */
	if (src_exponent >= 0) {
		temp = src;
		Sgl_clear_signexponent_set_hidden(temp);
		Int_from_sgl_mantissa(temp,src_exponent);
		if (Sgl_isone_sign(src))  result = -Sgl_all(temp);
		else result = Sgl_all(temp);
		*dstptr = result;

		/* check for inexact */
		if (Sgl_isinexact_to_fix(src,src_exponent)) {
			if (Is_inexacttrap_enabled()) return(INEXACTEXCEPTION);
			else Set_inexactflag();
		}
	}
	else {
		*dstptr = 0;

		/* check for inexact */
		if (Sgl_isnotzero_exponentmantissa(src)) {
			if (Is_inexacttrap_enabled()) return(INEXACTEXCEPTION);
			else Set_inexactflag();
		}
	}
	return(NOEXCEPTION);
}