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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int vc1_filter_line (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void vc1_loop_filter(uint8_t *src, int step, int stride,
                                   int len, int pq)
{
    int i;
    int filt3;

    for (i = 0; i < len; i += 4) {
        filt3 = vc1_filter_line(src + 2 * step, stride, pq);
        if (filt3) {
            vc1_filter_line(src + 0 * step, stride, pq);
            vc1_filter_line(src + 1 * step, stride, pq);
            vc1_filter_line(src + 3 * step, stride, pq);
        }
        src += step * 4;
    }
}