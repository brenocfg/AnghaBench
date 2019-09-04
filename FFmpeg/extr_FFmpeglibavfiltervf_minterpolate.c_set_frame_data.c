#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int width; int height; int** data; int* linesize; } ;
struct TYPE_15__ {TYPE_1__* avf; } ;
struct TYPE_14__ {int nb_planes; int log2_chroma_w; int log2_chroma_h; TYPE_6__* frames; TYPE_3__* pixel_refs; TYPE_2__* pixel_weights; TYPE_4__* pixel_mvs; } ;
struct TYPE_13__ {int** mvs; } ;
struct TYPE_12__ {int nb; int* refs; } ;
struct TYPE_11__ {int* weights; } ;
struct TYPE_10__ {int** data; int* linesize; } ;
typedef  TYPE_2__ PixelWeights ;
typedef  TYPE_3__ PixelRefs ;
typedef  TYPE_4__ PixelMVS ;
typedef  TYPE_5__ MIContext ;
typedef  TYPE_6__ Frame ;
typedef  TYPE_7__ AVFrame ;

/* Variables and functions */
 int ALPHA_MAX ; 
 int ROUNDED_DIV (int,int) ; 

__attribute__((used)) static void set_frame_data(MIContext *mi_ctx, int alpha, AVFrame *avf_out)
{
    int x, y, plane;

    for (plane = 0; plane < mi_ctx->nb_planes; plane++) {
        int width = avf_out->width;
        int height = avf_out->height;
        int chroma = plane == 1 || plane == 2;

        for (y = 0; y < height; y++)
            for (x = 0; x < width; x++) {
                int x_mv, y_mv;
                int weight_sum = 0;
                int i, val = 0;
                PixelMVS *pixel_mvs = &mi_ctx->pixel_mvs[x + y * avf_out->width];
                PixelWeights *pixel_weights = &mi_ctx->pixel_weights[x + y * avf_out->width];
                PixelRefs *pixel_refs = &mi_ctx->pixel_refs[x + y * avf_out->width];

                for (i = 0; i < pixel_refs->nb; i++)
                    weight_sum += pixel_weights->weights[i];

                if (!weight_sum || !pixel_refs->nb) {
                    pixel_weights->weights[0] = ALPHA_MAX - alpha;
                    pixel_refs->refs[0] = 1;
                    pixel_mvs->mvs[0][0] = 0;
                    pixel_mvs->mvs[0][1] = 0;
                    pixel_weights->weights[1] = alpha;
                    pixel_refs->refs[1] = 2;
                    pixel_mvs->mvs[1][0] = 0;
                    pixel_mvs->mvs[1][1] = 0;
                    pixel_refs->nb = 2;

                    weight_sum = ALPHA_MAX;
                }

                for (i = 0; i < pixel_refs->nb; i++) {
                    Frame *frame = &mi_ctx->frames[pixel_refs->refs[i]];
                    if (chroma) {
                        x_mv = (x >> mi_ctx->log2_chroma_w) + pixel_mvs->mvs[i][0] / (1 << mi_ctx->log2_chroma_w);
                        y_mv = (y >> mi_ctx->log2_chroma_h) + pixel_mvs->mvs[i][1] / (1 << mi_ctx->log2_chroma_h);
                    } else {
                        x_mv = x + pixel_mvs->mvs[i][0];
                        y_mv = y + pixel_mvs->mvs[i][1];
                    }

                    val += pixel_weights->weights[i] * frame->avf->data[plane][x_mv + y_mv * frame->avf->linesize[plane]];
                }

                val = ROUNDED_DIV(val, weight_sum);

                if (chroma)
                    avf_out->data[plane][(x >> mi_ctx->log2_chroma_w) + (y >> mi_ctx->log2_chroma_h) * avf_out->linesize[plane]] = val;
                else
                    avf_out->data[plane][x + y * avf_out->linesize[plane]] = val;
            }
    }
}