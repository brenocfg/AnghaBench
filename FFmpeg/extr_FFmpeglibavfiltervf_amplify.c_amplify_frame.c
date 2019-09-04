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
struct TYPE_7__ {int radius; int nb_inputs; float threshold; float tolerance; float factor; int llimit; int hlimit; int depth; int nb_planes; int* height; int planes; int* linesize; } ;
typedef  TYPE_2__ AmplifyContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AV_RN16 (int*) ; 
 int /*<<< orphan*/  FFABS (float) ; 
 int FFMIN (int /*<<< orphan*/ ,int const) ; 
 int av_clip_uint8 (int) ; 
 int av_clip_uintp2_c (int,int const) ; 
 int /*<<< orphan*/  av_image_copy_plane (int*,int const,int*,int const,int,int const) ; 
 float const fabsf (float) ; 

__attribute__((used)) static int amplify_frame(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    AmplifyContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame **in = td->in;
    AVFrame *out = td->out;
    const int radius = s->radius;
    const int nb_inputs = s->nb_inputs;
    const float threshold = s->threshold;
    const float tolerance = s->tolerance;
    const float factor = s->factor;
    const int llimit = s->llimit;
    const int hlimit = s->hlimit;
    const int depth = s->depth;
    int i, p, x, y;

    if (s->depth <= 8) {
        for (p = 0; p < s->nb_planes; p++) {
            const int slice_start = (s->height[p] * jobnr) / nb_jobs;
            const int slice_end = (s->height[p] * (jobnr+1)) / nb_jobs;
            uint8_t *dst = out->data[p] + slice_start * out->linesize[p];

            if (!((1 << p) & s->planes)) {
                av_image_copy_plane(dst, out->linesize[p],
                                    in[radius]->data[p] + slice_start * in[radius]->linesize[p],
                                    in[radius]->linesize[p],
                                    s->linesize[p], slice_end - slice_start);
                continue;
            }

            for (y = slice_start; y < slice_end; y++) {
                for (x = 0; x < s->linesize[p]; x++) {
                    int src = in[radius]->data[p][y * in[radius]->linesize[p] + x];
                    float diff, avg;
                    int sum = 0;

                    for (i = 0; i < nb_inputs; i++) {
                        sum += in[i]->data[p][y * in[i]->linesize[p] + x];
                    }

                    avg = sum / (float)nb_inputs;
                    diff = src - avg;
                    if (fabsf(diff) < threshold && fabsf(diff) > tolerance) {
                        int amp;
                        if (diff < 0) {
                            amp = -FFMIN(FFABS(diff * factor), llimit);
                        } else {
                            amp = FFMIN(FFABS(diff * factor), hlimit);
                        }
                        dst[x] = av_clip_uint8(src + amp);
                    } else {
                        dst[x] = src;
                    }
                }

                dst += out->linesize[p];
            }
        }
    } else {
        for (p = 0; p < s->nb_planes; p++) {
            const int slice_start = (s->height[p] * jobnr) / nb_jobs;
            const int slice_end = (s->height[p] * (jobnr+1)) / nb_jobs;
            uint16_t *dst = (uint16_t *)(out->data[p] + slice_start * out->linesize[p]);

            if (!((1 << p) & s->planes)) {
                av_image_copy_plane((uint8_t *)dst, out->linesize[p],
                                    in[radius]->data[p] + slice_start * in[radius]->linesize[p],
                                    in[radius]->linesize[p],
                                    s->linesize[p], slice_end - slice_start);
                continue;
            }

            for (y = slice_start; y < slice_end; y++) {
                for (x = 0; x < s->linesize[p] / 2; x++) {
                    int src = AV_RN16(in[radius]->data[p] + y * in[radius]->linesize[p] + x * 2);
                    float diff, avg;
                    int sum = 0;

                    for (i = 0; i < nb_inputs; i++) {
                        sum += AV_RN16(in[i]->data[p] + y * in[i]->linesize[p] + x * 2);
                    }

                    avg = sum / (float)nb_inputs;
                    diff = src - avg;

                    if (fabsf(diff) < threshold && fabsf(diff) > tolerance) {
                        int amp;
                        if (diff < 0) {
                            amp = -FFMIN(FFABS(diff * factor), llimit);
                        } else {
                            amp = FFMIN(FFABS(diff * factor), hlimit);
                        }
                        dst[x] = av_clip_uintp2_c(src + amp, depth);
                    } else {
                        dst[x] = src;
                    }
                }

                dst += out->linesize[p] / 2;
            }
        }
    }

    return 0;
}