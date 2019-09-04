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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {int nb_planes; int* planeheight; int /*<<< orphan*/ * planewidth; TYPE_1__* borders; int /*<<< orphan*/ * fill; } ;
struct TYPE_6__ {int top; int bottom; int /*<<< orphan*/ * right; int /*<<< orphan*/  left; } ;
typedef  TYPE_2__ FillBordersContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fixed_borders8(FillBordersContext *s, AVFrame *frame)
{
    int p, y;

    for (p = 0; p < s->nb_planes; p++) {
        uint8_t *ptr = frame->data[p];
        uint8_t fill = s->fill[p];
        int linesize = frame->linesize[p];

        for (y = s->borders[p].top; y < s->planeheight[p] - s->borders[p].bottom; y++) {
            memset(ptr + y * linesize, fill, s->borders[p].left);
            memset(ptr + y * linesize + s->planewidth[p] - s->borders[p].right, fill,
                   s->borders[p].right);
        }

        for (y = 0; y < s->borders[p].top; y++) {
            memset(ptr + y * linesize, fill, s->planewidth[p]);
        }

        for (y = s->planeheight[p] - s->borders[p].bottom; y < s->planeheight[p]; y++) {
            memset(ptr + y * linesize, fill, s->planewidth[p]);
        }
    }
}