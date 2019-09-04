#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {TYPE_3__* priv; } ;
struct TYPE_13__ {TYPE_6__* src; } ;
struct TYPE_12__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_11__ {TYPE_2__** input_views; TYPE_1__* pix_desc; } ;
struct TYPE_10__ {int height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; int /*<<< orphan*/  linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_9__ {int log2_chroma_h; } ;
typedef  TYPE_3__ FramepackContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_image_copy (int /*<<< orphan*/ **,int*,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vertical_frame_pack(AVFilterLink *outlink,
                                AVFrame *out,
                                int interleaved)
{
    AVFilterContext *ctx = outlink->src;
    FramepackContext *s = ctx->priv;
    int i;

    for (i = 0; i < 2; i++) {
        const uint8_t *src[4];
        uint8_t *dst[4];
        int linesizes[4];
        int sub_h = s->input_views[i]->height >> s->pix_desc->log2_chroma_h;

        src[0] = s->input_views[i]->data[0];
        src[1] = s->input_views[i]->data[1];
        src[2] = s->input_views[i]->data[2];

        dst[0] = out->data[0] + i * out->linesize[0] *
                 (interleaved + s->input_views[i]->height * (1 - interleaved));
        dst[1] = out->data[1] + i * out->linesize[1] *
                 (interleaved + sub_h * (1 - interleaved));
        dst[2] = out->data[2] + i * out->linesize[2] *
                 (interleaved + sub_h * (1 - interleaved));

        linesizes[0] = out->linesize[0] +
                       interleaved * out->linesize[0];
        linesizes[1] = out->linesize[1] +
                       interleaved * out->linesize[1];
        linesizes[2] = out->linesize[2] +
                       interleaved * out->linesize[2];

        av_image_copy(dst, linesizes, src, s->input_views[i]->linesize,
                      s->input_views[i]->format,
                      s->input_views[i]->width,
                      s->input_views[i]->height);
    }
}