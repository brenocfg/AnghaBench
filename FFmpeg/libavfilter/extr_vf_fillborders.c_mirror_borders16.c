#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int* linesize; scalar_t__* data; } ;
struct TYPE_7__ {int nb_planes; int* planeheight; int* planewidth; TYPE_1__* borders; } ;
struct TYPE_6__ {int top; int bottom; int left; int right; } ;
typedef  TYPE_2__ FillBordersContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mirror_borders16(FillBordersContext *s, AVFrame *frame)
{
    int p, y, x;

    for (p = 0; p < s->nb_planes; p++) {
        uint16_t *ptr = (uint16_t *)frame->data[p];
        int linesize = frame->linesize[p] / 2;

        for (y = s->borders[p].top; y < s->planeheight[p] - s->borders[p].bottom; y++) {
            for (x = 0; x < s->borders[p].left; x++) {
                ptr[y * linesize + x] = ptr[y * linesize + s->borders[p].left * 2 - 1 - x];
            }

            for (x = 0; x < s->borders[p].right; x++) {
                ptr[y * linesize + s->planewidth[p] - s->borders[p].right + x] =
                    ptr[y * linesize + s->planewidth[p] - s->borders[p].right - 1 - x];
            }
        }

        for (y = 0; y < s->borders[p].top; y++) {
            memcpy(ptr + y * linesize,
                   ptr + (s->borders[p].top * 2 - 1 - y) * linesize,
                   s->planewidth[p] * 2);
        }

        for (y = 0; y < s->borders[p].bottom; y++) {
            memcpy(ptr + (s->planeheight[p] - s->borders[p].bottom + y) * linesize,
                   ptr + (s->planeheight[p] - s->borders[p].bottom - 1 - y) * linesize,
                   s->planewidth[p] * 2);
        }
    }
}