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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_11__ {int* in_linesize; int in_ss_h; int* out_linesize; int out_ss_h; TYPE_2__* out; TYPE_1__* in; } ;
typedef  TYPE_4__ ThreadData ;
struct TYPE_13__ {TYPE_5__* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* multiply3x3 ) (int /*<<< orphan*/ **,int,int,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int rgb_stride; scalar_t__ dither; int /*<<< orphan*/ * yuv_offset; int /*<<< orphan*/  rgb2yuv_coeffs; int /*<<< orphan*/  (* rgb2yuv ) (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dither_scratch; int /*<<< orphan*/  (* rgb2yuv_fsb ) (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  delin_lut; int /*<<< orphan*/  lrgb2lrgb_coeffs; TYPE_3__ dsp; int /*<<< orphan*/  lrgb2lrgb_passthrough; int /*<<< orphan*/  lin_lut; int /*<<< orphan*/  rgb2rgb_passthrough; int /*<<< orphan*/  yuv2rgb_coeffs; int /*<<< orphan*/  (* yuv2rgb ) (int /*<<< orphan*/ **,int,int /*<<< orphan*/ **,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  yuv2yuv_coeffs; int /*<<< orphan*/  (* yuv2yuv ) (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ yuv2yuv_fastmode; int /*<<< orphan*/ ** rgb; } ;
struct TYPE_9__ {int /*<<< orphan*/ ** data; } ;
struct TYPE_8__ {int height; int width; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_5__ ColorSpaceContext ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ DITHER_FSB ; 
 int /*<<< orphan*/  apply_lut (int /*<<< orphan*/ **,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ **,int,int /*<<< orphan*/ **,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ **,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int convert(AVFilterContext *ctx, void *data, int job_nr, int n_jobs)
{
    const ThreadData *td = data;
    ColorSpaceContext *s = ctx->priv;
    uint8_t *in_data[3], *out_data[3];
    int16_t *rgb[3];
    int h_in = (td->in->height + 1) >> 1;
    int h1 = 2 * (job_nr * h_in / n_jobs), h2 = 2 * ((job_nr + 1) * h_in / n_jobs);
    int w = td->in->width, h = h2 - h1;

    in_data[0]  = td->in->data[0]  + td->in_linesize[0]  *  h1;
    in_data[1]  = td->in->data[1]  + td->in_linesize[1]  * (h1 >> td->in_ss_h);
    in_data[2]  = td->in->data[2]  + td->in_linesize[2]  * (h1 >> td->in_ss_h);
    out_data[0] = td->out->data[0] + td->out_linesize[0] *  h1;
    out_data[1] = td->out->data[1] + td->out_linesize[1] * (h1 >> td->out_ss_h);
    out_data[2] = td->out->data[2] + td->out_linesize[2] * (h1 >> td->out_ss_h);
    rgb[0]      = s->rgb[0]        + s->rgb_stride       *  h1;
    rgb[1]      = s->rgb[1]        + s->rgb_stride       *  h1;
    rgb[2]      = s->rgb[2]        + s->rgb_stride       *  h1;

    // FIXME for simd, also make sure we do pictures with negative stride
    // top-down so we don't overwrite lines with padding of data before it
    // in the same buffer (same as swscale)

    if (s->yuv2yuv_fastmode) {
        // FIXME possibly use a fast mode in case only the y range changes?
        // since in that case, only the diagonal entries in yuv2yuv_coeffs[]
        // are non-zero
        s->yuv2yuv(out_data, td->out_linesize, in_data, td->in_linesize, w, h,
                   s->yuv2yuv_coeffs, s->yuv_offset);
    } else {
        // FIXME maybe (for caching efficiency) do pipeline per-line instead of
        // full buffer per function? (Or, since yuv2rgb requires 2 lines: per
        // 2 lines, for yuv420.)
        /*
         * General design:
         * - yuv2rgb converts from whatever range the input was ([16-235/240] or
         *   [0,255] or the 10/12bpp equivalents thereof) to an integer version
         *   of RGB in psuedo-restricted 15+sign bits. That means that the float
         *   range [0.0,1.0] is in [0,28762], and the remainder of the int16_t
         *   range is used for overflow/underflow outside the representable
         *   range of this RGB type. rgb2yuv is the exact opposite.
         * - gamma correction is done using a LUT since that appears to work
         *   fairly fast.
         * - If the input is chroma-subsampled (420/422), the yuv2rgb conversion
         *   (or rgb2yuv conversion) uses nearest-neighbour sampling to read
         *   read chroma pixels at luma resolution. If you want some more fancy
         *   filter, you can use swscale to convert to yuv444p.
         * - all coefficients are 14bit (so in the [-2.0,2.0] range).
         */
        s->yuv2rgb(rgb, s->rgb_stride, in_data, td->in_linesize, w, h,
                   s->yuv2rgb_coeffs, s->yuv_offset[0]);
        if (!s->rgb2rgb_passthrough) {
            apply_lut(rgb, s->rgb_stride, w, h, s->lin_lut);
            if (!s->lrgb2lrgb_passthrough)
                s->dsp.multiply3x3(rgb, s->rgb_stride, w, h, s->lrgb2lrgb_coeffs);
            apply_lut(rgb, s->rgb_stride, w, h, s->delin_lut);
        }
        if (s->dither == DITHER_FSB) {
            s->rgb2yuv_fsb(out_data, td->out_linesize, rgb, s->rgb_stride, w, h,
                           s->rgb2yuv_coeffs, s->yuv_offset[1], s->dither_scratch);
        } else {
            s->rgb2yuv(out_data, td->out_linesize, rgb, s->rgb_stride, w, h,
                       s->rgb2yuv_coeffs, s->yuv_offset[1]);
        }
    }

    return 0;
}