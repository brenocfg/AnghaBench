#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int re; int im; } ;
typedef  TYPE_1__ FFTComplex ;

/* Variables and functions */

__attribute__((used)) static inline void fft5(FFTComplex *out, FFTComplex *in, FFTComplex exptab[2])
{
    FFTComplex z0[4], t[6];

    t[0].re = in[3].re + in[12].re;
    t[0].im = in[3].im + in[12].im;
    t[1].im = in[3].re - in[12].re;
    t[1].re = in[3].im - in[12].im;
    t[2].re = in[6].re + in[ 9].re;
    t[2].im = in[6].im + in[ 9].im;
    t[3].im = in[6].re - in[ 9].re;
    t[3].re = in[6].im - in[ 9].im;

    out[0].re = in[0].re + in[3].re + in[6].re + in[9].re + in[12].re;
    out[0].im = in[0].im + in[3].im + in[6].im + in[9].im + in[12].im;

    t[4].re = exptab[0].re * t[2].re - exptab[1].re * t[0].re;
    t[4].im = exptab[0].re * t[2].im - exptab[1].re * t[0].im;
    t[0].re = exptab[0].re * t[0].re - exptab[1].re * t[2].re;
    t[0].im = exptab[0].re * t[0].im - exptab[1].re * t[2].im;
    t[5].re = exptab[0].im * t[3].re - exptab[1].im * t[1].re;
    t[5].im = exptab[0].im * t[3].im - exptab[1].im * t[1].im;
    t[1].re = exptab[0].im * t[1].re + exptab[1].im * t[3].re;
    t[1].im = exptab[0].im * t[1].im + exptab[1].im * t[3].im;

    z0[0].re = t[0].re - t[1].re;
    z0[0].im = t[0].im - t[1].im;
    z0[1].re = t[4].re + t[5].re;
    z0[1].im = t[4].im + t[5].im;

    z0[2].re = t[4].re - t[5].re;
    z0[2].im = t[4].im - t[5].im;
    z0[3].re = t[0].re + t[1].re;
    z0[3].im = t[0].im + t[1].im;

    out[1].re = in[0].re + z0[3].re;
    out[1].im = in[0].im + z0[0].im;
    out[2].re = in[0].re + z0[2].re;
    out[2].im = in[0].im + z0[1].im;
    out[3].re = in[0].re + z0[1].re;
    out[3].im = in[0].im + z0[2].im;
    out[4].re = in[0].re + z0[0].re;
    out[4].im = in[0].im + z0[3].im;
}