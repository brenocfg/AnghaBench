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
struct FFIIRFilterState {int dummy; } ;
struct FFIIRFilterCoeffs {int dummy; } ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  FF_FILTER_MODE_LOWPASS ; 
 int /*<<< orphan*/  FF_FILTER_TYPE_BUTTERWORTH ; 
 int /*<<< orphan*/  FILT_ORDER ; 
 double INT16_MAX ; 
 double M_PI ; 
 int SIZE ; 
 int /*<<< orphan*/  ff_iir_filter (struct FFIIRFilterCoeffs*,struct FFIIRFilterState*,int,int*,int,int*,int) ; 
 int /*<<< orphan*/  ff_iir_filter_free_coeffsp (struct FFIIRFilterCoeffs**) ; 
 int /*<<< orphan*/  ff_iir_filter_free_statep (struct FFIIRFilterState**) ; 
 struct FFIIRFilterCoeffs* ff_iir_filter_init_coeffs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,double,double) ; 
 struct FFIIRFilterState* ff_iir_filter_init_state (int /*<<< orphan*/ ) ; 
 int lrint (double) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 double sin (double) ; 

int main(void)
{
    struct FFIIRFilterCoeffs *fcoeffs = NULL;
    struct FFIIRFilterState  *fstate  = NULL;
    float cutoff_coeff = 0.4;
    int16_t x[SIZE], y[SIZE];
    int i;

    fcoeffs = ff_iir_filter_init_coeffs(NULL, FF_FILTER_TYPE_BUTTERWORTH,
                                        FF_FILTER_MODE_LOWPASS, FILT_ORDER,
                                        cutoff_coeff, 0.0, 0.0);
    fstate  = ff_iir_filter_init_state(FILT_ORDER);

    for (i = 0; i < SIZE; i++)
        x[i] = lrint(0.75 * INT16_MAX * sin(0.5 * M_PI * i * i / SIZE));

    ff_iir_filter(fcoeffs, fstate, SIZE, x, 1, y, 1);

    for (i = 0; i < SIZE; i++)
        printf("%6d %6d\n", x[i], y[i]);

    ff_iir_filter_free_coeffsp(&fcoeffs);
    ff_iir_filter_free_statep(&fstate);
    return 0;
}