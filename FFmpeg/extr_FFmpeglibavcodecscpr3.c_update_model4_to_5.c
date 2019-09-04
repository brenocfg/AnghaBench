#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  n ;
struct TYPE_7__ {int type; int size; scalar_t__* symbols; int* freqs; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */
 int /*<<< orphan*/  calc_sum5 (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  rescale (TYPE_1__*,int*) ; 

__attribute__((used)) static int update_model4_to_5(PixelModel3 *m, uint32_t value)
{
    PixelModel3 n = {0};
    int c, e, g, totfr;

    n.type = 5;

    for (c = 0, e = 0; c < m->size && m->symbols[c] < value; c++) {
        n.symbols[c] = m->symbols[c];
        e += n.freqs[c] = m->freqs[c];
    }

    g = c;
    n.symbols[g] = value;
    e += n.freqs[g++] = 50;
    for (; c < m->size; g++, c++) {
        n.symbols[g] = m->symbols[c];
        e += n.freqs[g] = m->freqs[c];
    }
    n.size = m->size + 1;
    if (e > 4096)
        rescale(&n, &totfr);

    calc_sum5(&n);

    memcpy(m, &n, sizeof(n));

    return 0;
}