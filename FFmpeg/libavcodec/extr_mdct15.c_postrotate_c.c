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
typedef  int ptrdiff_t ;
struct TYPE_5__ {int /*<<< orphan*/  re; int /*<<< orphan*/  im; } ;
typedef  TYPE_1__ FFTComplex ;

/* Variables and functions */
 int /*<<< orphan*/  CMUL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void postrotate_c(FFTComplex *out, FFTComplex *in, FFTComplex *exp,
                         int *lut, ptrdiff_t len8)
{
    int i;

    /* Reindex again, apply twiddles and output */
    for (i = 0; i < len8; i++) {
        const int i0 = len8 + i, i1 = len8 - i - 1;
        const int s0 = lut[i0], s1 = lut[i1];

        CMUL(out[i1].re, out[i0].im, in[s1].im, in[s1].re, exp[i1].im, exp[i1].re);
        CMUL(out[i0].re, out[i1].im, in[s0].im, in[s0].re, exp[i0].im, exp[i0].re);
    }
}