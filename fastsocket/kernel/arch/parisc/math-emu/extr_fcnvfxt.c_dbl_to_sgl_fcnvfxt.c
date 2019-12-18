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
typedef  int /*<<< orphan*/  dbl_floating_point ;

/* Variables and functions */
 int DBL_BIAS ; 
 int Dbl_allp1 (unsigned int) ; 
 int /*<<< orphan*/  Dbl_clear_signexponent_set_hidden (unsigned int) ; 
 int /*<<< orphan*/  Dbl_copyfromptr (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int Dbl_exponent (unsigned int) ; 
 scalar_t__ Dbl_isinexact_to_fix (unsigned int,unsigned int,int) ; 
 scalar_t__ Dbl_isnotzero_exponentmantissa (unsigned int,unsigned int) ; 
 scalar_t__ Dbl_isone_sign (unsigned int) ; 
 scalar_t__ Dbl_isoverflow_to_int (int,unsigned int,unsigned int) ; 
 scalar_t__ Dbl_iszero_sign (unsigned int) ; 
 int INEXACTEXCEPTION ; 
 int INVALIDEXCEPTION ; 
 int /*<<< orphan*/  Int_from_dbl_mantissa (unsigned int,unsigned int,int) ; 
 scalar_t__ Is_inexacttrap_enabled () ; 
 scalar_t__ Is_invalidtrap_enabled () ; 
 int NOEXCEPTION ; 
 int SGL_FX_MAX_EXP ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Set_invalidflag () ; 

int
dbl_to_sgl_fcnvfxt(
			dbl_floating_point *srcptr,
			unsigned int *nullptr,
			int *dstptr,
			unsigned int *status)
{
	register unsigned int srcp1, srcp2, tempp1, tempp2;
	register int src_exponent, result;

	Dbl_copyfromptr(srcptr,srcp1,srcp2);
	src_exponent = Dbl_exponent(srcp1) - DBL_BIAS;

	/* 
	 * Test for overflow
	 */
	if (src_exponent > SGL_FX_MAX_EXP) {
		/* check for MININT */
		if (Dbl_isoverflow_to_int(src_exponent,srcp1,srcp2)) {
                        if (Dbl_iszero_sign(srcp1)) result = 0x7fffffff;
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
		tempp1 = srcp1;
		tempp2 = srcp2;
		Dbl_clear_signexponent_set_hidden(tempp1);
		Int_from_dbl_mantissa(tempp1,tempp2,src_exponent);
		if (Dbl_isone_sign(srcp1) && (src_exponent <= SGL_FX_MAX_EXP))
			result = -Dbl_allp1(tempp1);
		else result = Dbl_allp1(tempp1);
		*dstptr = result;

		/* check for inexact */
		if (Dbl_isinexact_to_fix(srcp1,srcp2,src_exponent)) {
			if (Is_inexacttrap_enabled()) return(INEXACTEXCEPTION);
			else Set_inexactflag();
		}
	}
	else {
		*dstptr = 0;

		/* check for inexact */
		if (Dbl_isnotzero_exponentmantissa(srcp1,srcp2)) {
			if (Is_inexacttrap_enabled()) return(INEXACTEXCEPTION);
			else Set_inexactflag();
		}
	}
	return(NOEXCEPTION);
}