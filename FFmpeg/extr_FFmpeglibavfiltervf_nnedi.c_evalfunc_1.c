#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {float* input; float* temp; int* padded_stride; int* padded_width; int* padded_height; int* dst_stride; int* field; scalar_t__* dstp; scalar_t__* paddedp; } ;
struct TYPE_6__ {float** weights1; int qual; int asize; int nns; int xdia; int ydia; int nb_planes; int process_plane; int /*<<< orphan*/  max_value; int /*<<< orphan*/  (* wae5 ) (float*,int const,float*) ;int /*<<< orphan*/  (* expfunc ) (float*,int const) ;int /*<<< orphan*/  (* dot_prod ) (TYPE_1__*,float*,float*,float*,int const,int const,float*) ;int /*<<< orphan*/  (* extract ) (int const*,int const,int const,int const,float*,float*) ;} ;
typedef  TYPE_1__ NNEDIContext ;
typedef  TYPE_2__ FrameData ;

/* Variables and functions */
 int /*<<< orphan*/  FFMAX (int,int /*<<< orphan*/ ) ; 
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int const*,int const,int const,int const,float*,float*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,float*,float*,float*,int const,int const,float*) ; 
 int /*<<< orphan*/  stub3 (float*,int const) ; 
 int /*<<< orphan*/  stub4 (float*,int const,float*) ; 

__attribute__((used)) static void evalfunc_1(NNEDIContext *s, FrameData *frame_data)
{
    float *input = frame_data->input;
    float *temp = frame_data->temp;
    float **weights1 = s->weights1;
    const int qual = s->qual;
    const int asize = s->asize;
    const int nns = s->nns;
    const int xdia = s->xdia;
    const int xdiad2m1 = (xdia / 2) - 1;
    const int ydia = s->ydia;
    const float scale = 1.0f / (float)qual;
    int plane, y, x, i;

    for (plane = 0; plane < s->nb_planes; plane++) {
        const uint8_t *srcp = (const uint8_t *)frame_data->paddedp[plane];
        const int src_stride = frame_data->padded_stride[plane] / sizeof(uint8_t);

        const int width = frame_data->padded_width[plane];
        const int height = frame_data->padded_height[plane];

        uint8_t *dstp = (uint8_t *)frame_data->dstp[plane];
        const int dst_stride = frame_data->dst_stride[plane] / sizeof(uint8_t);

        const int ystart = frame_data->field[plane];
        const int ystop = height - 12;
        const uint8_t *srcpp;

        if (!(s->process_plane & (1 << plane)))
            continue;

        srcp += (ystart + 6) * src_stride;
        dstp += ystart * dst_stride - 32;
        srcpp = srcp - (ydia - 1) * src_stride - xdiad2m1;

        for (y = ystart; y < ystop; y += 2) {
            for (x = 32; x < width - 32; x++) {
                float mstd[4];

                if (dstp[x] != 255)
                    continue;

                s->extract((const uint8_t *)(srcpp + x), src_stride, xdia, ydia, mstd, input);
                for (i = 0; i < qual; i++) {
                    s->dot_prod(s, input, weights1[i], temp, nns * 2, asize, mstd + 2);
                    s->expfunc(temp, nns);
                    s->wae5(temp, nns, mstd);
                }

                dstp[x] = FFMIN(FFMAX((int)(mstd[3] * scale + 0.5f), 0), s->max_value);
            }
            srcpp += src_stride * 2;
            dstp += dst_stride * 2;
        }
    }
}