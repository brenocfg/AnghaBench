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
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tilted_lpcs ;
typedef  int /*<<< orphan*/  synth_pf ;
typedef  int /*<<< orphan*/  lpcs ;
struct TYPE_8__ {int /*<<< orphan*/  (* rdft_calc ) (TYPE_3__*,float*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* rdft_calc ) (TYPE_4__*,float*) ;} ;
struct TYPE_7__ {float* tilted_lpcs_pf; float* denoise_coeffs_pf; int lsps; int denoise_filter_cache_size; float* denoise_filter_cache; TYPE_3__ irdft; TYPE_4__ rdft; } ;
typedef  TYPE_1__ WMAVoiceContext ;

/* Variables and functions */
 int FCB_TYPE_SILENCE ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  calc_input_response (TYPE_1__*,float*,int,float*,int) ; 
 int /*<<< orphan*/  ff_tilt_compensation (float*,double,float*,int) ; 
 int /*<<< orphan*/  memcpy (float*,float const*,int) ; 
 int /*<<< orphan*/  memmove (float*,float*,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,float*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,float*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,float*) ; 
 double tilt_factor (float const*,int) ; 

__attribute__((used)) static void wiener_denoise(WMAVoiceContext *s, int fcb_type,
                           float *synth_pf, int size,
                           const float *lpcs)
{
    int remainder, lim, n;

    if (fcb_type != FCB_TYPE_SILENCE) {
        float *tilted_lpcs = s->tilted_lpcs_pf,
              *coeffs = s->denoise_coeffs_pf, tilt_mem = 0;

        tilted_lpcs[0]           = 1.0;
        memcpy(&tilted_lpcs[1], lpcs, sizeof(lpcs[0]) * s->lsps);
        memset(&tilted_lpcs[s->lsps + 1], 0,
               sizeof(tilted_lpcs[0]) * (128 - s->lsps - 1));
        ff_tilt_compensation(&tilt_mem, 0.7 * tilt_factor(lpcs, s->lsps),
                             tilted_lpcs, s->lsps + 2);

        /* The IRDFT output (127 samples for 7-bit filter) beyond the frame
         * size is applied to the next frame. All input beyond this is zero,
         * and thus all output beyond this will go towards zero, hence we can
         * limit to min(size-1, 127-size) as a performance consideration. */
        remainder = FFMIN(127 - size, size - 1);
        calc_input_response(s, tilted_lpcs, fcb_type, coeffs, remainder);

        /* apply coefficients (in frequency spectrum domain), i.e. complex
         * number multiplication */
        memset(&synth_pf[size], 0, sizeof(synth_pf[0]) * (128 - size));
        s->rdft.rdft_calc(&s->rdft, synth_pf);
        s->rdft.rdft_calc(&s->rdft, coeffs);
        synth_pf[0] *= coeffs[0];
        synth_pf[1] *= coeffs[1];
        for (n = 1; n < 64; n++) {
            float v1 = synth_pf[n * 2], v2 = synth_pf[n * 2 + 1];
            synth_pf[n * 2]     = v1 * coeffs[n * 2] - v2 * coeffs[n * 2 + 1];
            synth_pf[n * 2 + 1] = v2 * coeffs[n * 2] + v1 * coeffs[n * 2 + 1];
        }
        s->irdft.rdft_calc(&s->irdft, synth_pf);
    }

    /* merge filter output with the history of previous runs */
    if (s->denoise_filter_cache_size) {
        lim = FFMIN(s->denoise_filter_cache_size, size);
        for (n = 0; n < lim; n++)
            synth_pf[n] += s->denoise_filter_cache[n];
        s->denoise_filter_cache_size -= lim;
        memmove(s->denoise_filter_cache, &s->denoise_filter_cache[size],
                sizeof(s->denoise_filter_cache[0]) * s->denoise_filter_cache_size);
    }

    /* move remainder of filter output into a cache for future runs */
    if (fcb_type != FCB_TYPE_SILENCE) {
        lim = FFMIN(remainder, s->denoise_filter_cache_size);
        for (n = 0; n < lim; n++)
            s->denoise_filter_cache[n] += synth_pf[size + n];
        if (lim < remainder) {
            memcpy(&s->denoise_filter_cache[lim], &synth_pf[size + lim],
                   sizeof(s->denoise_filter_cache[0]) * (remainder - lim));
            s->denoise_filter_cache_size = remainder;
        }
    }
}