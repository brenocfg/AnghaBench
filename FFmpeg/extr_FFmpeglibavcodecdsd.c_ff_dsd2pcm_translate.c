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
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_3__ {unsigned int pos; unsigned char* buf; } ;
typedef  TYPE_1__ DSDContext ;

/* Variables and functions */
 unsigned int CTABLES ; 
 unsigned int FIFOMASK ; 
 scalar_t__** ctables ; 
 unsigned char const* ff_reverse ; 

void ff_dsd2pcm_translate(DSDContext* s, size_t samples, int lsbf,
                          const unsigned char *src, ptrdiff_t src_stride,
                          float *dst, ptrdiff_t dst_stride)
{
    unsigned pos, i;
    unsigned char* p;
    double sum;

    pos = s->pos;

    while (samples-- > 0) {
        s->buf[pos] = lsbf ? ff_reverse[*src] : *src;
        src += src_stride;

        p = s->buf + ((pos - CTABLES) & FIFOMASK);
        *p = ff_reverse[*p];

        sum = 0.0;
        for (i = 0; i < CTABLES; i++) {
            unsigned char a = s->buf[(pos                   - i) & FIFOMASK];
            unsigned char b = s->buf[(pos - (CTABLES*2 - 1) + i) & FIFOMASK];
            sum += ctables[i][a] + ctables[i][b];
        }

        *dst = (float)sum;
        dst += dst_stride;

        pos = (pos + 1) & FIFOMASK;
    }

    s->pos = pos;
}