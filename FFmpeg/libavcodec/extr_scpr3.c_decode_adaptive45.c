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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int maxpos; int* freqs; int size; int* symbols; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */
 int add_symbol (TYPE_1__*,int,int,int*,int) ; 
 int /*<<< orphan*/  rescale (TYPE_1__*,int*) ; 

__attribute__((used)) static int decode_adaptive45(PixelModel3 *m, int rccode, uint32_t *value,
                             uint16_t *a, uint16_t *b, uint32_t *c, int max)
{
    uint32_t q, g, maxpos, d, e = *c, totfr = *c;
    int ret;

    for (d = 0; e <= 2048; d++)
        e <<= 1;
    maxpos = m->maxpos;
    rccode >>= d;
    *c = m->freqs[maxpos];
    m->freqs[maxpos] += 4096 - e >> d;

    for (q = 0, g = 0, e = 0; q < m->size; q++) {
        uint32_t f = m->symbols[q];
        uint32_t p = e + f - g;
        uint32_t k = m->freqs[q];

        if (rccode < p) {
            *value = rccode - e + g;
            *b = rccode << d;
            *a = 1 << d;
            m->freqs[maxpos] = *c;
            ret = add_symbol(m, q, *value, &totfr, max);
            *c = totfr;
            return ret;
        }

        if (p + k > rccode) {
            *value = f;
            e += *value - g;
            *b = e << d;
            *a = k << d;
            m->freqs[maxpos] = *c;
            m->freqs[q] += 50;
            totfr += 50;
            if ((q != maxpos) && (m->freqs[q] > m->freqs[maxpos]))
                m->maxpos = q;
            if (totfr + 50 > 4096)
                rescale(m, &totfr);
            *c = totfr;
            return 1;
        }

        e += f - g + k;
        g = f + 1;
    }

    m->freqs[maxpos] = *c;
    *value = g + rccode - e;
    *b = rccode << d;
    *a = 1 << d;
    ret = add_symbol(m, q, *value, &totfr, max);
    *c = totfr;
    return ret;
}