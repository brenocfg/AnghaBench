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
struct G722Band {int* diff_mem; int* zero_mem; int s_zero; } ;

/* Variables and functions */

__attribute__((used)) static inline void s_zero(int cur_diff, struct G722Band *band)
{
    int s_zero = 0;

    #define ACCUM(k, x, d) do { \
            int tmp = x; \
            band->zero_mem[k] = ((band->zero_mem[k] * 255) >> 8) + \
               d*((band->diff_mem[k]^cur_diff) < 0 ? -128 : 128); \
            band->diff_mem[k] = tmp; \
            s_zero += (tmp * band->zero_mem[k]) >> 15; \
        } while (0)
    if (cur_diff) {
        ACCUM(5, band->diff_mem[4], 1);
        ACCUM(4, band->diff_mem[3], 1);
        ACCUM(3, band->diff_mem[2], 1);
        ACCUM(2, band->diff_mem[1], 1);
        ACCUM(1, band->diff_mem[0], 1);
        ACCUM(0, cur_diff * 2, 1);
    } else {
        ACCUM(5, band->diff_mem[4], 0);
        ACCUM(4, band->diff_mem[3], 0);
        ACCUM(3, band->diff_mem[2], 0);
        ACCUM(2, band->diff_mem[1], 0);
        ACCUM(1, band->diff_mem[0], 0);
        ACCUM(0, cur_diff * 2, 0);
    }
    #undef ACCUM
    band->s_zero = s_zero;
}