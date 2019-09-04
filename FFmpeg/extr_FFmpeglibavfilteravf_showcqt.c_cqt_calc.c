#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int len; int* val; int start; } ;
struct TYPE_6__ {int re; int im; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int FFTSample ;
typedef  TYPE_1__ FFTComplex ;
typedef  TYPE_2__ Coeffs ;

/* Variables and functions */

__attribute__((used)) static void cqt_calc(FFTComplex *dst, const FFTComplex *src, const Coeffs *coeffs,
                     int len, int fft_len)
{
    int k, x, i, j;
    for (k = 0; k < len; k++) {
        FFTComplex l, r, a = {0,0}, b = {0,0};

        for (x = 0; x < coeffs[k].len; x++) {
            FFTSample u = coeffs[k].val[x];
            i = coeffs[k].start + x;
            j = fft_len - i;
            a.re += u * src[i].re;
            a.im += u * src[i].im;
            b.re += u * src[j].re;
            b.im += u * src[j].im;
        }

        /* separate left and right, (and multiply by 2.0) */
        l.re = a.re + b.re;
        l.im = a.im - b.im;
        r.re = b.im + a.im;
        r.im = b.re - a.re;
        dst[k].re = l.re * l.re + l.im * l.im;
        dst[k].im = r.re * r.re + r.im * r.im;
    }
}