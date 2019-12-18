#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nb_channels; float** fft_buffer; int fft_offset; int subframe_size; float** alt_sin; int frame_size; } ;
typedef  TYPE_1__ QDMCContext ;

/* Variables and functions */
 float* amplitude_tab ; 
 float* sin_table ; 

__attribute__((used)) static void add_wave(QDMCContext *s, int offset, int freqs, int group, int stereo_mode, int amp, int phase)
{
    int j, group_bits, pos, pindex;
    float im, re, amplitude, level, *imptr, *reptr;

    if (s->nb_channels == 1)
        stereo_mode = 0;

    group_bits = 4 - group;
    pos = freqs >> (4 - group);
    amplitude = amplitude_tab[amp & 0x3F];
    imptr = &s->fft_buffer[    stereo_mode][s->fft_offset + s->subframe_size * offset + pos];
    reptr = &s->fft_buffer[2 + stereo_mode][s->fft_offset + s->subframe_size * offset + pos];
    pindex = (phase << 6) - ((2 * (freqs >> (4 - group)) + 1) << 7);
    for (j = 0; j < (1 << (group_bits + 1)) - 1; j++) {
        pindex += (2 * freqs + 1) << (7 - group_bits);
        level = amplitude * s->alt_sin[group][j];
        im = level * sin_table[ pindex        & 0x1FF];
        re = level * sin_table[(pindex + 128) & 0x1FF];
        imptr[0] += im;
        imptr[1] -= im;
        reptr[0] += re;
        reptr[1] -= re;
        imptr += s->subframe_size;
        reptr += s->subframe_size;
        if (imptr >= &s->fft_buffer[stereo_mode][2 * s->frame_size]) {
            imptr = &s->fft_buffer[0 + stereo_mode][pos];
            reptr = &s->fft_buffer[2 + stereo_mode][pos];
        }
    }
}