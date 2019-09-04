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
 int FFABS (int) ; 

__attribute__((used)) static void draw_line(uint16_t *const pixels, int linesize,
                      int x0, int y0, int x1, int y1,
                      int w, int h,
                      const uint16_t *const rgbcolor)
{
    int dx  = FFABS(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy  = FFABS(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;) {
        pixels[y0 * linesize + x0 * 4 + 0] = rgbcolor[0];
        pixels[y0 * linesize + x0 * 4 + 1] = rgbcolor[1];
        pixels[y0 * linesize + x0 * 4 + 2] = rgbcolor[2];
        pixels[y0 * linesize + x0 * 4 + 3] = rgbcolor[3];

        if (x0 == x1 && y0 == y1)
            break;

        e2 = err;

        if (e2 >-dx) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}