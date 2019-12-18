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
struct TYPE_3__ {int length; int size; int fshift; int* cnts; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */

__attribute__((used)) static void calc_sum(PixelModel3 *m)
{
    uint32_t a;
    int len;

    len = m->length;
    a = 256 - m->size << (m->fshift > 0 ? m->fshift - 1 : 0);
    for (int c = 0; c < len; c++)
        a += m->cnts[c];
    m->cnts[len] = a;
}