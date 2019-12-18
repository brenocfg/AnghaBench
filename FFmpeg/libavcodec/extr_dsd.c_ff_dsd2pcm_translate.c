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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {unsigned int pos; size_t* buf; } ;
typedef  TYPE_1__ DSDContext ;

/* Variables and functions */
 unsigned int CTABLES ; 
 unsigned int FIFOMASK ; 
 int FIFOSIZE ; 
 scalar_t__** ctables ; 
 size_t const* ff_reverse ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 

void ff_dsd2pcm_translate(DSDContext* s, size_t samples, int lsbf,
                          const uint8_t *src, ptrdiff_t src_stride,
                          float *dst, ptrdiff_t dst_stride)
{
    uint8_t buf[FIFOSIZE];
    unsigned pos, i;
    uint8_t* p;
    double sum;

    pos = s->pos;

    memcpy(buf, s->buf, sizeof(buf));

    while (samples-- > 0) {
        buf[pos] = lsbf ? ff_reverse[*src] : *src;
        src += src_stride;

        p = buf + ((pos - CTABLES) & FIFOMASK);
        *p = ff_reverse[*p];

        sum = 0.0;
        for (i = 0; i < CTABLES; i++) {
            uint8_t a = buf[(pos                   - i) & FIFOMASK];
            uint8_t b = buf[(pos - (CTABLES*2 - 1) + i) & FIFOMASK];
            sum += ctables[i][a] + ctables[i][b];
        }

        *dst = (float)sum;
        dst += dst_stride;

        pos = (pos + 1) & FIFOMASK;
    }

    s->pos = pos;
    memcpy(s->buf, buf, sizeof(buf));
}