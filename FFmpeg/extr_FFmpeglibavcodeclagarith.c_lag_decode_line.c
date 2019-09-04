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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  lag_rac ;
struct TYPE_3__ {int zeros; scalar_t__ zeros_rem; } ;
typedef  TYPE_1__ LagarithContext ;

/* Variables and functions */
 int FFMIN (scalar_t__,int) ; 
 scalar_t__ lag_calc_zero_run (int) ; 
 void* lag_get_rac (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lag_decode_line(LagarithContext *l, lag_rac *rac,
                           uint8_t *dst, int width, int stride,
                           int esc_count)
{
    int i = 0;
    int ret = 0;

    if (!esc_count)
        esc_count = -1;

    /* Output any zeros remaining from the previous run */
handle_zeros:
    if (l->zeros_rem) {
        int count = FFMIN(l->zeros_rem, width - i);
        memset(dst + i, 0, count);
        i += count;
        l->zeros_rem -= count;
    }

    while (i < width) {
        dst[i] = lag_get_rac(rac);
        ret++;

        if (dst[i])
            l->zeros = 0;
        else
            l->zeros++;

        i++;
        if (l->zeros == esc_count) {
            int index = lag_get_rac(rac);
            ret++;

            l->zeros = 0;

            l->zeros_rem = lag_calc_zero_run(index);
            goto handle_zeros;
        }
    }
    return ret;
}