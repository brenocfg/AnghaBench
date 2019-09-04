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
typedef  int uint8_t ;
struct TYPE_3__ {int x1; int y1; int x2; int y2; } ;
typedef  TYPE_1__ FFBoundingBox ;

/* Variables and functions */

int ff_calculate_bounding_box(FFBoundingBox *bbox,
                              const uint8_t *data, int linesize, int w, int h,
                              int min_val)
{
    int x, y;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    const uint8_t *line;

    /* left bound */
    for (start_x = 0; start_x < w; start_x++)
        for (y = 0; y < h; y++)
            if ((data[y * linesize + start_x] > min_val))
                goto outl;
outl:
    if (start_x == w) /* no points found */
        return 0;

    /* right bound */
    for (end_x = w - 1; end_x >= start_x; end_x--)
        for (y = 0; y < h; y++)
            if ((data[y * linesize + end_x] > min_val))
                goto outr;
outr:

    /* top bound */
    line = data;
    for (start_y = 0; start_y < h; start_y++) {
        for (x = 0; x < w; x++)
            if (line[x] > min_val)
                goto outt;
        line += linesize;
    }
outt:

    /* bottom bound */
    line = data + (h-1)*linesize;
    for (end_y = h - 1; end_y >= start_y; end_y--) {
        for (x = 0; x < w; x++)
            if (line[x] > min_val)
                goto outb;
        line -= linesize;
    }
outb:

    bbox->x1 = start_x;
    bbox->y1 = start_y;
    bbox->x2 = end_x;
    bbox->y2 = end_y;
    return 1;
}