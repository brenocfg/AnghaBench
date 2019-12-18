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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int fshift; int size; size_t* symbols; int* cnts; int* freqs; size_t length; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */

__attribute__((used)) static void rescale_dec(PixelModel3 *m)
{
    uint16_t cnts[256] = {0};
    uint16_t freqs[512] = {0};
    int b, c, e, g;
    uint32_t a;

    for (a = 1 << (0 < m->fshift ? m->fshift - 1 : 0), b = 0; b < 256; b++)
        cnts[b] = a;

    for (a = 0, b = m->size; a < b; a++)
        cnts[m->symbols[a]] = m->cnts[a];

    for (b = a = 0; b < 256; b++) {
        freqs[2 * b] = cnts[b];
        freqs[2 * b + 1] = a;
        a += cnts[b];
    }

    if (m->fshift > 0)
        m->fshift--;

    a = 256 - m->size << (0 < m->fshift ? m->fshift - 1 : 0);
    for (b = 0, c = m->size; b < c; b++) {
        m->cnts[b] -= m->cnts[b] >> 1;
        a = a + m->cnts[b];
        e = m->symbols[b];
        g = freqs[2 * e + 1];
        m->freqs[2 * b] = freqs[2 * e];
        m->freqs[2 * b + 1] = g;
    }
    m->cnts[m->length] = a;
}