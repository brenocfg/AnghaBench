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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  n ;
struct TYPE_5__ {int type; int* freqs; int* cnts; int size; int* symbols; int cntsum; int* freqs1; int* dectab; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static int update_model3_to_7(PixelModel3 *m, uint8_t value)
{
    PixelModel3 n = {0};
    int c, d, e, f, g, q;

    n.type = 7;

    for (c = 0; c < 256; c++) {
        d = c;
        n.freqs[d] = 1;
        n.cnts[d] = 1;
    }

    for (c = m->size, d = (4096 - (256 - c)) / (c + 1) | 0, e = d - (d >> 1), g = 0; g < c;) {
        q = g++;
        q = m->symbols[q];
        n.freqs[q] = d;
        n.cnts[q] = e;
    }
    n.freqs[value] += d;
    n.cnts[value] += 16;
    for (d = c = n.cntsum = 0; 256 > d; d++) {
        e = d;
        n.cntsum += n.cnts[e];
        n.freqs1[e] = c;
        for (g = n.freqs[e], q = c + 128 - 1 >> 7, f = (c + g - 1 >> 7) + 1; q < f; q++) {
            n.dectab[q] = e;
        }
        c += g;
    }

    memcpy(m, &n, sizeof(n));

    return 0;
}