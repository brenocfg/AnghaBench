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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_6__ {TYPE_3__* out; TYPE_3__** in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {int** data; int const* linesize; } ;
struct TYPE_7__ {int depth; int nb_planes; int* height; int* linesize; int nb_inputs; int* weights; int wfactor; int /*<<< orphan*/  max; } ;
typedef  TYPE_2__ MixContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AV_RN16 (int*) ; 
 int av_clip (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_clip_uint8 (int) ; 

__attribute__((used)) static int mix_frames(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    MixContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame **in = td->in;
    AVFrame *out = td->out;
    int i, p, x, y;

    if (s->depth <= 8) {
        for (p = 0; p < s->nb_planes; p++) {
            const int slice_start = (s->height[p] * jobnr) / nb_jobs;
            const int slice_end = (s->height[p] * (jobnr+1)) / nb_jobs;
            uint8_t *dst = out->data[p] + slice_start * out->linesize[p];

            for (y = slice_start; y < slice_end; y++) {
                for (x = 0; x < s->linesize[p]; x++) {
                    int val = 0;

                    for (i = 0; i < s->nb_inputs; i++) {
                        uint8_t src = in[i]->data[p][y * in[i]->linesize[p] + x];

                        val += src * s->weights[i];
                    }

                    dst[x] = av_clip_uint8(val * s->wfactor);
                }

                dst += out->linesize[p];
            }
        }
    } else {
        for (p = 0; p < s->nb_planes; p++) {
            const int slice_start = (s->height[p] * jobnr) / nb_jobs;
            const int slice_end = (s->height[p] * (jobnr+1)) / nb_jobs;
            uint16_t *dst = (uint16_t *)(out->data[p] + slice_start * out->linesize[p]);

            for (y = slice_start; y < slice_end; y++) {
                for (x = 0; x < s->linesize[p] / 2; x++) {
                    int val = 0;

                    for (i = 0; i < s->nb_inputs; i++) {
                        uint16_t src = AV_RN16(in[i]->data[p] + y * in[i]->linesize[p] + x * 2);

                        val += src * s->weights[i];
                    }

                    dst[x] = av_clip(val * s->wfactor, 0, s->max);
                }

                dst += out->linesize[p] / 2;
            }
        }
    }

    return 0;
}