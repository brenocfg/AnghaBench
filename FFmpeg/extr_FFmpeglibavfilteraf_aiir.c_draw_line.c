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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WL32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int FFABS (int) ; 

__attribute__((used)) static void draw_line(AVFrame *out, int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = FFABS(x1-x0);
    int dy = FFABS(y1-y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy) / 2, e2;

    for (;;) {
        AV_WL32(out->data[0] + y0 * out->linesize[0] + x0 * 4, color);

        if (x0 == x1 && y0 == y1)
            break;

        e2 = err;

        if (e2 >-dx) {
            err -= dy;
            x0--;
        }

        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}