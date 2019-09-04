#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {float re; float im; } ;
struct TYPE_14__ {int cutoff; double level; int phase; int phase_shift; int duration; scalar_t__ time_index; int /*<<< orphan*/  table; TYPE_9__* complex; } ;
struct TYPE_13__ {float re; float im; } ;
struct TYPE_10__ {TYPE_9__** complex; } ;
struct TYPE_12__ {int channels; int fft_size; int* fft_coefs_min_index; int* fft_coefs_max_index; int fft_tone_end; int fft_tone_start; int frequency_range; TYPE_2__* fft_coefs; TYPE_1__ fft; scalar_t__ superblocktype_2_3; TYPE_5__* fft_tones; } ;
struct TYPE_11__ {int sub_packet; int channel; scalar_t__ exp; double const phase; int offset; } ;
typedef  TYPE_3__ QDM2Context ;
typedef  TYPE_4__ QDM2Complex ;
typedef  TYPE_5__ FFTTone ;

/* Variables and functions */
 double M_PI ; 
 float cos (double const) ; 
 double** fft_tone_level_table ; 
 int /*<<< orphan*/ ** fft_tone_sample_table ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qdm2_fft_generate_tone (TYPE_3__*,TYPE_5__*) ; 
 float sin (double const) ; 

__attribute__((used)) static void qdm2_fft_tone_synthesizer(QDM2Context *q, int sub_packet)
{
    int i, j, ch;
    const double iscale = 0.25 * M_PI;

    for (ch = 0; ch < q->channels; ch++) {
        memset(q->fft.complex[ch], 0, q->fft_size * sizeof(QDM2Complex));
    }


    /* apply FFT tones with duration 4 (1 FFT period) */
    if (q->fft_coefs_min_index[4] >= 0)
        for (i = q->fft_coefs_min_index[4]; i < q->fft_coefs_max_index[4]; i++) {
            float level;
            QDM2Complex c;

            if (q->fft_coefs[i].sub_packet != sub_packet)
                break;

            ch = (q->channels == 1) ? 0 : q->fft_coefs[i].channel;
            level = (q->fft_coefs[i].exp < 0) ? 0.0 : fft_tone_level_table[q->superblocktype_2_3 ? 0 : 1][q->fft_coefs[i].exp & 63];

            c.re = level * cos(q->fft_coefs[i].phase * iscale);
            c.im = level * sin(q->fft_coefs[i].phase * iscale);
            q->fft.complex[ch][q->fft_coefs[i].offset + 0].re += c.re;
            q->fft.complex[ch][q->fft_coefs[i].offset + 0].im += c.im;
            q->fft.complex[ch][q->fft_coefs[i].offset + 1].re -= c.re;
            q->fft.complex[ch][q->fft_coefs[i].offset + 1].im -= c.im;
        }

    /* generate existing FFT tones */
    for (i = q->fft_tone_end; i != q->fft_tone_start; ) {
        qdm2_fft_generate_tone(q, &q->fft_tones[q->fft_tone_start]);
        q->fft_tone_start = (q->fft_tone_start + 1) % 1000;
    }

    /* create and generate new FFT tones with duration 0 (long) to 3 (short) */
    for (i = 0; i < 4; i++)
        if (q->fft_coefs_min_index[i] >= 0) {
            for (j = q->fft_coefs_min_index[i]; j < q->fft_coefs_max_index[i]; j++) {
                int offset, four_i;
                FFTTone tone;

                if (q->fft_coefs[j].sub_packet != sub_packet)
                    break;

                four_i = (4 - i);
                offset = q->fft_coefs[j].offset >> four_i;
                ch = (q->channels == 1) ? 0 : q->fft_coefs[j].channel;

                if (offset < q->frequency_range) {
                    if (offset < 2)
                        tone.cutoff = offset;
                    else
                        tone.cutoff = (offset >= 60) ? 3 : 2;

                    tone.level = (q->fft_coefs[j].exp < 0) ? 0.0 : fft_tone_level_table[q->superblocktype_2_3 ? 0 : 1][q->fft_coefs[j].exp & 63];
                    tone.complex = &q->fft.complex[ch][offset];
                    tone.table = fft_tone_sample_table[i][q->fft_coefs[j].offset - (offset << four_i)];
                    tone.phase = 64 * q->fft_coefs[j].phase - (offset << 8) - 128;
                    tone.phase_shift = (2 * q->fft_coefs[j].offset + 1) << (7 - four_i);
                    tone.duration = i;
                    tone.time_index = 0;

                    qdm2_fft_generate_tone(q, &tone);
                }
            }
            q->fft_coefs_min_index[i] = j;
        }
}