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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

__attribute__((used)) static void draw_sample_cline_rgba_full(uint8_t *buf, int height, int linesize,
                                         int16_t *prev_y,
                                         const uint8_t color[4], int h)
{
    int k;
    const int start = (height - h) / 2;
    const int end   = start + h;
    for (k = start; k < end; k++) {
        buf[k * linesize + 0] = color[0];
        buf[k * linesize + 1] = color[1];
        buf[k * linesize + 2] = color[2];
        buf[k * linesize + 3] = color[3];
    }
}