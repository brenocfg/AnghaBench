#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {float re; float im; } ;
struct TYPE_11__ {float* lastg; int /*<<< orphan*/  rnn; int /*<<< orphan*/  mem_hp_x; } ;
typedef  TYPE_1__ DenoiseState ;
typedef  int /*<<< orphan*/  AudioRNNContext ;
typedef  TYPE_2__ AVComplexFloat ;

/* Variables and functions */
 float FFMAX (float,float) ; 
 int FRAME_SIZE ; 
 int FREQ_SIZE ; 
 int NB_BANDS ; 
 int NB_FEATURES ; 
 int WINDOW_SIZE ; 
 int /*<<< orphan*/  biquad (float*,int /*<<< orphan*/ ,float const*,float const*,float const*,int) ; 
 int compute_frame_features (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,TYPE_2__*,float*,float*,float*,float*,float*) ; 
 int /*<<< orphan*/  compute_rnn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*,float*,float*) ; 
 int /*<<< orphan*/  frame_synthesis (int /*<<< orphan*/ *,TYPE_1__*,float*,TYPE_2__*) ; 
 int /*<<< orphan*/  interp_band_gain (float*,float*) ; 
 int /*<<< orphan*/  pitch_filter (TYPE_2__*,TYPE_2__*,float*,float*,float*,float*) ; 

__attribute__((used)) static float rnnoise_channel(AudioRNNContext *s, DenoiseState *st, float *out, const float *in)
{
    AVComplexFloat X[FREQ_SIZE];
    AVComplexFloat P[WINDOW_SIZE];
    float x[FRAME_SIZE];
    float Ex[NB_BANDS], Ep[NB_BANDS];
    float Exp[NB_BANDS];
    float features[NB_FEATURES];
    float g[NB_BANDS];
    float gf[FREQ_SIZE];
    float vad_prob = 0;
    static const float a_hp[2] = {-1.99599, 0.99600};
    static const float b_hp[2] = {-2, 1};
    int silence;

    biquad(x, st->mem_hp_x, in, b_hp, a_hp, FRAME_SIZE);
    silence = compute_frame_features(s, st, X, P, Ex, Ep, Exp, features, x);

    if (!silence) {
        compute_rnn(s, &st->rnn, g, &vad_prob, features);
        pitch_filter(X, P, Ex, Ep, Exp, g);
        for (int i = 0; i < NB_BANDS; i++) {
            float alpha = .6f;

            g[i] = FFMAX(g[i], alpha * st->lastg[i]);
            st->lastg[i] = g[i];
        }

        interp_band_gain(gf, g);

        for (int i = 0; i < FREQ_SIZE; i++) {
            X[i].re *= gf[i];
            X[i].im *= gf[i];
        }
    }

    frame_synthesis(s, st, out, X);

    return vad_prob;
}