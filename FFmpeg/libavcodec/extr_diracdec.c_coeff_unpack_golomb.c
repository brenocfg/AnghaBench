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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 unsigned int FFSIGN (int) ; 
 int dirac_get_se_golomb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int coeff_unpack_golomb(GetBitContext *gb, int qfactor, int qoffset)
{
    int coeff = dirac_get_se_golomb(gb);
    const unsigned sign = FFSIGN(coeff);
    if (coeff)
        coeff = sign*((sign * coeff * qfactor + qoffset) >> 2);
    return coeff;
}