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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

__attribute__((used)) static void draw_sample_cline_gray(uint8_t *buf, int height, int linesize,
                                   int16_t *prev_y,
                                   const uint8_t color[4], int h)
{
    int k;
    const int start = (height - h) / 2;
    const int end   = start + h;
    for (k = start; k < end; k++)
        buf[k * linesize] += color[0];
}