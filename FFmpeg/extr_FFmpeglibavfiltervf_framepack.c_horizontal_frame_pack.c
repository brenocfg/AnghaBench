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
typedef  int uint8_t ;
struct TYPE_14__ {TYPE_3__* priv; } ;
struct TYPE_13__ {TYPE_6__* src; } ;
struct TYPE_12__ {int** data; int width; int height; int* linesize; } ;
struct TYPE_11__ {TYPE_2__** input_views; TYPE_1__* pix_desc; } ;
struct TYPE_10__ {int** data; int* linesize; int width; int /*<<< orphan*/  height; int /*<<< orphan*/  format; } ;
struct TYPE_9__ {int nb_components; int log2_chroma_w; int log2_chroma_h; } ;
typedef  TYPE_3__ FramepackContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int) ; 
 size_t LEFT ; 
 size_t RIGHT ; 
 int /*<<< orphan*/  av_image_copy (int**,int*,int const**,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void horizontal_frame_pack(AVFilterLink *outlink,
                                  AVFrame *out,
                                  int interleaved)
{
    AVFilterContext *ctx = outlink->src;
    FramepackContext *s = ctx->priv;
    int i, plane;

    if (interleaved) {
        const uint8_t *leftp  = s->input_views[LEFT]->data[0];
        const uint8_t *rightp = s->input_views[RIGHT]->data[0];
        uint8_t *dstp         = out->data[0];
        int length = out->width / 2;
        int lines  = out->height;

        for (plane = 0; plane < s->pix_desc->nb_components; plane++) {
            if (plane == 1 || plane == 2) {
                length = AV_CEIL_RSHIFT(out->width / 2, s->pix_desc->log2_chroma_w);
                lines  = AV_CEIL_RSHIFT(out->height,    s->pix_desc->log2_chroma_h);
            }
            for (i = 0; i < lines; i++) {
                int j;
                leftp  = s->input_views[LEFT]->data[plane] +
                         s->input_views[LEFT]->linesize[plane] * i;
                rightp = s->input_views[RIGHT]->data[plane] +
                         s->input_views[RIGHT]->linesize[plane] * i;
                dstp   = out->data[plane] + out->linesize[plane] * i;
                for (j = 0; j < length; j++) {
                    // interpolate chroma as necessary
                    if ((s->pix_desc->log2_chroma_w ||
                         s->pix_desc->log2_chroma_h) &&
                        (plane == 1 || plane == 2)) {
                        *dstp++ = (*leftp + *rightp) / 2;
                        *dstp++ = (*leftp + *rightp) / 2;
                    } else {
                        *dstp++ = *leftp;
                        *dstp++ = *rightp;
                    }
                    leftp += 1;
                    rightp += 1;
                }
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            const uint8_t *src[4];
            uint8_t *dst[4];
            int sub_w = s->input_views[i]->width >> s->pix_desc->log2_chroma_w;

            src[0] = s->input_views[i]->data[0];
            src[1] = s->input_views[i]->data[1];
            src[2] = s->input_views[i]->data[2];

            dst[0] = out->data[0] + i * s->input_views[i]->width;
            dst[1] = out->data[1] + i * sub_w;
            dst[2] = out->data[2] + i * sub_w;

            av_image_copy(dst, out->linesize, src, s->input_views[i]->linesize,
                          s->input_views[i]->format,
                          s->input_views[i]->width,
                          s->input_views[i]->height);
        }
    }
}