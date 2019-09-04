#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_5__ {TYPE_1__* plane; } ;
struct TYPE_4__ {int available_lines; scalar_t__* line; } ;
typedef  TYPE_2__ SwsSlice ;

/* Variables and functions */

__attribute__((used)) static void fill_ones(SwsSlice *s, int n, int is16bit)
{
    int i;
    for (i = 0; i < 4; ++i) {
        int j;
        int size = s->plane[i].available_lines;
        for (j = 0; j < size; ++j) {
            int k;
            int end = is16bit ? n>>1: n;
            // fill also one extra element
            end += 1;
            if (is16bit)
                for (k = 0; k < end; ++k)
                    ((int32_t*)(s->plane[i].line[j]))[k] = 1<<18;
            else
                for (k = 0; k < end; ++k)
                    ((int16_t*)(s->plane[i].line[j]))[k] = 1<<14;
        }
    }
}