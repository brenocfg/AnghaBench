#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_3__ {int order; int coeff_bits; int coeff_shift; } ;
typedef  int /*<<< orphan*/  MLPEncodeContext ;
typedef  TYPE_1__ FilterParams ;

/* Variables and functions */
 int FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INT_MAX ; 
 int INT_MIN ; 
 int /*<<< orphan*/  number_sbits (int) ; 

__attribute__((used)) static void code_filter_coeffs(MLPEncodeContext *ctx, FilterParams *fp, int32_t *fcoeff)
{
    int min = INT_MAX, max = INT_MIN;
    int bits, shift;
    int coeff_mask = 0;
    int order;

    for (order = 0; order < fp->order; order++) {
        int coeff = fcoeff[order];

        if (coeff < min)
            min = coeff;
        if (coeff > max)
            max = coeff;

        coeff_mask |= coeff;
    }

    bits = FFMAX(number_sbits(min), number_sbits(max));

    for (shift = 0; shift < 7 && bits + shift < 16 && !(coeff_mask & (1<<shift)); shift++);

    fp->coeff_bits  = bits;
    fp->coeff_shift = shift;
}