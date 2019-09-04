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
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static void filter_simple_low(int32_t *work_line,
                              uint8_t *in_lines_cur[2],
                              const int16_t *coef, int linesize)
{
    int i;

    for (i = 0; i < linesize; i++) {
        *work_line    = *in_lines_cur[0]++ * coef[0];
        *work_line++ += *in_lines_cur[1]++ * coef[1];
    }
}