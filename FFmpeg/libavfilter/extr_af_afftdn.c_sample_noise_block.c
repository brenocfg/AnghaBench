#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {float re; double im; } ;
struct TYPE_12__ {scalar_t__* extended_data; } ;
struct TYPE_11__ {int window_length; float* window; int fft_length2; int* noise_band_edge; int /*<<< orphan*/  sample_floor; int /*<<< orphan*/  fft_length; } ;
struct TYPE_10__ {int* noise_band_norm; double* noise_band_avr; double* noise_band_avi; double* noise_band_var; double* noisy_data; TYPE_7__* fft_data; int /*<<< orphan*/  fft; } ;
typedef  TYPE_1__ DeNoiseChannel ;
typedef  TYPE_2__ AudioFFTDeNoiseContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  av_fft_calc (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  av_fft_permute (int /*<<< orphan*/ ,TYPE_7__*) ; 
 double fmax (double,int /*<<< orphan*/ ) ; 
 int fmin (int,int) ; 
 int /*<<< orphan*/  preprocess (TYPE_7__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sample_noise_block(AudioFFTDeNoiseContext *s,
                               DeNoiseChannel *dnch,
                               AVFrame *in, int ch)
{
    float *src = (float *)in->extended_data[ch];
    double mag2, var = 0.0, avr = 0.0, avi = 0.0;
    int edge, j, k, n, edgemax;

    for (int i = 0; i < s->window_length; i++) {
        dnch->fft_data[i].re = s->window[i] * src[i] * (1LL << 24);
        dnch->fft_data[i].im = 0.0;
    }

    for (int i = s->window_length; i < s->fft_length2; i++) {
        dnch->fft_data[i].re = 0.0;
        dnch->fft_data[i].im = 0.0;
    }

    av_fft_permute(dnch->fft, dnch->fft_data);
    av_fft_calc(dnch->fft, dnch->fft_data);

    preprocess(dnch->fft_data, s->fft_length);

    edge = s->noise_band_edge[0];
    j = edge;
    k = 0;
    n = j;
    edgemax = fmin(s->fft_length2, s->noise_band_edge[15]);
    dnch->fft_data[s->fft_length2].re = dnch->fft_data[0].im;
    dnch->fft_data[0].im = 0.0;
    dnch->fft_data[s->fft_length2].im = 0.0;

    for (int i = j; i <= edgemax; i++) {
        if ((i == j) && (i < edgemax)) {
            if (j > edge) {
                dnch->noise_band_norm[k - 1] += j - edge;
                dnch->noise_band_avr[k - 1] += avr;
                dnch->noise_band_avi[k - 1] += avi;
                dnch->noise_band_var[k - 1] += var;
            }
            k++;
            edge = j;
            j = s->noise_band_edge[k];
            if (k == 15) {
                j++;
            }
            var = 0.0;
            avr = 0.0;
            avi = 0.0;
        }
        avr += dnch->fft_data[n].re;
        avi += dnch->fft_data[n].im;
        mag2 = dnch->fft_data[n].re * dnch->fft_data[n].re +
               dnch->fft_data[n].im * dnch->fft_data[n].im;

        mag2 = fmax(mag2, s->sample_floor);

        dnch->noisy_data[i] = mag2;
        var += mag2;
        n++;
    }

    dnch->noise_band_norm[k - 1] += j - edge;
    dnch->noise_band_avr[k - 1] += avr;
    dnch->noise_band_avi[k - 1] += avi;
    dnch->noise_band_var[k - 1] += var;
}