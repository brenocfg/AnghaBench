#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  out ;
struct TYPE_14__ {int /*<<< orphan*/  (* vector_fmul_scalar ) (float*,float*,float,int) ;} ;
struct TYPE_13__ {int start_pos; int stop_pos; scalar_t__ has_stop_point; scalar_t__ has_start_point; } ;
struct TYPE_12__ {size_t amp_sf; int amp_index; int freq_index; int /*<<< orphan*/  phase_index; } ;
struct TYPE_11__ {int /*<<< orphan*/  amplitude_mode; TYPE_3__* waves; } ;
struct TYPE_10__ {size_t start_index; int num_wavs; } ;
typedef  TYPE_1__ Atrac3pWavesData ;
typedef  TYPE_2__ Atrac3pWaveSynthParams ;
typedef  TYPE_3__ Atrac3pWaveParam ;
typedef  TYPE_4__ Atrac3pWaveEnvelope ;
typedef  TYPE_5__ AVFloatDSPContext ;

/* Variables and functions */
 int DEQUANT_PHASE (int /*<<< orphan*/ ) ; 
 int* amp_sf_tab ; 
 float* hann_window ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 double* sine_table ; 
 int /*<<< orphan*/  stub1 (float*,float*,float,int) ; 

__attribute__((used)) static void waves_synth(Atrac3pWaveSynthParams *synth_param,
                        Atrac3pWavesData *waves_info,
                        Atrac3pWaveEnvelope *envelope,
                        AVFloatDSPContext *fdsp,
                        int invert_phase, int reg_offset, float *out)
{
    int i, wn, inc, pos;
    double amp;
    Atrac3pWaveParam *wave_param = &synth_param->waves[waves_info->start_index];

    for (wn = 0; wn < waves_info->num_wavs; wn++, wave_param++) {
        /* amplitude dequantization */
        amp = amp_sf_tab[wave_param->amp_sf] *
              (!synth_param->amplitude_mode
               ? (wave_param->amp_index + 1) / 15.13f
               : 1.0f);

        inc = wave_param->freq_index;
        pos = DEQUANT_PHASE(wave_param->phase_index) - (reg_offset ^ 128) * inc & 2047;

        /* waveform generation */
        for (i = 0; i < 128; i++) {
            out[i] += sine_table[pos] * amp;
            pos     = (pos + inc) & 2047;
        }
    }

    /* invert phase if requested */
    if (invert_phase)
        fdsp->vector_fmul_scalar(out, out, -1.0f, 128);

    /* fade in with steep Hann window if requested */
    if (envelope->has_start_point) {
        pos = (envelope->start_pos << 2) - reg_offset;
        if (pos > 0 && pos <= 128) {
            memset(out, 0, pos * sizeof(*out));
            if (!envelope->has_stop_point ||
                envelope->start_pos != envelope->stop_pos) {
                out[pos + 0] *= hann_window[0];
                out[pos + 1] *= hann_window[32];
                out[pos + 2] *= hann_window[64];
                out[pos + 3] *= hann_window[96];
            }
        }
    }

    /* fade out with steep Hann window if requested */
    if (envelope->has_stop_point) {
        pos = (envelope->stop_pos + 1 << 2) - reg_offset;
        if (pos > 0 && pos <= 128) {
            out[pos - 4] *= hann_window[96];
            out[pos - 3] *= hann_window[64];
            out[pos - 2] *= hann_window[32];
            out[pos - 1] *= hann_window[0];
            memset(&out[pos], 0, (128 - pos) * sizeof(out[pos]));
        }
    }
}