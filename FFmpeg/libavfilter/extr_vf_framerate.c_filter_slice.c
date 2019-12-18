#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  src2_factor; int /*<<< orphan*/  src1_factor; TYPE_3__* copy_src2; TYPE_3__* copy_src1; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {int const* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {int* height; int blend_factor_max; int /*<<< orphan*/ * line_size; int /*<<< orphan*/  (* blend ) (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;TYPE_3__* work; } ;
typedef  TYPE_2__ FrameRateContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int job, int nb_jobs)
{
    FrameRateContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *work = s->work;
    AVFrame *src1 = td->copy_src1;
    AVFrame *src2 = td->copy_src2;
    uint16_t src1_factor = td->src1_factor;
    uint16_t src2_factor = td->src2_factor;
    int plane;

    for (plane = 0; plane < 4 && src1->data[plane] && src2->data[plane]; plane++) {
        const int start = (s->height[plane] *  job   ) / nb_jobs;
        const int end   = (s->height[plane] * (job+1)) / nb_jobs;
        uint8_t *src1_data = src1->data[plane] + start * src1->linesize[plane];
        uint8_t *src2_data = src2->data[plane] + start * src2->linesize[plane];
        uint8_t *dst_data  = work->data[plane] + start * work->linesize[plane];

        s->blend(src1_data, src1->linesize[plane], src2_data, src2->linesize[plane],
                 dst_data,  work->linesize[plane], s->line_size[plane], end - start,
                 src1_factor, src2_factor, s->blend_factor_max >> 1);
    }

    return 0;
}