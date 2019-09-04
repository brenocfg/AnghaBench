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
typedef  int uint16_t ;
struct TYPE_7__ {void* re; void* im; } ;
struct TYPE_6__ {int* revtab; void** tcos; void** tsin; int mdct_bits; int /*<<< orphan*/  (* fft_calc ) (TYPE_1__*,TYPE_2__*) ;} ;
typedef  void* FFTSample ;
typedef  TYPE_1__ FFTContext ;
typedef  TYPE_2__ FFTComplex ;

/* Variables and functions */
 int /*<<< orphan*/  CMUL (void*,void*,void* const,void* const,void* const,void* const) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_2__*) ; 

void ff_imdct_half_c(FFTContext *s, FFTSample *output, const FFTSample *input)
{
    int k, n8, n4, n2, n, j;
    const uint16_t *revtab = s->revtab;
    const FFTSample *tcos = s->tcos;
    const FFTSample *tsin = s->tsin;
    const FFTSample *in1, *in2;
    FFTComplex *z = (FFTComplex *)output;

    n = 1 << s->mdct_bits;
    n2 = n >> 1;
    n4 = n >> 2;
    n8 = n >> 3;

    /* pre rotation */
    in1 = input;
    in2 = input + n2 - 1;
    for(k = 0; k < n4; k++) {
        j=revtab[k];
        CMUL(z[j].re, z[j].im, *in2, *in1, tcos[k], tsin[k]);
        in1 += 2;
        in2 -= 2;
    }
    s->fft_calc(s, z);

    /* post rotation + reordering */
    for(k = 0; k < n8; k++) {
        FFTSample r0, i0, r1, i1;
        CMUL(r0, i1, z[n8-k-1].im, z[n8-k-1].re, tsin[n8-k-1], tcos[n8-k-1]);
        CMUL(r1, i0, z[n8+k  ].im, z[n8+k  ].re, tsin[n8+k  ], tcos[n8+k  ]);
        z[n8-k-1].re = r0;
        z[n8-k-1].im = i0;
        z[n8+k  ].re = r1;
        z[n8+k  ].im = i1;
    }
}