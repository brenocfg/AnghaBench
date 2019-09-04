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
struct TYPE_3__ {int size; int length; int* symbols; int* freqs; int* cnts; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */

__attribute__((used)) static int add_dec(PixelModel3 *m, int sym, int f1, int f2)
{
    int size;

    if (m->size >= 40 || m->size >= m->length)
        return -1;

    size = m->size;
    m->symbols[size] = sym;
    m->freqs[2 * size] = f1;
    m->freqs[2 * size + 1] = f2;
    m->cnts[size] = f1 - (f1 >> 1);
    m->size++;

    return size;
}