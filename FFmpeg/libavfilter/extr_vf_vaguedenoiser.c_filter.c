#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  float uint8_t ;
typedef  float uint16_t ;
struct TYPE_8__ {int nb_planes; int* planeheight; int* planewidth; float* block; int nsteps; int planes; int bpc; int depth; int in; int** vlowsize; int** vhighsize; int** hlowsize; int** hhighsize; int /*<<< orphan*/  peak; int /*<<< orphan*/  out; int /*<<< orphan*/  tmp; int /*<<< orphan*/  percent; int /*<<< orphan*/  threshold; int /*<<< orphan*/  (* thresholding ) (float*,int const,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ VagueDenoiserContext ;
struct TYPE_9__ {float** data; int* linesize; } ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int NPAD ; 
 float av_clip (float const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float av_clip_uint8 (float const) ; 
 int /*<<< orphan*/  av_image_copy_plane (float*,int,float*,int,int,int) ; 
 int /*<<< orphan*/  copy (float*,...) ; 
 int /*<<< orphan*/  copyh (int /*<<< orphan*/ ,float*,int const,int const) ; 
 int /*<<< orphan*/  copyv (float*,int const,int,int const) ; 
 int /*<<< orphan*/  invert_step (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (float*,int const,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  transform_step (int,int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 

__attribute__((used)) static void filter(VagueDenoiserContext *s, AVFrame *in, AVFrame *out)
{
    int p, y, x, i, j;

    for (p = 0; p < s->nb_planes; p++) {
        const int height = s->planeheight[p];
        const int width = s->planewidth[p];
        const uint8_t *srcp8 = in->data[p];
        const uint16_t *srcp16 = (const uint16_t *)in->data[p];
        uint8_t *dstp8 = out->data[p];
        uint16_t *dstp16 = (uint16_t *)out->data[p];
        float *output = s->block;
        int h_low_size0 = width;
        int v_low_size0 = height;
        int nsteps_transform = s->nsteps;
        int nsteps_invert = s->nsteps;
        const float *input = s->block;

        if (!((1 << p) & s->planes)) {
            av_image_copy_plane(out->data[p], out->linesize[p], in->data[p], in->linesize[p],
                                s->planewidth[p] * s->bpc, s->planeheight[p]);
            continue;
        }

        if (s->depth <= 8) {
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++)
                    output[x] = srcp8[x];
                srcp8 += in->linesize[p];
                output += width;
            }
        } else {
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++)
                    output[x] = srcp16[x];
                srcp16 += in->linesize[p] / 2;
                output += width;
            }
        }

        while (nsteps_transform--) {
            int low_size = (h_low_size0 + 1) >> 1;
            float *input = s->block;
            for (j = 0; j < v_low_size0; j++) {
                copy(input, s->in + NPAD, h_low_size0);
                transform_step(s->in, s->out, h_low_size0, low_size, s);
                copy(s->out + NPAD, input, h_low_size0);
                input += width;
            }

            low_size = (v_low_size0 + 1) >> 1;
            input = s->block;
            for (j = 0; j < h_low_size0; j++) {
                copyv(input, width, s->in + NPAD, v_low_size0);
                transform_step(s->in, s->out, v_low_size0, low_size, s);
                copyh(s->out + NPAD, input, width, v_low_size0);
                input++;
            }

            h_low_size0 = (h_low_size0 + 1) >> 1;
            v_low_size0 = (v_low_size0 + 1) >> 1;
        }

        s->thresholding(s->block, width, height, width, s->threshold, s->percent, s->nsteps);

        while (nsteps_invert--) {
            const int idx = s->vlowsize[p][nsteps_invert]  + s->vhighsize[p][nsteps_invert];
            const int idx2 = s->hlowsize[p][nsteps_invert] + s->hhighsize[p][nsteps_invert];
            float * idx3 = s->block;
            for (i = 0; i < idx2; i++) {
                copyv(idx3, width, s->in + NPAD, idx);
                invert_step(s->in, s->out, s->tmp, idx, s);
                copyh(s->out + NPAD, idx3, width, idx);
                idx3++;
            }

            idx3 = s->block;
            for (i = 0; i < idx; i++) {
                copy(idx3, s->in + NPAD, idx2);
                invert_step(s->in, s->out, s->tmp, idx2, s);
                copy(s->out + NPAD, idx3, idx2);
                idx3 += width;
            }
        }

        if (s->depth <= 8) {
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++)
                    dstp8[x] = av_clip_uint8(input[x] + 0.5f);
                input += width;
                dstp8 += out->linesize[p];
            }
        } else {
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++)
                    dstp16[x] = av_clip(input[x] + 0.5f, 0, s->peak);
                input += width;
                dstp16 += out->linesize[p] / 2;
            }
        }
    }
}