#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  float int8_t ;
struct TYPE_8__ {int* stereo_weights; size_t midonly; int subframes; size_t bandwidth; int output_channels; int sflength; int nlsf_interp_factor; int flength; TYPE_1__* frame; } ;
struct TYPE_7__ {int coded; int log_gain; int prev_voiced; int primarylag; float* output; float* lpc_history; } ;
typedef  TYPE_1__ SilkFrame ;
typedef  TYPE_2__ SilkContext ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int LTP_ORDER ; 
 size_t OPUS_BANDWIDTH_NARROWBAND ; 
 int SILK_HISTORY ; 
 int SILK_MAX_LAG ; 
 int av_clip (float const,int,int /*<<< orphan*/ ) ; 
 int av_clip_uintp2 (int,int) ; 
 float av_clipf (float,float,float) ; 
 size_t ff_opus_rc_dec_cdf (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const) ; 
#define  ff_silk_ltp_filter0_taps 136 
#define  ff_silk_ltp_filter1_taps 135 
#define  ff_silk_ltp_filter2_taps 134 
 float* ff_silk_ltp_scale_factor ; 
 int /*<<< orphan*/  const* const ff_silk_model_frame_type_active ; 
 int /*<<< orphan*/  const* const ff_silk_model_frame_type_inactive ; 
 int /*<<< orphan*/  const* const ff_silk_model_gain_delta ; 
 int /*<<< orphan*/  const* const* ff_silk_model_gain_highbits ; 
 int /*<<< orphan*/  const* const ff_silk_model_gain_lowbits ; 
 int /*<<< orphan*/  const* const ff_silk_model_ltp_filter ; 
#define  ff_silk_model_ltp_filter0_sel 133 
#define  ff_silk_model_ltp_filter1_sel 132 
#define  ff_silk_model_ltp_filter2_sel 131 
 int /*<<< orphan*/  const* const ff_silk_model_ltp_scale_index ; 
 int /*<<< orphan*/  const* const ff_silk_model_mid_only ; 
 int /*<<< orphan*/  const* const ff_silk_model_pitch_contour_mbwb10ms ; 
 int /*<<< orphan*/  const* const ff_silk_model_pitch_contour_mbwb20ms ; 
 int /*<<< orphan*/  const* const ff_silk_model_pitch_contour_nb10ms ; 
 int /*<<< orphan*/  const* const ff_silk_model_pitch_contour_nb20ms ; 
 int /*<<< orphan*/  const* const ff_silk_model_pitch_delta ; 
 int /*<<< orphan*/  const* const ff_silk_model_pitch_highbits ; 
#define  ff_silk_model_pitch_lowbits_mb 130 
#define  ff_silk_model_pitch_lowbits_nb 129 
#define  ff_silk_model_pitch_lowbits_wb 128 
 int /*<<< orphan*/  const* const ff_silk_model_stereo_s1 ; 
 int /*<<< orphan*/  const* const ff_silk_model_stereo_s2 ; 
 int /*<<< orphan*/  const* const ff_silk_model_stereo_s3 ; 
 int /*<<< orphan*/ * ff_silk_pitch_max_lag ; 
 int* ff_silk_pitch_min_lag ; 
 float** ff_silk_pitch_offset_mbwb10ms ; 
 float** ff_silk_pitch_offset_mbwb20ms ; 
 float** ff_silk_pitch_offset_nb10ms ; 
 float** ff_silk_pitch_offset_nb20ms ; 
 int* ff_silk_pitch_scale ; 
 int* ff_silk_stereo_weights ; 
 int /*<<< orphan*/  memmove (float*,float*,int) ; 
 int /*<<< orphan*/  silk_decode_excitation (TYPE_2__*,int /*<<< orphan*/ *,float*,int,int,int) ; 
 int /*<<< orphan*/  silk_decode_lpc (TYPE_2__*,TYPE_1__* const,int /*<<< orphan*/ *,float*,float*,int*,int*,int) ; 

__attribute__((used)) static void silk_decode_frame(SilkContext *s, OpusRangeCoder *rc,
                              int frame_num, int channel, int coded_channels, int active, int active1)
{
    /* per frame */
    int voiced;       // combines with active to indicate inactive, active, or active+voiced
    int qoffset_high;
    int order;                             // order of the LPC coefficients
    float lpc_leadin[16], lpc_body[16], residual[SILK_MAX_LAG + SILK_HISTORY];
    int has_lpc_leadin;
    float ltpscale;

    /* per subframe */
    struct {
        float gain;
        int pitchlag;
        float ltptaps[5];
    } sf[4];

    SilkFrame * const frame = s->frame + channel;

    int i;

    /* obtain stereo weights */
    if (coded_channels == 2 && channel == 0) {
        int n, wi[2], ws[2], w[2];
        n     = ff_opus_rc_dec_cdf(rc, ff_silk_model_stereo_s1);
        wi[0] = ff_opus_rc_dec_cdf(rc, ff_silk_model_stereo_s2) + 3 * (n / 5);
        ws[0] = ff_opus_rc_dec_cdf(rc, ff_silk_model_stereo_s3);
        wi[1] = ff_opus_rc_dec_cdf(rc, ff_silk_model_stereo_s2) + 3 * (n % 5);
        ws[1] = ff_opus_rc_dec_cdf(rc, ff_silk_model_stereo_s3);

        for (i = 0; i < 2; i++)
            w[i] = ff_silk_stereo_weights[wi[i]] +
                   (((ff_silk_stereo_weights[wi[i] + 1] - ff_silk_stereo_weights[wi[i]]) * 6554) >> 16)
                    * (ws[i]*2 + 1);

        s->stereo_weights[0] = (w[0] - w[1]) / 8192.0;
        s->stereo_weights[1] = w[1]          / 8192.0;

        /* and read the mid-only flag */
        s->midonly = active1 ? 0 : ff_opus_rc_dec_cdf(rc, ff_silk_model_mid_only);
    }

    /* obtain frame type */
    if (!active) {
        qoffset_high = ff_opus_rc_dec_cdf(rc, ff_silk_model_frame_type_inactive);
        voiced = 0;
    } else {
        int type = ff_opus_rc_dec_cdf(rc, ff_silk_model_frame_type_active);
        qoffset_high = type & 1;
        voiced = type >> 1;
    }

    /* obtain subframe quantization gains */
    for (i = 0; i < s->subframes; i++) {
        int log_gain;     //Q7
        int ipart, fpart, lingain;

        if (i == 0 && (frame_num == 0 || !frame->coded)) {
            /* gain is coded absolute */
            int x = ff_opus_rc_dec_cdf(rc, ff_silk_model_gain_highbits[active + voiced]);
            log_gain = (x<<3) | ff_opus_rc_dec_cdf(rc, ff_silk_model_gain_lowbits);

            if (frame->coded)
                log_gain = FFMAX(log_gain, frame->log_gain - 16);
        } else {
            /* gain is coded relative */
            int delta_gain = ff_opus_rc_dec_cdf(rc, ff_silk_model_gain_delta);
            log_gain = av_clip_uintp2(FFMAX((delta_gain<<1) - 16,
                                     frame->log_gain + delta_gain - 4), 6);
        }

        frame->log_gain = log_gain;

        /* approximate 2**(x/128) with a Q7 (i.e. non-integer) input */
        log_gain = (log_gain * 0x1D1C71 >> 16) + 2090;
        ipart = log_gain >> 7;
        fpart = log_gain & 127;
        lingain = (1 << ipart) + ((-174 * fpart * (128-fpart) >>16) + fpart) * ((1<<ipart) >> 7);
        sf[i].gain = lingain / 65536.0f;
    }

    /* obtain LPC filter coefficients */
    silk_decode_lpc(s, frame, rc, lpc_leadin, lpc_body, &order, &has_lpc_leadin, voiced);

    /* obtain pitch lags, if this is a voiced frame */
    if (voiced) {
        int lag_absolute = (!frame_num || !frame->prev_voiced);
        int primarylag;         // primary pitch lag for the entire SILK frame
        int ltpfilter;
        const int8_t * offsets;

        if (!lag_absolute) {
            int delta = ff_opus_rc_dec_cdf(rc, ff_silk_model_pitch_delta);
            if (delta)
                primarylag = frame->primarylag + delta - 9;
            else
                lag_absolute = 1;
        }

        if (lag_absolute) {
            /* primary lag is coded absolute */
            int highbits, lowbits;
            static const uint16_t * const model[] = {
                ff_silk_model_pitch_lowbits_nb, ff_silk_model_pitch_lowbits_mb,
                ff_silk_model_pitch_lowbits_wb
            };
            highbits = ff_opus_rc_dec_cdf(rc, ff_silk_model_pitch_highbits);
            lowbits  = ff_opus_rc_dec_cdf(rc, model[s->bandwidth]);

            primarylag = ff_silk_pitch_min_lag[s->bandwidth] +
                         highbits*ff_silk_pitch_scale[s->bandwidth] + lowbits;
        }
        frame->primarylag = primarylag;

        if (s->subframes == 2)
            offsets = (s->bandwidth == OPUS_BANDWIDTH_NARROWBAND)
                     ? ff_silk_pitch_offset_nb10ms[ff_opus_rc_dec_cdf(rc,
                                                ff_silk_model_pitch_contour_nb10ms)]
                     : ff_silk_pitch_offset_mbwb10ms[ff_opus_rc_dec_cdf(rc,
                                                ff_silk_model_pitch_contour_mbwb10ms)];
        else
            offsets = (s->bandwidth == OPUS_BANDWIDTH_NARROWBAND)
                     ? ff_silk_pitch_offset_nb20ms[ff_opus_rc_dec_cdf(rc,
                                                ff_silk_model_pitch_contour_nb20ms)]
                     : ff_silk_pitch_offset_mbwb20ms[ff_opus_rc_dec_cdf(rc,
                                                ff_silk_model_pitch_contour_mbwb20ms)];

        for (i = 0; i < s->subframes; i++)
            sf[i].pitchlag = av_clip(primarylag + offsets[i],
                                     ff_silk_pitch_min_lag[s->bandwidth],
                                     ff_silk_pitch_max_lag[s->bandwidth]);

        /* obtain LTP filter coefficients */
        ltpfilter = ff_opus_rc_dec_cdf(rc, ff_silk_model_ltp_filter);
        for (i = 0; i < s->subframes; i++) {
            int index, j;
            static const uint16_t * const filter_sel[] = {
                ff_silk_model_ltp_filter0_sel, ff_silk_model_ltp_filter1_sel,
                ff_silk_model_ltp_filter2_sel
            };
            static const int8_t (* const filter_taps[])[5] = {
                ff_silk_ltp_filter0_taps, ff_silk_ltp_filter1_taps, ff_silk_ltp_filter2_taps
            };
            index = ff_opus_rc_dec_cdf(rc, filter_sel[ltpfilter]);
            for (j = 0; j < 5; j++)
                sf[i].ltptaps[j] = filter_taps[ltpfilter][index][j] / 128.0f;
        }
    }

    /* obtain LTP scale factor */
    if (voiced && frame_num == 0)
        ltpscale = ff_silk_ltp_scale_factor[ff_opus_rc_dec_cdf(rc,
                                         ff_silk_model_ltp_scale_index)] / 16384.0f;
    else ltpscale = 15565.0f/16384.0f;

    /* generate the excitation signal for the entire frame */
    silk_decode_excitation(s, rc, residual + SILK_MAX_LAG, qoffset_high,
                           active, voiced);

    /* skip synthesising the side channel if we want mono-only */
    if (s->output_channels == channel)
        return;

    /* generate the output signal */
    for (i = 0; i < s->subframes; i++) {
        const float * lpc_coeff = (i < 2 && has_lpc_leadin) ? lpc_leadin : lpc_body;
        float *dst    = frame->output      + SILK_HISTORY + i * s->sflength;
        float *resptr = residual           + SILK_MAX_LAG + i * s->sflength;
        float *lpc    = frame->lpc_history + SILK_HISTORY + i * s->sflength;
        float sum;
        int j, k;

        if (voiced) {
            int out_end;
            float scale;

            if (i < 2 || s->nlsf_interp_factor == 4) {
                out_end = -i * s->sflength;
                scale   = ltpscale;
            } else {
                out_end = -(i - 2) * s->sflength;
                scale   = 1.0f;
            }

            /* when the LPC coefficients change, a re-whitening filter is used */
            /* to produce a residual that accounts for the change */
            for (j = - sf[i].pitchlag - LTP_ORDER/2; j < out_end; j++) {
                sum = dst[j];
                for (k = 0; k < order; k++)
                    sum -= lpc_coeff[k] * dst[j - k - 1];
                resptr[j] = av_clipf(sum, -1.0f, 1.0f) * scale / sf[i].gain;
            }

            if (out_end) {
                float rescale = sf[i-1].gain / sf[i].gain;
                for (j = out_end; j < 0; j++)
                    resptr[j] *= rescale;
            }

            /* LTP synthesis */
            for (j = 0; j < s->sflength; j++) {
                sum = resptr[j];
                for (k = 0; k < LTP_ORDER; k++)
                    sum += sf[i].ltptaps[k] * resptr[j - sf[i].pitchlag + LTP_ORDER/2 - k];
                resptr[j] = sum;
            }
        }

        /* LPC synthesis */
        for (j = 0; j < s->sflength; j++) {
            sum = resptr[j] * sf[i].gain;
            for (k = 1; k <= order; k++)
                sum += lpc_coeff[k - 1] * lpc[j - k];

            lpc[j] = sum;
            dst[j] = av_clipf(sum, -1.0f, 1.0f);
        }
    }

    frame->prev_voiced = voiced;
    memmove(frame->lpc_history, frame->lpc_history + s->flength, SILK_HISTORY * sizeof(float));
    memmove(frame->output,      frame->output      + s->flength, SILK_HISTORY * sizeof(float));

    frame->coded = 1;
}