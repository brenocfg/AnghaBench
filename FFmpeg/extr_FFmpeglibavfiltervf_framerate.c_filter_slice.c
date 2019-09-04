#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {TYPE_2__* copy_src1; TYPE_1__* copy_src2; int /*<<< orphan*/  src2_factor; int /*<<< orphan*/  src1_factor; } ;
typedef  TYPE_4__ ThreadData ;
struct TYPE_13__ {TYPE_5__* priv; } ;
struct TYPE_12__ {int* line_size; int vsub; int blend_factor_max; int /*<<< orphan*/  (* blend ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;TYPE_3__* work; } ;
struct TYPE_10__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_9__ {int* linesize; int height; int /*<<< orphan*/ ** data; } ;
struct TYPE_8__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_5__ FrameRateContext ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int job, int nb_jobs)
{
    FrameRateContext *s = ctx->priv;
    ThreadData *td = arg;
    uint16_t src1_factor = td->src1_factor;
    uint16_t src2_factor = td->src2_factor;
    int plane;

    for (plane = 0; plane < 4 && td->copy_src1->data[plane] && td->copy_src2->data[plane]; plane++) {
        int cpy_line_width = s->line_size[plane];
        uint8_t *cpy_src1_data = td->copy_src1->data[plane];
        int cpy_src1_line_size = td->copy_src1->linesize[plane];
        uint8_t *cpy_src2_data = td->copy_src2->data[plane];
        int cpy_src2_line_size = td->copy_src2->linesize[plane];
        int cpy_src_h = (plane > 0 && plane < 3) ? (td->copy_src1->height >> s->vsub) : (td->copy_src1->height);
        uint8_t *cpy_dst_data = s->work->data[plane];
        int cpy_dst_line_size = s->work->linesize[plane];
        const int start = (cpy_src_h *  job   ) / nb_jobs;
        const int end   = (cpy_src_h * (job+1)) / nb_jobs;
        cpy_src1_data += start * cpy_src1_line_size;
        cpy_src2_data += start * cpy_src2_line_size;
        cpy_dst_data += start * cpy_dst_line_size;

        s->blend(cpy_src1_data, cpy_src1_line_size,
                 cpy_src2_data, cpy_src2_line_size,
                 cpy_dst_data,  cpy_dst_line_size,
                 cpy_line_width, end - start,
                 src1_factor, src2_factor, s->blend_factor_max >> 1);
    }

    return 0;
}