#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * irdft; int /*<<< orphan*/ * rdft; } ;
typedef  TYPE_1__ SincContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  DFT_R2C ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  IDFT_C2R ; 
 int M_PI ; 
 int /*<<< orphan*/  PACK (float*,int) ; 
 scalar_t__ SQR (float) ; 
 int /*<<< orphan*/  UNPACK (float*,int) ; 
 float atan2f (float,float) ; 
 float* av_calloc (int,int) ; 
 int /*<<< orphan*/  av_free (float*) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int,float,int,float,int,float,int,int,float) ; 
 int /*<<< orphan*/  av_log2 (int) ; 
 int /*<<< orphan*/  av_rdft_calc (int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  av_rdft_end (int /*<<< orphan*/ *) ; 
 void* av_rdft_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float* av_realloc_f (float*,int,int) ; 
 float cosf (float) ; 
 float exp (float) ; 
 float expf (float) ; 
 scalar_t__ fabs (float) ; 
 scalar_t__ fabsf (float) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 float safe_log (int /*<<< orphan*/ ) ; 
 float sinf (float) ; 
 int /*<<< orphan*/  sqrtf (scalar_t__) ; 

__attribute__((used)) static int fir_to_phase(SincContext *s, float **h, int *len, int *post_len, float phase)
{
    float *pi_wraps, *work, phase1 = (phase > 50.f ? 100.f - phase : phase) / 50.f;
    int i, work_len, begin, end, imp_peak = 0, peak = 0;
    float imp_sum = 0, peak_imp_sum = 0;
    float prev_angle2 = 0, cum_2pi = 0, prev_angle1 = 0, cum_1pi = 0;

    for (i = *len, work_len = 2 * 2 * 8; i > 1; work_len <<= 1, i >>= 1);

    work = av_calloc(work_len + 2, sizeof(*work));    /* +2: (UN)PACK */
    pi_wraps = av_calloc(((work_len + 2) / 2), sizeof(*pi_wraps));
    if (!work || !pi_wraps)
        return AVERROR(ENOMEM);

    memcpy(work, *h, *len * sizeof(*work));

    av_rdft_end(s->rdft);
    av_rdft_end(s->irdft);
    s->rdft = s->irdft = NULL;
    s->rdft  = av_rdft_init(av_log2(work_len), DFT_R2C);
    s->irdft = av_rdft_init(av_log2(work_len), IDFT_C2R);
    if (!s->rdft || !s->irdft)
        return AVERROR(ENOMEM);

    av_rdft_calc(s->rdft, work);   /* Cepstral: */
    UNPACK(work, work_len);

    for (i = 0; i <= work_len; i += 2) {
        float angle = atan2f(work[i + 1], work[i]);
        float detect = 2 * M_PI;
        float delta = angle - prev_angle2;
        float adjust = detect * ((delta < -detect * .7f) - (delta > detect * .7f));

        prev_angle2 = angle;
        cum_2pi += adjust;
        angle += cum_2pi;
        detect = M_PI;
        delta = angle - prev_angle1;
        adjust = detect * ((delta < -detect * .7f) - (delta > detect * .7f));
        prev_angle1 = angle;
        cum_1pi += fabsf(adjust);        /* fabs for when 2pi and 1pi have combined */
        pi_wraps[i >> 1] = cum_1pi;

        work[i] = safe_log(sqrtf(SQR(work[i]) + SQR(work[i + 1])));
        work[i + 1] = 0;
    }

    PACK(work, work_len);
    av_rdft_calc(s->irdft, work);

    for (i = 0; i < work_len; i++)
        work[i] *= 2.f / work_len;

    for (i = 1; i < work_len / 2; i++) {        /* Window to reject acausal components */
        work[i] *= 2;
        work[i + work_len / 2] = 0;
    }
    av_rdft_calc(s->rdft, work);

    for (i = 2; i < work_len; i += 2)   /* Interpolate between linear & min phase */
        work[i + 1] = phase1 * i / work_len * pi_wraps[work_len >> 1] + (1 - phase1) * (work[i + 1] + pi_wraps[i >> 1]) - pi_wraps[i >> 1];

    work[0] = exp(work[0]);
    work[1] = exp(work[1]);
    for (i = 2; i < work_len; i += 2) {
        float x = expf(work[i]);

        work[i    ] = x * cosf(work[i + 1]);
        work[i + 1] = x * sinf(work[i + 1]);
    }

    av_rdft_calc(s->irdft, work);
    for (i = 0; i < work_len; i++)
        work[i] *= 2.f / work_len;

    /* Find peak pos. */
    for (i = 0; i <= (int) (pi_wraps[work_len >> 1] / M_PI + .5f); i++) {
        imp_sum += work[i];
        if (fabs(imp_sum) > fabs(peak_imp_sum)) {
            peak_imp_sum = imp_sum;
            peak = i;
        }
        if (work[i] > work[imp_peak])   /* For debug check only */
            imp_peak = i;
    }

    while (peak && fabsf(work[peak - 1]) > fabsf(work[peak]) && (work[peak - 1] * work[peak] > 0)) {
        peak--;
    }

    if (!phase1) {
        begin = 0;
    } else if (phase1 == 1) {
        begin = peak - *len / 2;
    } else {
        begin = (.997f - (2 - phase1) * .22f) * *len + .5f;
        end = (.997f + (0 - phase1) * .22f) * *len + .5f;
        begin = peak - (begin & ~3);
        end = peak + 1 + ((end + 3) & ~3);
        *len = end - begin;
        *h = av_realloc_f(*h, *len, sizeof(**h));
        if (!*h) {
            av_free(pi_wraps);
            av_free(work);
            return AVERROR(ENOMEM);
        }
    }

    for (i = 0; i < *len; i++) {
        (*h)[i] = work[(begin + (phase > 50.f ? *len - 1 - i : i) + work_len) & (work_len - 1)];
    }
    *post_len = phase > 50 ? peak - begin : begin + *len - (peak + 1);

    av_log(s, AV_LOG_DEBUG, "%d nPI=%g peak-sum@%i=%g (val@%i=%g); len=%i post=%i (%g%%)\n",
           work_len, pi_wraps[work_len >> 1] / M_PI, peak, peak_imp_sum, imp_peak,
           work[imp_peak], *len, *post_len, 100.f - 100.f * *post_len / (*len - 1));

    av_free(pi_wraps);
    av_free(work);

    return 0;
}