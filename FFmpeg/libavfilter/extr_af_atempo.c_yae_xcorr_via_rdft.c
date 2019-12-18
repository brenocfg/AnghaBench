#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int re; int im; } ;
typedef  int /*<<< orphan*/  RDFTContext ;
typedef  int /*<<< orphan*/  FFTSample ;
typedef  TYPE_1__ FFTComplex ;

/* Variables and functions */
 int /*<<< orphan*/  av_rdft_calc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void yae_xcorr_via_rdft(FFTSample *xcorr,
                               RDFTContext *complex_to_real,
                               const FFTComplex *xa,
                               const FFTComplex *xb,
                               const int window)
{
    FFTComplex *xc = (FFTComplex *)xcorr;
    int i;

    // NOTE: first element requires special care -- Given Y = rDFT(X),
    // Im(Y[0]) and Im(Y[N/2]) are always zero, therefore av_rdft_calc
    // stores Re(Y[N/2]) in place of Im(Y[0]).

    xc->re = xa->re * xb->re;
    xc->im = xa->im * xb->im;
    xa++;
    xb++;
    xc++;

    for (i = 1; i < window; i++, xa++, xb++, xc++) {
        xc->re = (xa->re * xb->re + xa->im * xb->im);
        xc->im = (xa->im * xb->re - xa->re * xb->im);
    }

    // apply inverse rDFT:
    av_rdft_calc(complex_to_real, xcorr);
}