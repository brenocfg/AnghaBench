#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 scalar_t__ FFABS (int) ; 

int ff_idet_filter_line_c_16bit(const uint16_t *a, const uint16_t *b, const uint16_t *c, int w)
{
    int x;
    int ret=0;

    for(x=0; x<w; x++){
        int v = (*a++ + *c++) - 2 * *b++;
        ret += FFABS(v);
    }

    return ret;
}