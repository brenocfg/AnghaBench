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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  n ;
struct TYPE_5__ {int type; int length; int* freqs; int* freqs1; int* cnts; int cntsum; int* symbols; int fshift; int* dectab; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static int update_model6_to_7(PixelModel3 *m)
{
    PixelModel3 n = {0};
    int c, d, e, f, k, p, length, i, j, index;
    uint16_t *freqs, *freqs1, *cnts;

    n.type = 7;

    length = m->length;
    freqs = n.freqs;
    freqs1 = n.freqs1;
    cnts = n.cnts;
    n.cntsum = m->cnts[length];
    for (i = 0; i < length; i++) {
        if (!m->cnts[i])
            continue;
        index = m->symbols[i];
        freqs[index] = m->freqs[2 * i];
        freqs1[index] = m->freqs[2 * i + 1];
        cnts[index] = m->cnts[i];
    }
    c = 1 << m->fshift;
    d = c - (c >> 1);
    for (j = 0, e = 0; j < 256; j++) {
        f = freqs[j];
        if (!f) {
            f = c;
            freqs[j] = c;
            freqs1[j] = e;
            cnts[j] = d;
        }
        p = (e + 127) >> 7;
        k = ((f + e - 1) >> 7) + 1;
        for (i = 0; i < k - p; i++)
            n.dectab[p + i] = j;
        e += f;
    }

    memcpy(m, &n, sizeof(n));

    return 0;
}