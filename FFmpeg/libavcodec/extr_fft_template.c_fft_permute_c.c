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
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_3__ {size_t* revtab; size_t* revtab32; int nbits; void** tmp_buf; } ;
typedef  TYPE_1__ FFTContext ;
typedef  void* FFTComplex ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void**,void**,int) ; 

__attribute__((used)) static void fft_permute_c(FFTContext *s, FFTComplex *z)
{
    int j, np;
    const uint16_t *revtab = s->revtab;
    const uint32_t *revtab32 = s->revtab32;
    np = 1 << s->nbits;
    /* TODO: handle split-radix permute in a more optimal way, probably in-place */
    if (revtab) {
        for(j=0;j<np;j++) s->tmp_buf[revtab[j]] = z[j];
    } else
        for(j=0;j<np;j++) s->tmp_buf[revtab32[j]] = z[j];

    memcpy(z, s->tmp_buf, np * sizeof(FFTComplex));
}