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
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int height; int width; int* linesize; int** data; } ;
struct TYPE_6__ {int* co; } ;
typedef  TYPE_1__ ColorkeyContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int do_colorkey_pixel (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static int do_colorhold_slice(AVFilterContext *avctx, void *arg, int jobnr, int nb_jobs)
{
    AVFrame *frame = arg;

    const int slice_start = (frame->height * jobnr) / nb_jobs;
    const int slice_end = (frame->height * (jobnr + 1)) / nb_jobs;

    ColorkeyContext *ctx = avctx->priv;

    int x, y;

    for (y = slice_start; y < slice_end; ++y) {
        for (x = 0; x < frame->width; ++x) {
            int o, t, r, g, b;

            o = frame->linesize[0] * y + x * 4;
            r = frame->data[0][o + ctx->co[0]];
            g = frame->data[0][o + ctx->co[1]];
            b = frame->data[0][o + ctx->co[2]];

            t = do_colorkey_pixel(ctx, r, g, b);

            if (t > 0) {
                int a = (r + g + b) / 3;
                int rt = 255 - t;

                frame->data[0][o + ctx->co[0]] = (a * t + r * rt + 127) >> 8;
                frame->data[0][o + ctx->co[1]] = (a * t + g * rt + 127) >> 8;
                frame->data[0][o + ctx->co[2]] = (a * t + b * rt + 127) >> 8;
            }
        }
    }

    return 0;
}