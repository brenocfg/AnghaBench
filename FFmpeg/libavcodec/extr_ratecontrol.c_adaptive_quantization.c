#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* mb_mean; int /*<<< orphan*/ * mb_var; int /*<<< orphan*/ * mc_mb_var; } ;
struct TYPE_7__ {float border_masking; float* cplx_tab; float* bits_tab; int mb_width; int mb_height; int mb_num; int* mb_index2xy; int const mb_stride; int* mb_type; int mpv_flags; int* lambda_table; TYPE_2__ current_picture; TYPE_1__* avctx; } ;
struct TYPE_5__ {double lumi_masking; double dark_masking; float temporal_cplx_masking; float spatial_cplx_masking; float p_masking; int mb_lmin; int mb_lmax; } ;
typedef  TYPE_2__ Picture ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int CANDIDATE_MB_TYPE_INTRA ; 
 float FFMAX (float,float) ; 
 int FF_MPV_FLAG_NAQ ; 
 float pow (float,float const) ; 
 float sqrt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adaptive_quantization(MpegEncContext *s, double q)
{
    int i;
    const float lumi_masking         = s->avctx->lumi_masking / (128.0 * 128.0);
    const float dark_masking         = s->avctx->dark_masking / (128.0 * 128.0);
    const float temp_cplx_masking    = s->avctx->temporal_cplx_masking;
    const float spatial_cplx_masking = s->avctx->spatial_cplx_masking;
    const float p_masking            = s->avctx->p_masking;
    const float border_masking       = s->border_masking;
    float bits_sum                   = 0.0;
    float cplx_sum                   = 0.0;
    float *cplx_tab                  = s->cplx_tab;
    float *bits_tab                  = s->bits_tab;
    const int qmin                   = s->avctx->mb_lmin;
    const int qmax                   = s->avctx->mb_lmax;
    Picture *const pic               = &s->current_picture;
    const int mb_width               = s->mb_width;
    const int mb_height              = s->mb_height;

    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        float temp_cplx = sqrt(pic->mc_mb_var[mb_xy]); // FIXME merge in pow()
        float spat_cplx = sqrt(pic->mb_var[mb_xy]);
        const int lumi  = pic->mb_mean[mb_xy];
        float bits, cplx, factor;
        int mb_x = mb_xy % s->mb_stride;
        int mb_y = mb_xy / s->mb_stride;
        int mb_distance;
        float mb_factor = 0.0;
        if (spat_cplx < 4)
            spat_cplx = 4;              // FIXME fine-tune
        if (temp_cplx < 4)
            temp_cplx = 4;              // FIXME fine-tune

        if ((s->mb_type[mb_xy] & CANDIDATE_MB_TYPE_INTRA)) { // FIXME hq mode
            cplx   = spat_cplx;
            factor = 1.0 + p_masking;
        } else {
            cplx   = temp_cplx;
            factor = pow(temp_cplx, -temp_cplx_masking);
        }
        factor *= pow(spat_cplx, -spatial_cplx_masking);

        if (lumi > 127)
            factor *= (1.0 - (lumi - 128) * (lumi - 128) * lumi_masking);
        else
            factor *= (1.0 - (lumi - 128) * (lumi - 128) * dark_masking);

        if (mb_x < mb_width / 5) {
            mb_distance = mb_width / 5 - mb_x;
            mb_factor   = (float)mb_distance / (float)(mb_width / 5);
        } else if (mb_x > 4 * mb_width / 5) {
            mb_distance = mb_x - 4 * mb_width / 5;
            mb_factor   = (float)mb_distance / (float)(mb_width / 5);
        }
        if (mb_y < mb_height / 5) {
            mb_distance = mb_height / 5 - mb_y;
            mb_factor   = FFMAX(mb_factor,
                                (float)mb_distance / (float)(mb_height / 5));
        } else if (mb_y > 4 * mb_height / 5) {
            mb_distance = mb_y - 4 * mb_height / 5;
            mb_factor   = FFMAX(mb_factor,
                                (float)mb_distance / (float)(mb_height / 5));
        }

        factor *= 1.0 - border_masking * mb_factor;

        if (factor < 0.00001)
            factor = 0.00001;

        bits        = cplx * factor;
        cplx_sum   += cplx;
        bits_sum   += bits;
        cplx_tab[i] = cplx;
        bits_tab[i] = bits;
    }

    /* handle qmin/qmax clipping */
    if (s->mpv_flags & FF_MPV_FLAG_NAQ) {
        float factor = bits_sum / cplx_sum;
        for (i = 0; i < s->mb_num; i++) {
            float newq = q * cplx_tab[i] / bits_tab[i];
            newq *= factor;

            if (newq > qmax) {
                bits_sum -= bits_tab[i];
                cplx_sum -= cplx_tab[i] * q / qmax;
            } else if (newq < qmin) {
                bits_sum -= bits_tab[i];
                cplx_sum -= cplx_tab[i] * q / qmin;
            }
        }
        if (bits_sum < 0.001)
            bits_sum = 0.001;
        if (cplx_sum < 0.001)
            cplx_sum = 0.001;
    }

    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        float newq      = q * cplx_tab[i] / bits_tab[i];
        int intq;

        if (s->mpv_flags & FF_MPV_FLAG_NAQ) {
            newq *= bits_sum / cplx_sum;
        }

        intq = (int)(newq + 0.5);

        if (intq > qmax)
            intq = qmax;
        else if (intq < qmin)
            intq = qmin;
        s->lambda_table[mb_xy] = intq;
    }
}