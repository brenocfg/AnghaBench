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
struct TYPE_13__ {int /*<<< orphan*/  is_disabled; TYPE_4__* priv; } ;
struct TYPE_12__ {scalar_t__* extended_data; } ;
struct TYPE_10__ {float (* compute_distance_ssd ) (float const*,float const*,int const) ;int /*<<< orphan*/  (* compute_cache ) (float*,float const*,int const,int const,int,int) ;} ;
struct TYPE_11__ {int S; int K; int om; int offset; float m; int const H; float pdiff_lut_scale; float* weight_lut; TYPE_3__ dsp; int /*<<< orphan*/  a; TYPE_2__* cache; TYPE_1__* in; } ;
struct TYPE_9__ {scalar_t__* extended_data; } ;
struct TYPE_8__ {scalar_t__* extended_data; } ;
typedef  TYPE_4__ AudioNLMeansContext ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
#define  IN_MODE 130 
#define  NOISE_MODE 129 
#define  OUT_MODE 128 
 unsigned int WEIGHT_LUT_SIZE ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 float sqrtf (int /*<<< orphan*/ ) ; 
 float stub1 (float const*,float const*,int const) ; 
 int /*<<< orphan*/  stub2 (float*,float const*,int const,int const,int,int) ; 
 int /*<<< orphan*/  stub3 (float*,float const*,int const,int const,int,int) ; 

__attribute__((used)) static int filter_channel(AVFilterContext *ctx, void *arg, int ch, int nb_jobs)
{
    AudioNLMeansContext *s = ctx->priv;
    AVFrame *out = arg;
    const int S = s->S;
    const int K = s->K;
    const int om = s->om;
    const float *f = (const float *)(s->in->extended_data[ch]) + K;
    float *cache = (float *)s->cache->extended_data[ch];
    const float sw = (65536.f / (4 * K + 2)) / sqrtf(s->a);
    float *dst = (float *)out->extended_data[ch] + s->offset;
    const float smooth = s->m;

    for (int i = S; i < s->H + S; i++) {
        float P = 0.f, Q = 0.f;
        int v = 0;

        if (i == S) {
            for (int j = i - S; j <= i + S; j++) {
                if (i == j)
                    continue;
                cache[v++] = s->dsp.compute_distance_ssd(f + i, f + j, K);
            }
        } else {
            s->dsp.compute_cache(cache, f, S, K, i, i - S);
            s->dsp.compute_cache(cache + S, f, S, K, i, i + 1);
        }

        for (int j = 0; j < 2 * S && !ctx->is_disabled; j++) {
            const float distance = cache[j];
            unsigned weight_lut_idx;
            float w;

            if (distance < 0.f) {
                cache[j] = 0.f;
                continue;
            }
            w = distance * sw;
            if (w >= smooth)
                continue;
            weight_lut_idx = w * s->pdiff_lut_scale;
            av_assert2(weight_lut_idx < WEIGHT_LUT_SIZE);
            w = s->weight_lut[weight_lut_idx];
            P += w * f[i - S + j + (j >= S)];
            Q += w;
        }

        P += f[i];
        Q += 1;

        switch (om) {
        case IN_MODE:    dst[i - S] = f[i];           break;
        case OUT_MODE:   dst[i - S] = P / Q;          break;
        case NOISE_MODE: dst[i - S] = f[i] - (P / Q); break;
        }
    }

    return 0;
}