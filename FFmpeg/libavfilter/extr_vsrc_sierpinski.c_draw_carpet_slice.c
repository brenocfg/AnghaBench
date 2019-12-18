#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * priv; } ;
struct TYPE_4__ {int width; int height; int const* linesize; int /*<<< orphan*/ ** data; } ;
typedef  int /*<<< orphan*/  SierpinskiContext ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ fill_sierpinski (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int draw_carpet_slice(AVFilterContext *ctx, void *arg, int job, int nb_jobs)
{
    SierpinskiContext *s = ctx->priv;
    AVFrame *frame = arg;
    const int width  = frame->width;
    const int height = frame->height;
    const int start = (height *  job   ) / nb_jobs;
    const int end   = (height * (job+1)) / nb_jobs;
    uint8_t *dst = frame->data[0] + start * frame->linesize[0];

    for (int y = start; y < end; y++) {
        for (int x = 0; x < width; x++) {
            if (fill_sierpinski(s, x, y)) {
                AV_WL32(&dst[x*4], 0x00000000);
            } else {
                AV_WL32(&dst[x*4], 0xFFFFFFFF);
            }
        }

        dst += frame->linesize[0];
    }

    return 0;
}