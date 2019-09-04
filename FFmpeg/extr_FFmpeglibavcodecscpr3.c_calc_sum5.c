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
struct TYPE_3__ {int size; int* freqs; int cntsum; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */

__attribute__((used)) static void calc_sum5(PixelModel3 *m)
{
    uint32_t a;

    a = 256 - m->size;
    for (int b = 0; b < m->size; b++)
        a += m->freqs[b];
    m->cntsum = a;
}