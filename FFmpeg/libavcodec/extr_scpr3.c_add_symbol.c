#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int size; int* freqs; int maxpos; int /*<<< orphan*/ * symbols; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */
 int /*<<< orphan*/  rescale (TYPE_1__*,int*) ; 

__attribute__((used)) static int add_symbol(PixelModel3 *m, int index, uint32_t symbol, int *totfr, int max)
{
    if (m->size == max)
        return 0;

    for (int c = m->size - 1; c >= index; c--) {
        m->symbols[c + 1] = m->symbols[c];
        m->freqs[c + 1] = m->freqs[c];
    }

    m->symbols[index] = symbol;
    m->freqs[index] = 50;
    m->size++;

    if (m->maxpos >= index)
        m->maxpos++;

    *totfr += 50;
    if (*totfr + 50 > 4096)
        rescale(m, totfr);

    return 1;
}