#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int** data; int* linesize; } ;
struct TYPE_10__ {int* rgba; TYPE_1__* comp; } ;
struct TYPE_9__ {int nb_planes; int* pixelstep; int* vsub; int* hsub; } ;
struct TYPE_8__ {int* u8; } ;
typedef  TYPE_2__ FFDrawContext ;
typedef  TYPE_3__ FFDrawColor ;
typedef  TYPE_4__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static void pick_color8(FFDrawContext *draw, FFDrawColor *color, AVFrame *in, int x, int y, int *value)
{
    int p, i;

    color->rgba[3] = 255;
    for (p = 0; p < draw->nb_planes; p++) {
        if (draw->nb_planes == 1) {
            for (i = 0; i < 4; i++) {
                value[i] = in->data[0][y * in->linesize[0] + x * draw->pixelstep[0] + i];
                color->comp[0].u8[i] = value[i];
            }
        } else {
            value[p] = in->data[p][(y >> draw->vsub[p]) * in->linesize[p] + (x >> draw->hsub[p])];
            color->comp[p].u8[0] = value[p];
        }
    }
}