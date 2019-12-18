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
struct TYPE_4__ {float** fft_buffer; int fft_offset; int subframe_size; int* noise2_buffer; size_t band_index; int*** noise; unsigned int rndval; } ;
typedef  TYPE_1__ QDMCContext ;

/* Variables and functions */
 float* amplitude_tab ; 
 int /*<<< orphan*/  lin_calc (TYPE_1__*,float,int,int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int* noise_bands_size ; 
 int* qdmc_nodes ; 

__attribute__((used)) static void add_noise(QDMCContext *s, int ch, int current_subframe)
{
    int i, j, aindex;
    float amplitude;
    float *im = &s->fft_buffer[0 + ch][s->fft_offset + s->subframe_size * current_subframe];
    float *re = &s->fft_buffer[2 + ch][s->fft_offset + s->subframe_size * current_subframe];

    memset(s->noise2_buffer, 0, 4 * s->subframe_size);

    for (i = 0; i < noise_bands_size[s->band_index]; i++) {
        if (qdmc_nodes[i + 21 * s->band_index] > s->subframe_size - 1)
            break;

        aindex = s->noise[ch][i][current_subframe / 2];
        amplitude = aindex > 0 ? amplitude_tab[aindex & 0x3F] : 0.0f;

        lin_calc(s, amplitude, qdmc_nodes[21 * s->band_index + i],
                 qdmc_nodes[21 * s->band_index + i + 2], i);
    }

    for (j = 2; j < s->subframe_size - 1; j++) {
        float rnd_re, rnd_im;

        s->rndval = 214013U * s->rndval + 2531011;
        rnd_im = ((s->rndval & 0x7FFF) - 16384.0f) * 0.000030517578f * s->noise2_buffer[j];
        s->rndval = 214013U * s->rndval + 2531011;
        rnd_re = ((s->rndval & 0x7FFF) - 16384.0f) * 0.000030517578f * s->noise2_buffer[j];
        im[j  ] += rnd_im;
        re[j  ] += rnd_re;
        im[j+1] -= rnd_im;
        re[j+1] -= rnd_re;
    }
}