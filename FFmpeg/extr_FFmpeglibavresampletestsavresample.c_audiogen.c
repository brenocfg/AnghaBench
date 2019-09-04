#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
typedef  int /*<<< orphan*/  AVLFG ;

/* Variables and functions */
 int AVRESAMPLE_MAX_CHANNELS ; 
 double M_PI ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 double dbl_rand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_sample (void**,int,int,int,int,double) ; 
 double sin (double) ; 

__attribute__((used)) static void audiogen(AVLFG *rnd, void **data, enum AVSampleFormat sample_fmt,
                     int channels, int sample_rate, int nb_samples)
{
    int i, ch, k;
    double v, f, a, ampa;
    double tabf1[AVRESAMPLE_MAX_CHANNELS];
    double tabf2[AVRESAMPLE_MAX_CHANNELS];
    double taba[AVRESAMPLE_MAX_CHANNELS];

#define PUT_SAMPLE put_sample(data, sample_fmt, channels, k, ch, v);

    k = 0;

    /* 1 second of single freq sine at 1000 Hz */
    a = 0;
    for (i = 0; i < 1 * sample_rate && k < nb_samples; i++, k++) {
        v = sin(a) * 0.30;
        for (ch = 0; ch < channels; ch++)
            PUT_SAMPLE
        a += M_PI * 1000.0 * 2.0 / sample_rate;
    }

    /* 1 second of varying frequency between 100 and 10000 Hz */
    a = 0;
    for (i = 0; i < 1 * sample_rate && k < nb_samples; i++, k++) {
        v = sin(a) * 0.30;
        for (ch = 0; ch < channels; ch++)
            PUT_SAMPLE
        f  = 100.0 + (((10000.0 - 100.0) * i) / sample_rate);
        a += M_PI * f * 2.0 / sample_rate;
    }

    /* 0.5 second of low amplitude white noise */
    for (i = 0; i < sample_rate / 2 && k < nb_samples; i++, k++) {
        v = dbl_rand(rnd) * 0.30;
        for (ch = 0; ch < channels; ch++)
            PUT_SAMPLE
    }

    /* 0.5 second of high amplitude white noise */
    for (i = 0; i < sample_rate / 2 && k < nb_samples; i++, k++) {
        v = dbl_rand(rnd);
        for (ch = 0; ch < channels; ch++)
            PUT_SAMPLE
    }

    /* 1 second of unrelated ramps for each channel */
    for (ch = 0; ch < channels; ch++) {
        taba[ch]  = 0;
        tabf1[ch] = 100 + av_lfg_get(rnd) % 5000;
        tabf2[ch] = 100 + av_lfg_get(rnd) % 5000;
    }
    for (i = 0; i < 1 * sample_rate && k < nb_samples; i++, k++) {
        for (ch = 0; ch < channels; ch++) {
            v = sin(taba[ch]) * 0.30;
            PUT_SAMPLE
            f = tabf1[ch] + (((tabf2[ch] - tabf1[ch]) * i) / sample_rate);
            taba[ch] += M_PI * f * 2.0 / sample_rate;
        }
    }

    /* 2 seconds of 500 Hz with varying volume */
    a    = 0;
    ampa = 0;
    for (i = 0; i < 2 * sample_rate && k < nb_samples; i++, k++) {
        for (ch = 0; ch < channels; ch++) {
            double amp = (1.0 + sin(ampa)) * 0.15;
            if (ch & 1)
                amp = 0.30 - amp;
            v = sin(a) * amp;
            PUT_SAMPLE
            a    += M_PI * 500.0 * 2.0 / sample_rate;
            ampa += M_PI *  2.0 / sample_rate;
        }
    }
}