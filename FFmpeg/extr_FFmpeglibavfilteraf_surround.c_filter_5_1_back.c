#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {int buf_size; int /*<<< orphan*/  (* upmix_5_1 ) (TYPE_3__*,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,int) ;TYPE_1__* input; } ;
struct TYPE_6__ {scalar_t__* extended_data; } ;
typedef  TYPE_2__ AudioSurroundContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 float FFDIFFSIGN (float,float) ; 
 float M_PI ; 
 float atan2f (float,float) ; 
 float fabsf (float) ; 
 float hypotf (float,float) ; 
 int /*<<< orphan*/  stereo_position (float,float,float*,float*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,int) ; 

__attribute__((used)) static void filter_5_1_back(AVFilterContext *ctx)
{
    AudioSurroundContext *s = ctx->priv;
    float *srcl, *srcr, *srcc, *srclfe, *srcbl, *srcbr;
    int n;

    srcl = (float *)s->input->extended_data[0];
    srcr = (float *)s->input->extended_data[1];
    srcc = (float *)s->input->extended_data[2];
    srclfe = (float *)s->input->extended_data[3];
    srcbl = (float *)s->input->extended_data[4];
    srcbr = (float *)s->input->extended_data[5];

    for (n = 0; n < s->buf_size; n++) {
        float fl_re = srcl[2 * n], fr_re = srcr[2 * n];
        float fl_im = srcl[2 * n + 1], fr_im = srcr[2 * n + 1];
        float c_re = srcc[2 * n], c_im = srcc[2 * n + 1];
        float lfe_re = srclfe[2 * n], lfe_im = srclfe[2 * n + 1];
        float bl_re = srcbl[2 * n], bl_im = srcbl[2 * n + 1];
        float br_re = srcbr[2 * n], br_im = srcbr[2 * n + 1];
        float fl_mag = hypotf(fl_re, fl_im);
        float fr_mag = hypotf(fr_re, fr_im);
        float fl_phase = atan2f(fl_im, fl_re);
        float fr_phase = atan2f(fr_im, fr_re);
        float bl_mag = hypotf(bl_re, bl_im);
        float br_mag = hypotf(br_re, br_im);
        float bl_phase = atan2f(bl_im, bl_re);
        float br_phase = atan2f(br_im, br_re);
        float phase_difl = fabsf(fl_phase - bl_phase);
        float phase_difr = fabsf(fr_phase - br_phase);
        float magl_sum = fl_mag + bl_mag;
        float magr_sum = fr_mag + br_mag;
        float mag_difl = magl_sum < 0.000001 ? FFDIFFSIGN(fl_mag, bl_mag) : (fl_mag - bl_mag) / magl_sum;
        float mag_difr = magr_sum < 0.000001 ? FFDIFFSIGN(fr_mag, br_mag) : (fr_mag - br_mag) / magr_sum;
        float mag_totall = hypotf(fl_mag, bl_mag);
        float mag_totalr = hypotf(fr_mag, br_mag);
        float sl_phase = atan2f(fl_im + bl_im, fl_re + bl_re);
        float sr_phase = atan2f(fr_im + br_im, fr_re + br_re);
        float xl, yl;
        float xr, yr;

        if (phase_difl > M_PI)
            phase_difl = 2 * M_PI - phase_difl;

        if (phase_difr > M_PI)
            phase_difr = 2 * M_PI - phase_difr;

        stereo_position(mag_difl, phase_difl, &xl, &yl);
        stereo_position(mag_difr, phase_difr, &xr, &yr);

        s->upmix_5_1(ctx, c_re, c_im, lfe_re, lfe_im,
                     mag_totall, mag_totalr,
                     fl_phase, fr_phase,
                     bl_phase, br_phase,
                     sl_phase, sr_phase,
                     xl, yl, xr, yr, n);
    }
}